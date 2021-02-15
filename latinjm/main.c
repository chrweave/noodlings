#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int rc4ArrarySize = 0;
int * rc4Array;
int cubeDim;
char *** cube;

makeMultiDimBlock(size_t chunkSize, int numDims, int *dimSizes){
    int numElements[200];
    int i = 0;
    int j = 0;
    int k = 1;
    int blocSize = 0;
    int elementSize = sizeof (void*);
    void* tempAddress;
    void* target;
    void* bloc;

    memset(&numElements[0], 0, 200 * sizeof (int));
    for (i = 0; i < numDims; i++){
        if (i == numDims - 1){
            elementSize = chunkSize;
        }
        k *= dimSizes[i];
        numElements[i] = k;
        blocSize += numElements[i] * elementSize;
    }
    bloc = malloc(blocSize);
    memset(bloc, 0, blocSize);
    target = bloc;
    tempAddress = (void*) ((ptrdiff_t) bloc + (ptrdiff_t) (sizeof (void*) * numElements[0]));
    elementSize = sizeof (void*);
    for (i = 1; i < numDims; i++){
        if (i == numDims - 1){
            elementSize = chunkSize;
        }
        for (j = 0; j < numElements[i - 1]; j++){
            memcpy(target, &tempAddress, sizeof (void*));
            tempAddress = (void*) ((ptrdiff_t) tempAddress + (ptrdiff_t) (elementSize * dimSizes[i]));
            target = (void*) ((ptrdiff_t) target + (ptrdiff_t) sizeof (void*));
        }
    }
    return bloc;
}

void parseArgs(char ** argv){
    cubeDim=atoi(argv[1]);
    cube=(char***) makeMultiDimBlock(sizeof(char),3,[cubeDim,cubeDim,cubeDim]);
}

int main(int argc, char ** argv){
    if(argc > 2){
        parseArgs(argv);
    }
    return 0;
}
