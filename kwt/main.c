#include <stdio.h>
#include <stdlib.h>

/* <macros> */
#define MEG 1048576
/* </macros> */

/* <structureTypes> */
struct _al{
    void* data;
    struct _al * next;
};
typedef struct _al AbstractList;

struct _at{
    void* data;
    struct _at * left;
    struct _at * right;
};
typedef struct _at AbstractTree;

struct _av{
    void * data;
    void * current;
    int size;
};

typedef struct _av AbstractVector;

struct _ep{
    void ** pointerPool;
    void * data;
    int datumSize;
    int poolSize;
    int current;
};

typedef struct _ep ExpandingPool;
/* </structureTypes> */


void readFileList(char * fname);
long * getFilePointersForStartOfFileNames(FILE* f);
void setTreeChild(AbstractTree * parent, AbstractTree * child, int selector);
void flushList(AbstractList * a);
ExpandingPool * getExpandingPool(int inDatumSize);
void * getDatumFromExpandingPool(ExpandingPool * ep);
void doubleExpandingPool(ExpandingPool * ep);
void initAllowed(void);

/* <globalVariables> */
int allowed[256];
/* </globalVariables> */

void initAllowed(void){
    int i = 0;
    for(i=0;i<256;i++){
        int c = 0;
        c = c || (i > 47 && i < 58);
        c = c || (i > 64 && i < 91);
        allowed[i] = c || (i > 96 && i < 123);
    }
}


ExpandingPool * getExpandingPool(int inDatumSize){
    ExpandingPool * ep =(ExpandingPool*)malloc(sizeof(ExpandingPool));
    int i = 0;
    char * harvester = NULL;
    ep->datumSize=inDatumSize;
    ep->poolSize=MEG;
    ep->current = 0;
    ep->data=malloc(MEG*inDatumSize);
    ep->pointerPool=malloc(sizeof(void*)*MEG);
    harvester=(char*)ep->data;
    for(i=0;i<MEG;i++){
        ep->pointerPool[i]=harvester;
        harvester+=ep->datumSize;
    }
    return ep;
}

void doubleExpandingPool(ExpandingPool * ep){
    char * harvester = NULL;
    int i = 0;
    ep->poolSize*=2;
    ep->data=realloc(ep->data,ep->poolSize*ep->datumSize);
    ep->pointerPool=realloc(ep->pointerPool,sizeof(void*)*ep->poolSize);
    harvester=ep->data;
    for(i=0;i<ep->poolSize;i++){
        ep->pointerPool[i]=harvester;
        harvester+=ep->datumSize;
    }
}

void * getDatumFromExpandingPool(ExpandingPool * ep){
    void * ret=ep->pointerPool[ep->current];
    ep->current++;
    if(ep->current>ep->poolSize-16){
        doubleExpandingPool(ep);
    }
    return ret;
}


void flushList(AbstractList * a){
    AbstractList * t=a;
    AbstractList *o=a;
    while (t!=NULL){
        if(t->data!=NULL){
            free(t->data);
        }
        o=t;
        t=t->next;
        free(o);
    }
}


void setTreeChild(AbstractTree * parent, AbstractTree * child, int selector){
    if (selector){
        parent->left=child;
    } else {
        parent->right=child;
    }
}



long * getFilePointersForStartOfFileNames(FILE* f){
    long * ret=NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    long p = ftell(f);


    while ((nread = getline(&line, &len, f)) != -1) {
        printf("%ld\n", p);
        p = ftell(f);
        printf("%s@@@",line);
    }
    return ret;
}

void readFileList(char * fname){
    FILE * f=NULL;
    f=fopen(fname,"rb");
    if(f!=NULL){
        getFilePointersForStartOfFileNames(f);
    }
}

int main(int argc, char ** argv)
{
    if(argc>1){
        readFileList(argv[1]);
    }
}
