#include<stdio.h>
#include<stdlib.h>

int lim = 0;

int ** square;
int *  testArray;
int rcx;
int rcy;


void setSqaure (char* pass){

}

void parseArgs(char ** argv){
    int i;
    lim = atoi(argv[1]);
    if(lim >1){
        square=(int**)malloc(sizeof(int*)*);
    }
}

int main (int argc, char ** argv){
    if(argc>2){
        parseArgs(argv);
    }
    return 0;
}
