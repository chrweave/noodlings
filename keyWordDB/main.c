#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#define PL {printf("at %d\n",__LINE__);fflush(NULL);}
struct _bt{
    void* data;
    struct _bt* child[2];
};

typedef struct _bt Bintree;
typedef struct {
    Bintree * target;
    void * indata;
    int (*compare)(void* a, void* b);
    Bintree* (*allocator)(void *);
    void (*handleMatch)(Bintree * matchPoint);
}InsertArgs;
typedef unsigned int Uint;

int allowed[256];
char wordBuffer[131072];

void initAllowed(void){
    int i = 0;
    for(i=0;i<256;i++){
        int c = 0;
        c = c || (i > 47 && i < 58);
        c = c || (i > 64 && i < 91);
        allowed[i] = c || (i > 96 && i < 123);
    }
}

Bintree * followDown(Bintree * bt, InsertArgs*ia, int childSelector){
    if(bt->child[childSelector]==NULL){
        bt->child[childSelector]=ia->allocator(ia->indata);
    }
    return bt->child[childSelector];
}

void insert(InsertArgs * ia){
    Bintree * t = ia->target;
    while(t != NULL){
        int s= ia->compare(t->data,ia->indata);
        if (s==0){
            if(ia->handleMatch!=NULL){
                ia->handleMatch(t);
            }
            break;
        } else {
            if(s<0){
                t=followDown(t,ia,0);
            } else {
                t=followDown(t,ia,1);
            }
        }
    }
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

void keyWordChomp(char * fname){
    FILE * f = NULL;
    f=fopen(fname,"r");
    if(f != NULL){
        int i = 0;
        int c = 0;
        int h = 0;
        do{
            c=fgetc(f);
            if(feof(f)){
                break;
            }
            if(allowed[c]){
                wordBuffer[i++]=(char)c;
            } else{
                if(i > 1){
                    PL
                            wordBuffer[i]=0;
                    h=fnv(wordBuffer);
                    printf("%08X %s\n",h,wordBuffer);
                }
                i=0;
            }
            if (i==131072){
                wordBuffer[i-1]=0;
                h=fnv(wordBuffer);
                printf("%08X %s\n",h,wordBuffer);
                i=0;
            }
        } while (1);
        fclose(f);
    }
}

int main(int argc, char ** argv){
    if(argc >1){
        keyWordChomp(argv[1]);
    }
    printf("Hello World!\n");
    return 0;
}
