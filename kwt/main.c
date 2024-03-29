#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MEG 1048576
#define RBS 8192
#define K64 65536
#define M16 16777216

typedef unsigned long long V;
typedef unsigned int U;

struct _il{
    int x;
    struct _il * n;
};

typedef struct _il Il;

struct _bt{
    U hash;
    int bal;
    char* term;
    Il * d;
    struct _bt * ch[2];
};
typedef struct _bt Bst;

typedef struct {
    void* p[RBS];
    size_t s;
    size_t l;
    int rp;
    int cp;
    void * ptr;
    char id[16];
} MemPool;

V lo=0x768032e13e71e9fbu;
V la=0xf38df1969a680995u;
V lc=0x5686184f5ef9ddb9u;
V sp;
MemPool * treePool = NULL;
MemPool * stringPool = NULL;
MemPool * docPool = NULL;
Bst* tree [M16];
Bst* stack [K64];
Bst** pp [256];
Bst* pool;
int poolIndex = 0;
int poolLimit=MEG;
int allowed[256];
long * fileNamePointers;
char readB[MEG];
unsigned char freadB[RBS];
char trail[256];
int docNumber;

void getMemPoolRow(MemPool * mp){
    if(mp->rp==RBS){
        printf("Row Buffer exceeded; %s row %d.\n",mp->id,mp->rp);
        exit(1);
    }
    mp->p[mp->rp]=mp->ptr=malloc(mp->l);
    mp->cp=0;
    if(mp->ptr==NULL){
        printf("Failed to allocate %s row %d.\n",mp->id,mp->rp);
        exit(1);
    }
}

MemPool * newMemPool(size_t size, char* name){
    MemPool * mp = NULL;
    int i = 0;
    mp = (MemPool *)malloc(sizeof(MemPool));
    if(mp == NULL){
        printf("Failed to allocate %s.\n",name);
        exit(1); /* allocate or die */
    }
    for(i=0;i<RBS;i++){
        mp->p[i]=NULL;
    }
    mp->s=size;
    mp->l=size*MEG;
    mp->rp=0;
    strncpy(mp->id,name,15);
    mp->id[15]='\0';
    getMemPoolRow(mp);
    return mp;
}

void * getMemory(MemPool * mp, size_t numUnits){
    void * ret = NULL;
    if(mp != NULL){
        size_t add = numUnits*mp->s;
        if(mp->cp+add > mp->l){
            mp->rp ++;
            getMemPoolRow(mp);
        }
        ret=mp->ptr;
        mp->ptr+=add;
        mp->cp+=add;
    }
    return ret;
}

Il* addDocNumberToHead(Il* il){
    Il * ret = (Il*)getMemory(docPool,1);
    ret->n=il;
    ret->x=docNumber;
    return ret;
}


Bst* getTreeNode(void){
    Bst * r=(Bst*)getMemory(treePool,1);
    r->ch[0]=r->ch[1]=NULL;
    r->bal=0;
    return r;
}

char * getTerm(char* interm){
    char * r= (char*)getMemory(stringPool,strlen(interm)+1);
    strcpy (r,interm);
    return r;
}

void prr(Bst * t,char * u){
    printf("%s%d\n",u,t->hash);
    fflush(NULL);
}

void lrot(Bst ** x){
    Bst *y= (*x)->ch[1];
    Bst *q= y->ch[0];
    y->bal=(*x)->bal=0; /* caution another case is needed for deletion.*/
    y->ch[0]=*x;
    (*x)->ch[1]=q;
    *x=y;
}

void rrot(Bst ** x){
    Bst *y= (*x)->ch[0];
    Bst *q= y->ch[1];
    y->bal=(*x)->bal=0; /* caution another case is needed for deletion.*/
    y->ch[1]=*x;
    (*x)->ch[0]=q;
    *x=y;
}

void rlrot(Bst ** x){
    Bst * z=(*x)->ch[1];
    Bst * y=z->ch[0];
    Bst * p=y->ch[0];
    Bst * q=y->ch[1];


    if(y->bal==0){
        (*x)->bal=z->bal=0;
    } else {
        if (y->bal > 0) { /* q was higher*/
            (*x)->bal = -1;
            z->bal = 0;
        } else {/* p was higher*/
            (*x)->bal = 0;
            z->bal = 1;
        }
    }
    y->bal = 0;
    y->ch[0]=*x;
    (*x)->ch[1]=p;
    y->ch[1]=z;
    z->ch[0]=q;
    *x=y;
}

