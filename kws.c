#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

#define ATLINE {printf("here %d\n",__LINE__); fflush(NULL);}

struct btn{
    void* data;
    struct btn * l;
    struct btn * r;
};

typedef struct btn Btn;
typedef unsigned int Uint;

struct ll {
    void* data;
    struct ll* next;
};

typedef struct ll Ll;

typedef struct {
    char * text;
    int docArraySize;
    int numDocs;
    int * docArray;
} Term;

static char repo[4096];
static Btn* table[65536];
static Btn* docTable[65536];
static Btn* alphaTree;
static Btn* btnStack[65536]; /*watch for unbalanced trees ...*/
static Btn docFilterPool[16777216];
static int docFilterPoolIndex = 0;
static int allowed[256];
static int docNum=0;

Term * setTerm(char * in){
    Term * t= (Term*)malloc(sizeof(Term));
    int l=strlen(in)+1;
    t->text=malloc(l);
    memcpy(t->text,in,l);
    t->docArray=(int*)malloc(sizeof(int)*128);
    t->docArraySize=128;
    t->numDocs=0;
    return t;
}

Btn* getNextDocFilterPoolBtn(void){
    Btn* d=&(docFilterPool[docFilterPoolIndex++]);
    d->l=NULL;
    d->r=NULL;
    return d;
}


void setAllowed(void){
    int i = 0;
    for(i=0;i<256;i++){
        allowed[i]=0;
    }
    for(i=0;i<26;i++){
        allowed[65+i]=allowed[97+i]=1;
    }
    for(i=0;i<10;i++){
        allowed[i+48]=1;
    }
    allowed[95]=1;
}

void setAllocatedBtnSide(Btn* old, Btn* newBtn, int side){
    if(side>0){
        old->r=newBtn;
    } else {
        old->l=newBtn;
    }
}

void concatenateDocArrays(Btn * target, Btn * source){
    Term * t = (Term*)target->data;
    Term * s = (Term*)source->data;
    int l=t->numDocs+s->numDocs;
    if (l>t->docArraySize){
        t->docArraySize=l+128;
        t->docArray=realloc(t->docArray,t->docArraySize);
    }
    memcpy(&(t->docArray[t->numDocs]),s->docArray,s->numDocs*(sizeof(int)));
    t->numDocs=l;
}

void insertBtn(Btn* root, Btn* tbi){
    Btn * t=root;
    int side = 0;
    int nequal =1;

    while(t->data!=NULL){
        side=strcmp((char*)tbi->data,(char*)t->data);
        if(side ==0){
            nequal=0;
            concatenateDocArrays(t,tbi);
            break;
        }
        if(side<0){
            if(t->l==NULL){
                t->l=tbi;
                break;
            }
            t=t->l;
        } else {
            if(t->r==NULL){
                t->r=tbi;
                break;
            }
            t=t->r;
        }
    }
}

Btn* createBtn(void* inData){
    Btn * d=(Btn*)malloc(sizeof(Btn));
    d->l=NULL;
    d->r=NULL;
    d->data=inData;
    return d;
}

int fnv(char* p){
    Uint ret=2166136261u;
    Uint c;
    while((c=(Uint)*p++)){
        ret^=c;
        ret*=16777619u;
    }
    return (int)(ret^(ret>>16))&65535;
}

void docUnik(char* inTerm){
    int h=fnv(inTerm);
    Btn * t;
    Term* testTerm;
    int side = 0;
    int nequal =1;
    if(docTable[h] == NULL){
        docTable[h]=getNextDocFilterPoolBtn();
    }
    t=docTable[h];
    while(t->data!=NULL){
        testTerm=(Term*)t->data;
        side=strcmp(inTerm,testTerm->text);
        if(side ==0){
            nequal=0;
            break;
        }
        if(side<0){
            if(t->l==NULL){
                t->l=getNextDocFilterPoolBtn();
            }
            t=t->l;
        } else {
            if(t->r==NULL){
                t->r=getNextDocFilterPoolBtn();
            }
            t=t->r;
        }
    }
    if(nequal){
        t->data=(void*) setTerm(inTerm);
    }
}

void initTable(void){
    int i = 0;
    for(i=0;i<65536;i++){
        table[i] = NULL;
        docTable[i] = NULL;
    }
}

void addDocToTerm(Term* t){
    if(t->numDocs>t->docArraySize-2){
        t->docArraySize+=128;
        t->docArray=(int *)realloc((void*)t->docArray,t->docArraySize);
    }
    t->docArray[t->numDocs++]=docNum;
}

void pushTermInAllTerms(char * inTerm, int hashIndex){
    printf("%08x %s\n", hashIndex,inTerm);fflush(NULL);
    Btn * t;
    int side = 0;
    int nequal =1;
    Term* newTerm;
    Term* testTerm;
    if(table[hashIndex] == NULL){
        newTerm=setTerm(inTerm);
        table[hashIndex]=createBtn((void*)newTerm);
    } else {
        t=docTable[hashIndex];
        while(t->data!=NULL){
            testTerm=(Term*)t->data;
            side=strcmp(inTerm,testTerm->text);
            if(side ==0){
                addDocToTerm(testTerm);
                break;
            }
            if(side<0){
                if(t->l==NULL){
                    newTerm=setTerm(inTerm);
                    t->l=createBtn((void*)newTerm);
                    break;
                }
                t=t->l;
            } else {
                if(t->r==NULL){
                    newTerm=setTerm(inTerm);
                    t->r=createBtn((void*)newTerm);
                    break;
                }
                t=t->r;
            }
        }
        if(nequal){
            t->data=malloc(strlen(inTerm)+1);
            strcpy((char*)t->data,inTerm);
        }
    }
}

void flushDocTermTree(Btn * b, int hashIndex){
    Btn *t =b;
    int searchIndex = 0;
    do{
        while(t!=NULL){
            btnStack[searchIndex++]=t;
            pushTermInAllTerms((char*)t->data,hashIndex);
            free(t->data);
            t=t->l;
        }
        searchIndex--;
        if(searchIndex<0){
            break;
        }
        t=btnStack[searchIndex]->r;
    }while(1);

}

void flushDocTerms(void){
    int i;
    for(i=0;i<65536;i++){
        flushDocTermTree(docTable[i],i);
    }
}

void chewFile(char * fname){
    int c;
    char buff[4096];
    int i = 0;
    FILE * f=fopen(fname,"r");
    if(f !=NULL){
        docFilterPoolIndex=0;
        do{
            c=fgetc(f);
            if(feof(f)){
                break;
            }
            if(allowed[(int)((unsigned char)c)]){
                buff[i++]=(char)c;
            } else {
                buff[i]=0;
                if(i>1){
                    docUnik(buff);
                }
                i=0;
            }
        }while(1);
        fclose(f);
    }
    flushDocTerms();
}

void initDocFilterPool(void){
    int i = 0;
    for (i=0;i<16777216;i++){
        docFilterPool[i].data=NULL;
    }
}

void init(void){
    setAllowed();
    initDocFilterPool();
    initTable();
}
void parseArgs(int argc, char ** argv){
    int i = 0;
    for (i=0;i<argc;i++){
        if(strcmp(argv[i],"-w")==0){
            strcpy(repo,argv[i+1]);
            i++;
        }
    }
}

int main (int argc, char ** argv){
    parseArgs(argc, argv);
    init();
    chewFile(argv[1]);
    return 0;
}
