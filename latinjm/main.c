/* C version of Pual Hankin's implementation of Jacobson and Matthews random latin square using an rc4 generator
 * See his original source at: https://blog.paulhankin.net/latinsquares/ */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stddef.h>
#include <string.h>

typedef struct {
    int x;
    int y;
    int z;
} CubePoint;

int rc4ArrarySize = 0;
int * rc4Array = NULL;
int rc4x;
int rc4y;
int cubeDim;
char *** cube = NULL;
int ** xy = NULL;
int ** yz = NULL;
int ** xz = NULL;

void* makeMultiDimBlock(size_t chunkSize, int numDims, int *dimSizes){
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

void initCube(void){
    int cubedims[]={cubeDim,cubeDim,cubeDim};
    int i = 0;
    int j = 0;
    cube=(char***) makeMultiDimBlock(sizeof(char),3,cubedims);
    for(i=0;i<cubeDim;i++){
        for(j=0;j<cubeDim;j++){
            cube[i][j][(i+j)%cubeDim] = 1;
        }
    }
}

void readCube(void){
    int i = 0;
    int j = 0;
    int k = 0;
    for(i=0;i<cubeDim;i++){
        for(j=0;j<cubeDim;j++){
            for(k=0;k<cubeDim;k++){
                if(cube[i][j][k]==1){
                    printf("%4d ",k);
                }
            }
        }
        printf("\n");
    }
}

int pump(void){
    int temp=rc4Array[rc4x];
    rc4y+=temp;
    rc4y%=rc4ArrarySize;
    rc4Array[rc4x]=rc4Array[rc4y];
    rc4Array[rc4y]=temp;
    temp+=rc4Array[rc4x];
    temp%=rc4ArrarySize;
    temp=rc4Array[temp];
    rc4x++;
    rc4x%=rc4ArrarySize;
    return temp;
}

void initRc4Array(char * p){
    int i;
    int l=strlen(p);

    rc4ArrarySize=cubeDim*100;
    rc4x = 0;
    rc4y = 0;
    rc4Array=(int*)malloc(sizeof(int)*rc4ArrarySize);
    for(i=0;i<rc4ArrarySize;i++){
        rc4Array[i]=i;
    }
    for(i=0;i<rc4ArrarySize;i++){
        rc4y+=(int)p[i%l]+256;
        pump();
    }
    for(i=0;i<rc4ArrarySize;i++){
        pump();
    }
}



void clearSingleVolatile(void* v){
    if(v!=NULL){
        free(v);
        v=NULL;
    }
}

void clearVolatiles(void){
    clearSingleVolatile((void*)cube);
    clearSingleVolatile((void*)rc4Array);
}



void randomPoint(CubePoint * a){
    a->x=pump()%cubeDim;
    a->y=pump()%cubeDim;
    a->z=pump()%cubeDim;
}

void initMarginals(void){
    int q[]={cubeDim,cubeDim},i,j,k;

    xy = (int**)makeMultiDimBlock(sizeof(int),2,q);
    yz = (int**)makeMultiDimBlock(sizeof(int),2,q);
    xz = (int**)makeMultiDimBlock(sizeof(int),2,q);
    for(i=0;i<cubeDim;i++){
        for(j=0;j<cubeDim;j++){
            k=i+j;
            k%=cubeDim;
            xy[i][j]=k;
            yz[j][k]=i;
            xz[i][k]=j;
        }
    }
}

void rand2(int a, int b, int * c, int *d ) {
    if (pump()%2 == 0) {
        *c=a;
        *d=b;
    } else {
        *c=b;
        *d=a;
    }
}

void latin(void) {
    int mxy, mxz, myz;
    int m [3];
    int proper = 1;
    int minIter = cubeDim*cubeDim*cubeDim;
    int iter;

    initMarginals();
    for(iter=0;iter<minIter||!proper; iter++){
        int i, j, k, i2, j2, k2, i2_, j2_, k2_;

        if (proper) {
            // Pick a random 0 in the array
            do{
                i = pump()%cubeDim;
                j = pump()%cubeDim;
                k = pump()%cubeDim;
            }while( xy[i][j] == k);
            // find i2 such that [i2, j, k] is 1. same for j2, k2
            i2 = yz[j][k];
            j2 = xz[i][k];
            k2 = xy[i][j];
            i2_=i;
            j2_=j;
            k2_=k;
        } else {
            i = m[0];
            j = m[1];
            k = m[2];
            // find one such that [i2, j, k] is 1, same for j2, k2.
            // each is either the value stored in the corresponding
            // slice, or one of our three temporary "extra" 1s.
            // That's because (i, j, k) is -1.
            rand2(yz[j][k], myz,&i2,&i2_);
            rand2(xz[i][k], mxz,&j2,&j2_);
            rand2(xy[i][j], mxy,&k2,&k2_);
        }

        proper = (xy[i2][j2] == k2);
        if (!proper) {
            m[0]=i2;
            m[1]=j2;
            m[2]=k2;
            mxy = xy[i2][j2];
            myz = yz[j2][k2];
            mxz = xz[i2][k2];
        }

        xy[i][j] = k2_;
        xy[i][j2] = k2;
        xy[i2][j] = k2;
        xy[i2][j2] = k;

        yz[j][k] = i2_;
        yz[j][k2] = i2;
        yz[j2][k] = i2;
        yz[j2][k2] = i;

        xz[i][k] = j2_;
        xz[i][k2] = j2;
        xz[i2][k] = j2;
        xz[i2][k2] = j;
    }
    return xy;
}


void parseArgs(char ** argv){
    cubeDim=atoi(argv[1]);
    initRc4Array(argv[2]);
    //initCube();
    //initMarginals();
    readCube();
    clearVolatiles();
}

int main(int argc, char ** argv){
    if(argc > 2){
        parseArgs(argv);
    }
    return 0;
}
