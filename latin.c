#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _xl xlist;

struct _xl{
    int r;
    int c;
    int s;
    xlist* prev;
    xlist* next;
};

int lim = 0;
int biglim;
int ** square;
int *  testArray;
xlist * testList;
xlist * xRoot;
int rowNumber;
int rcx=0;
int rcy=0;

void pump(){
    int temp;

    temp=testArray[rcx];
    rcy+=temp;
    rcy%=biglim;
    testArray[rcx]=testArray[rcy];
    testArray[rcy]=temp;
    rcx++;
    rcx%=biglim;
}

void initTestListElement(int i, int j, int k, int l){
    xlist * mine=&(testList[l]);
    int t=testArray[l];
    mine->r=i;
    mine->c=j;
    mine->s=k;
    mine->prev=&(testList[(l+1)%biglim]);
    mine->next=&(testList[(l-1+biglim)%biglim]);
    if(t==0){
        xRoot=mine;
    }
}

int deletionCandidate(xlist * a){
    int ret = 0;
    ret=ret||((a->r==xRoot->r)&&(a->s==xRoot->s));
    ret=ret||((a->r==xRoot->r)&&(a->c==xRoot->c));
    ret=ret||((a->c==xRoot->c)&&(a->s==xRoot->s));
    return ret;
}


void initTestArray(char* pass){
    int i;
    int l=strlen(pass);

    for(i=0;i<biglim;i++){
        rcy+=(int)pass[i%l]+512;
        pump();
    }
    for(i=0;i<biglim;i++){
       pump();
    }

}

void initTestList(void){
    int i;
    int j;
    int k;
    int l=0;

    for(i=0;i<lim;i++){
        for(j=0;j<lim;j+=){
            for(k=0;k<lim;k++){
                initTestListElement(i,j,k,l++);
            }
        }
    }
}


void setSqaure (char* pass){
    initTestArray(pass);
}

void clearSingleVolatile(void* v){
    if(v!=NULL){
        free(v);
        v=NULL;
    }
}

void clearVolatiles(){
    int i;
    for (i=0;i<limi++){
        clearSingleVolatile((void*)square[i]);
    }
    clearSingleVolatile((void*)square);
}

void parseArgs(char ** argv){
    int i;
    int j;
    lim = atoi(argv[1]);
    if(lim >1){
        biglim=lim*lim*lim;
        square=(int**)malloc(sizeof(int*)*lim);
        testArray=(int*)malloc(sizeof(int)*biglim);
        for(i=0;i<lim;i++){
            testArray[i]=i;
            square[i]=(int*)malloc(sizeof(int)*lim);
            for(j=0;j<lim;j++){
                square[i][j]=-2;
            }
        }
        setSqaure(argv[2]);
    }
}

int main (int argc, char ** argv){
    if(argc>2){
        parseArgs(argv);
    }
    return 0;
}
