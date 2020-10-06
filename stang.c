#include<stsio.h>
#include<stdlib.h>

int numSamples;
int numNodes;
double * positions;
double * deltas;
double * momentums;
double bridge;
int bridgeSize;

void parseArguments(char ** argv){
    numSamples=atoi(argv[1]);
    numNodes=atoi(argv[2]);
    bridgeSize=atoi(argv[3]);
    positions=(double*)malloc(sizeof(double)*numNodes);
    deltas=(double*)malloc(sizeof(double)*numNodes);
    momentums=(double*)malloc(sizeof(double)*numNodes);
}
void setInitialConditions(){
}
int main(int argc, char ** argv){
    if(argc > 3 ){
        parseArguments(argv);
    }
    return 0;
}
