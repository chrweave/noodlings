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
    Bintree*(*handleMatch)(Bintree * matchPoint, void * neededData);
}InsertArgs;

void insert(InsertArgs * ia){
    Bintree * t = ia->target;
    while(t != NULL){
        int s= ia->compare(t->data,ia->indata);
    }
}

int main()
{
    printf("Hello World!\n");
    return 0;
}
