#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEG 1048576
#define RBS 8192
#define K64 65536

typedef unsigned long long V;
typedef unsigned int U;

struct _bt{
    V hash;
    char* term;
    struct _bt * ch[2];
};
typedef struct _bt BinarySearchTree;

V lo=0x768032e13e71e9fbu;
V la=0xf38df1969a680995u;
V lc=0x5686184f5ef9ddb9u;
V sp;
BinarySearchTree* tree [K64];
BinarySearchTree* stack [K64];
int allowed[256];
long * fileNamePointers;
char readB[MEG];
unsigned char freadB[RBS];
int annotation = 0;

BinarySearchTree* getTreeNode(void){
    BinarySearchTree* r=(BinarySearchTree*)malloc(sizeof (BinarySearchTree));
    r->ch[0]=r->ch[1]=NULL;
    return r;
}

char * getTerm(char* interm){
    char * r= (char*)malloc(strlen(interm)+1);
    strcpy (r,interm);
    return r;
}

void insert(BinarySearchTree ** inbt, char * term, V hash){
    BinarySearchTree * bt=*inbt;
    BinarySearchTree * p =bt;
    int newTerm = 1;
    int q;
    while(bt !=NULL){
        if(hash==bt->hash){
            q=strcmp(term,bt->term);
            if(q==0){
                newTerm=0;
                break;
            } else {
                q=1-(q<0);
            }

        } else {
            if(hash > bt->hash){
                q=1;
            } else {
                q=0;
            }
        }
        p=bt;
        bt=bt->ch[q];
    }
    if(newTerm){
        if(bt==p){
            bt=*inbt=getTreeNode(); /* NULL root */
        } else {
            bt=p->ch[q]=getTreeNode();
        }
        bt->hash=hash;
        bt->term=getTerm(term);
    }
}

void init(void){
    int i;
    int c;
    for (i=0;i<256;i++){
        c=(i=='_');
        c|=(i>='0'&&i<='9');
        c|=(i>='A'&&i<='Z');
        c|=(i>='a'&&i<='z');
        allowed[i]=c;
    }
    for(i=0;i<K64;i++){
        tree[i]=NULL;
    }
}

void processBuffer(int r, int *l){
    BinarySearchTree**bts=NULL;
    int i;
    int ll=*l;
    unsigned char c;
    for(i=0;i<r;i++){
        c=freadB[i];
        if(allowed[c]){
            readB[ll++]=(char)(c);
            sp^=(V)c;
            sp*=la;
            sp+=lc;
        } else {
            if(ll>1){
                readB[ll]=0;
                sp=sp>>32;

                //bts=&tree[(int)sp&0xffff];
                bts=&tree[(int)(sp>>16)];
                insert(bts,readB,sp);
            }
            ll=0;
            sp=lo;
        }
    }
    *l=ll;
}

void dumpTree(BinarySearchTree * bt){
    int p = 0;
    while(p>-1){
        while(bt!=NULL){
            stack[p++]=bt;
            bt=bt->ch[0]; /* visit left child */
        }
        p--;
        if(p>-1){
            bt=stack[p]; /* pop */
            if(bt!=NULL){
                if (annotation){
                    int i = 0;
                    for(i=0;i<p;i++){
                        printf(".");
                    }
                }
                printf("(%08llx) %s\n",bt->hash,bt->term);
                bt=bt->ch[1]; /* visit right child */
            }
        }
    }
}

void dump(void){
    int i = 0;

    for(i=0;i<K64;i++){
        dumpTree(tree[i]);
    }
}

void processFile(FILE* f){
    int l =0;
    int r = 0;


    sp=lo;
    do{
        r=fread(freadB,1,RBS,f);
        if(r<RBS){
            freadB[r]=0;
        }
        processBuffer(r, &l);
    }while(r>0);
}

void processFiles(FILE* f){
    long * ret=(long*)malloc(MEG*sizeof(long));
    int max = MEG;
    int numFiles = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    long p = ftell(f);
    FILE* g=NULL;

    while ((nread = getline(&line, &len, f)) != -1) {
        p = ftell(f);
        ret[0]=(long)numFiles;
        ret[1+numFiles++]=p;
        if(numFiles>max-16){
            max*=2;
            ret=(long*)realloc(ret,max*sizeof (long));
        }
        line[nread-1]=0;
        g=NULL;
        g=fopen(line,"rb");
        if(g!=NULL){
            processFile(g);
            fclose(g);
        }
    }
    dump();
}

void handleFileList(char * fn){
    FILE * f= NULL;
    f=fopen(fn,"r");
    if(f!=NULL){
        processFiles(f);
        fclose(f);
    }
}

void lrot(BinarySearchTree * x){
    BinarySearchTree ** p= &x;
    BinarySearchTree *y= x->ch[1];
    BinarySearchTree *q= y->ch[0];
    *p=y;
    y->ch[0]=x;
    x->ch[1]=q;
}

void rdump(BinarySearchTree * t){
    if(t!=NULL){
        printf("%s\n.",t->term);
        rdump(t->ch[0]);
        printf(".");
        rdump(t->ch[1]);
    } else {
        printf("\n");
    }
}

void test(void){
    BinarySearchTree *t =NULL;

    insert(&t,"5",5);
    insert(&t,"4",4);
    insert(&t,"6",6);
    insert(&t,"7",7);
    dumpTree(t);
    //lrot(t);
    printf("--------\n");
    rdump(t);
    dumpTree(t);

}

int main (int argc, char ** argv){
    if (argc>1){
        init();
        //annotation=1;
        handleFileList(argv[1]);
    } else {
        test();
    }
    return 0;
}
