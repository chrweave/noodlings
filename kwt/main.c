#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEG 1048576
#define RBS 8192
#define K64 65536

typedef unsigned long long V;
typedef unsigned int U;

struct _bt{
    U hash;
    int bal;
    char* term;
    struct _bt * ch[2];
};
typedef struct _bt Bst;

V lo=0x768032e13e71e9fbu;
V la=0xf38df1969a680995u;
V lc=0x5686184f5ef9ddb9u;
V sp;
Bst* tree [K64];
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

Bst* getTreeNode(void){
    Bst * r=&(pool[poolIndex++]);
    if(poolIndex>poolLimit-16){
        poolLimit+=MEG;
        pool=realloc(pool,poolLimit);
        if(pool==NULL){
            printf("Out of pool memory.\n");
            exit(1);
        }
    }

    r->ch[0]=r->ch[1]=NULL;
    r->bal=0;
    return r;
}

char * getTerm(char* interm){
    char * r= (char*)malloc(strlen(interm)+1);
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
    prr(*x,"l");
    y->bal=(*x)->bal=0; /* caution another case is needed for deletion.*/
    y->ch[0]=*x;
    (*x)->ch[1]=q;
    *x=y;
}

void rrot(Bst ** x){
    Bst *y= (*x)->ch[0];
    Bst *q= y->ch[1];
    prr(*x,"r");
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


    prr(*x,"rl");
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


    prr(*x,"lr");
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

    //printf("%llu",hash);
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

    pool=(Bst*)malloc(sizeof(Bst)*poolLimit);
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
                k=(int)(sp>>16);
                bts=&tree[k];
                if (k==8652){
                    printf("%llu\n",sp-567020188);
                }
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
        //printf("%s,%d,%08x,%d\n",t->term,t->bal, t->hash,t->hash);
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

    for(i=0;i<K64;i++){
        printf("__%d__\n",i);
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
    //dump();
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
//    char digits[128];
    int i=0;
//    int c;
//    int r=1;
//    int k;
    for(i=0;i<26;i++){
        intinsert(k[i],&t);
    }

    //    insert(&t,"5",5);
    //    insert(&t,"4",4);
    //    insert(&t,"6",6);
    //    insert(&t,"7",7);
    //    insert(&t,"9",9);
    //    insert(&t,"8",8);
    //    rdump(t,0);
    //    lrot(&(t->ch[1]));
    //    printf("--------\n");
    //    rdump(t,0);
    //    rrot(&(t->ch[1]));
    //    printf("--------\n");
    //    rdump(t,0);
    //    rlrot(&(t->ch[1]->ch[1]));
    //    printf("--------\n");
    //    rdump(t,0);
    //    lrot(&t);
    //    printf("--------\n");
    //    rdump(t,0);



//    while(r){
//        while(1){
//            if(feof(stdin)){
//                r=0;
//                break;
//            }
//            c=fgetc(stdin);
//            if(c==10){
//                digits[i]=0;
//                k=atoi(digits);
//                i=0;
//                break;
//            } else {
//                digits[i++]=(char)c;
//            }
//        }
//        if(k<0){
//            break;
//        }
//        insert(&t,digits,k);
//        printf("--------\n");
//        rdump(t,0);
//    }
}

int main (int argc, char ** argv){
    init();
    if (argc>1){
        //annotation=1;
        handleFileList(argv[1]);
    } else {
        test();
    }
    free(pool);
    return 0;
}
