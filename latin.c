#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int lim = 0;

int ** square;
int *  testArray;
int rowNumber;
int rcx=0;
int rcy=0;

void pump(){
    int temp;

    temp=testArray[rcx];
    rcy+=temp;
    rcy%=lim;
    testArray[rcx]=testArray[rcy];
    testArray[rcy]=temp;
    rcx++;
    rcx%=lim;
}

void churnTestArray(){
    int i;

    for(i=0;i<lim;i++){
       pump();
    }
}

void initTestArray(char* pass){
    int i;
    int l=strlen(pass);

    for(i=0;i<lim;i++){
        rcy+=(int)pass+512;
        pump();
    }
    churnTestArray();

}


void setSqaure (char* pass){
    initTestArray(pass);
}

void parseArgs(char ** argv){
    int i;
    lim = atoi(argv[1]);
    if(lim >1){
        square=(int**)malloc(sizeof(int*)*lim);
        testArray=(int*)malloc(sizeof(int)*lim);
        for(i=0;i<lim;i++){
            testArray[i]=i;
        }
    }
}

int main (int argc, char ** argv){
    if(argc>2){
        parseArgs(argv);
    }
    return 0;
}
