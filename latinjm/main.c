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
    temp%=cubeDim;
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

int getXp(int y,int z){
    int ret = -2;
    int i = 0;
    int c = 1;
    for(i=0;c && i<cubeDim;i++){
        if(cube[i][y][z]){
            ret=i;
            c=0;
        }
    }
    return ret;
}

int getYp(int x,int z){
    int ret = -2;
    int i = 0;
    int c = 1;
    for(i=0;c && i<cubeDim;i++){
        if(cube[x][i][z]){
            ret=i;
            c=0;
        }
    }
    return ret;
}

int getZp(int x,int y){
    int ret = -2;
    int i = 0;
    int c = 1;
    for(i=0;c && i<cubeDim;i++){
        if(cube[x][y][i]){
            ret=i;
            c=0;
        }
    }
    return ret;
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

void getPrimes(CubePoint * a, CubePoint * b){
    int c;
    b->x=getXp(a->y,a->z);
    b->y=getYp(a->x,a->z);
    b->z=getZp(a->x,a->y);
    c= (b->x>=0)&&(b->y>=0)&&(b->z>=0);
    if(!c){
        printf("%d %d %d were found as primes.\n",b->x,b->y,b->z);
        clearVolatiles();
        exit(EXIT_FAILURE);
    }
}

void randomPoint(CubePoint * a){
    a->x=pump();
    a->y=pump();
    a->z=pump();
}

void warpCube(void){
    int i =0;
    int l=cubeDim*cubeDim;
    CubePoint rando;
    CubePoint prime;
    CubePoint neg;
    int perfect = 1;

    randomPoint(&rando);
    for(i=0;i<l;i++){
        if(perfect){
            while(cube[rando.x][rando.y][rando.z]==1){
                randomPoint(&rando);
            }
            getPrimes(&rando,&prime);
        } else {
            getPrimes(&neg,&prime);
        }
    }
}

void parseArgs(char ** argv){
    cubeDim=atoi(argv[1]);
    initRc4Array(argv[2]);
    initCube();
    readCube();
    clearVolatiles();
}

int main(int argc, char ** argv){
    if(argc > 2){
        parseArgs(argv);
    }
    return 0;
}
