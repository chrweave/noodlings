#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>


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

int main()
{
    printf("Hello World!\n");
    return 0;
}
