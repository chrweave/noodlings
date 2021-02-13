#ifndef _NDALLOC_H
#define _NDALLOC_H
#include <stdlib.h>
#include <memory.h>
#include <stddef.h>
#include <stdarg.h>

//WARNING: Use extremem caution with this class.
//n-D arrays allocated with this will give VALID
//(but wrong) data for MOST overreads and overwrites.

template <class T> class NDAlloc {
public:
    int i;
    void* tempAddress;
    void* bloc;

    NDAlloc() {
        bloc = NULL;
    }

    ~NDAlloc() {
        ;
    }

     void * makeMultiDimBlock(int numDims, ...) {
        int dimSizes[200];
        int numElements[200];
        va_list argp;
        int i = 0;
        int j = 0;
        int k = 1;
        int elementSize = sizeof (void*);
        int blocSize = 0;
        void* tempAddress;
        void* target;

        memset(&dimSizes[0], 0, 200 * sizeof (int));
        memset(&numElements[0], 0, 200 * sizeof (int));
        va_start(argp, numDims);
        for (i = 0; i < numDims; i++) {
            dimSizes[i] = va_arg(argp, int);
            //printf("%d ", dimSizes[i]);
        }
        //printf("\n");
        va_end(argp);
        k = 1;
        elementSize = sizeof (void*);
        for (i = 0; i < numDims; i++) {
            if (i == numDims - 1) {
                elementSize = sizeof (T);
            }
            k *= dimSizes[i];
            numElements[i] = k;
            //printf("%d ", numElements[i]);
            blocSize += numElements[i] * elementSize;
        }
        //printf("--%d\n", blocSize);
        bloc = malloc(blocSize);
        //printf("blocSize = %d\n", blocSize);
        memset(bloc,0,blocSize);
        target = bloc;
        tempAddress = (void*) ((ptrdiff_t) bloc + (ptrdiff_t) (sizeof (void*) * numElements[0]));
        elementSize = sizeof (void*);
        //for (i = 0; i < numDims - 1; i++) {
        for (i = 1; i < numDims; i++) {
            //if (i == numDims - 2) {
            if (i == numDims - 1) {
                elementSize = sizeof (T);
            }
            //for (j = 0; j < numElements[i]; j++) {
            for (j = 0; j < numElements[i - 1]; j++) {
                //printf("target: %d, tempaddress: %d\n", (int) target, (int) tempAddress);
                memcpy(target, &tempAddress, sizeof (void*));
                //tempAddress = (void*) ((ptrdiff_t) tempAddress + (ptrdiff_t) (elementSize * dimSizes[i + 1]));
                tempAddress = (void*) ((ptrdiff_t) tempAddress + (ptrdiff_t) (elementSize * dimSizes[i]));
                target = (void*) ((ptrdiff_t) target + (ptrdiff_t) sizeof (void*));
            }
            //printf("\n");
        }
        return bloc;
    }
   
};
#endif