void lrrot(Bst ** x){
    Bst * z=(*x)->ch[0];
    Bst * y=z->ch[1];
    Bst * p=y->ch[1];
    Bst * q=y->ch[0];


    if(y->bal==0){
        (*x)->bal=z->bal=0;
    } else {
        if (y->bal < 0) { /* q was higher*/
            (*x)->bal = 1;
            z->bal = 0;
        } else {/* p was higher*/
            (*x)->bal = 0;
            z->bal = -1;
        }
    }
    y->bal=0;
    y->ch[1]=*x;
    (*x)->ch[0]=p;
    y->ch[0]=z;
    z->ch[1]=q;
    *x=y;
}

void insert(Bst ** inbt, char * term, V hash){
    Bst * bt=*inbt;
    Bst * p =bt;
    int newTerm = 1;
    int q;
    int t = 0;
    int i = 0;

    pp[0]=inbt;
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
        stack[t++]=p=bt;
        pp[t]=&(bt->ch[q]);
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
        for(i=t-1;i>-1;i--){
            p=stack[i];
            if(bt==p->ch[1]){/* The right subtree increases */
                if(p->bal>0){
                    if(bt->bal < 0){ /*right-left case*/
                        rlrot(pp[i]);
                    } else { /* left case */
                        lrot(pp[i]);
                    }
                } else {
                    if(p->bal <0){
                        p->bal=0;
                        break;
                    }
                    p->bal=1;
                    bt=p;
                    continue;
                }
            } else { /* Z == left_child(X): the left subtree increases */
                if(p->bal<0){
                    if(bt->bal > 0){ /*right-left-right case*/
                        lrrot(pp[i]);
                    } else { /* left case */
                        rrot(pp[i]);
                    }
                } else {
                    if(p->bal >0){
                        p->bal=0;
                        break;
                    }
                    p->bal=-1;
                    bt=p;
                    continue;
                }
            }
            break;
        }
    }
}

void init(void){
    int i;
    int c;
    treePool = newMemPool(sizeof(Bst), "treePool");
    stringPool = newMemPool(1, "stringPool");
    docPool = newMemPool(sizeof(Il), "docPool");
    
    for (i=0;i<256;i++){
        c=(i=='_');
        c|=(i>='0'&&i<='9');
        c|=(i>='A'&&i<='Z');
        c|=(i>='a'&&i<='z');
        allowed[i]=c;
    }
    for(i=0;i<M16;i++){
        tree[i]=NULL;
    }
}

void processBuffer(int r, int *l){
    Bst**bts=NULL;
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
                int k;
                readB[ll]=0;
                sp=sp>>32;
                k=(int)(sp>>8);
                bts=&tree[k];
                /*if (k==8652){
                    printf("%llu\n",sp-567020188);
                }*/
                insert(bts,readB,(U)sp);
            }
            ll=0;
            sp=lo;
        }
    }
    *l=ll;
}

void rdump(Bst * t, int d, char a){
    int i = 0;

    if(t!=NULL){
        if (d>0){
            trail[d-1]=a;
        }
        rdump(t->ch[0], d+1, '<');
        for (i=0;i<d;i++){
            printf("%c",trail[i]);
        }
        printf("%s,%d\n",t->term,t->bal);
        rdump(t->ch[1], d+1, '>');
    }
}

void dumpTree(Bst * bt){
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
                printf("(%08x) %s\n",bt->hash,bt->term);
                bt=bt->ch[1]; /* visit right child */
            }
        }
    }
}

void dump(void){
    int i = 0;

    for(i=0;i<M16;i++){
        rdump(tree[i],0,'\0');
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

void intinsert(int x, Bst** t){
    char q[16];
    sprintf(q,"%d",x);
    printf("\n---------%d\n",x);
    insert(t,q,x);
    rdump(*t,0,'\0');
}

void test(void){
    Bst *t = NULL;
    int k[]={3,24,21,20,2,19,18,14,12,11,1,16,15,6,5,17,7,25,8,4,13,10,23,26,22,9};
    int i=0;
    for(i=0;i<26;i++){
        intinsert(k[i],&t);
    }
}

int main (int argc, char ** argv){
    init();
    if (argc>1){
        handleFileList(argv[1]);
    } else {
        test();
    }
    free(pool);
    return 0;
}
