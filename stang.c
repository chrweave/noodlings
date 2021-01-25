#include<stdio.h>
#include<stdlib.h>

int numSamples;
int numNodes;
int bridgeSize;
double * samples;
double * positions;
double * deltas;
double * momentums;
double * bridge;

void clearArray(void* ar){
    if(ar!=NULL){
        free(ar);
    }
}

double * getDoubleArray(int size){
    return (double*) malloc (sizeof(double)*size);
}

void setString(void){
    int i = 0;
    for(i=0;i<=numNodes/2;i++){
        positions[i]=(double)i;
        positions[numNodes-1-i]=(double)i;
    }
    for(i=0;i<numNodes;i++){
        printf("%g ",positions[i]);
    }
    printf("\n");
}

void cleanup(void){
    clearArray(positions);
    clearArray(deltas);
    clearArray(momentums);
    clearArray(bridge);
}
void parseArguments(char ** argv){
    numSamples=atoi(argv[1]);
    numNodes=atoi(argv[2]);
    bridgeSize=atoi(argv[3]);   
}
void setInitialConditions(void){
    int i;
    
    positions=getDoubleArray(numNodes);
    deltas=getDoubleArray(numNodes);
    momentums=getDoubleArray(numNodes);
    bridge=getDoubleArray(numNodes);
    setString();
}
int main(int argc, char ** argv){
    if(argc > 3 ){
        parseArguments(argv);
        setInitialConditions();
		cleanup();
    }
    return 0;
}
