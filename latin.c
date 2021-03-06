#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void printSquare(void);
typedef struct _xl xlist;

struct _xl{
    int r;
    int c;
    int s;
    int id;
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

void pump(void){
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
    //xlist * mine=&(testList[l]);
    testList[l].r=i;
    testList[l].c=j;
    testList[l].s=k;
    testList[l].id=l;
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
        for(j=0;j<lim;j++){
            for(k=0;k<lim;k++){
                initTestListElement(i,j,k,testArray[l++]);
            }
        }
    }
}

void deleteListElement(xlist * a){
    a->next->prev=a->prev;
    a->prev->next=a->next;
}

void dumpTriples(void){
    xlist * t=xRoot;
    do {
        if(deletionCandidate(t)){
            printf("(%d%d%d) ",t->r,t->c,t->s);
        } else {
            printf(" %d%d%d  ",t->r,t->c,t->s);
        }
        t=t->next;
    }while (t!=xRoot);
    printf("\n");
}

void setSqaure (char* pass){
    xlist* temp;
    initTestArray(pass);
    initTestList();
    xRoot=testList;
    while(xRoot->next != xRoot){
        //dumpTriples();
        square[xRoot->r][xRoot->c]=xRoot->s;
        temp=xRoot->next;
        while(temp!=xRoot){
            if(deletionCandidate(temp)){
                deleteListElement(temp);
            }
            temp=temp->next;
        }
        deleteListElement(xRoot);
        xRoot=xRoot->next;
        //printSquare(); getchar();
    }
}

void clearSingleVolatile(void* v){
    if(v!=NULL){
        free(v);
        v=NULL;
    }
}

void clearVolatiles(void){
    int i;
    for (i=0;i<lim;i++){
        clearSingleVolatile((void*)square[i]);
    }
    clearSingleVolatile((void*)square);
    clearSingleVolatile((void*)testList);
    clearSingleVolatile((void*)testArray);
}

void printSquare(void){
    int i = 0;
    int j = 0;
    for(i=0;i<lim;i++){
        for(j=0;j<lim;j++){
            printf("%3d ",square[i][j]);
        }
        printf("\n");
    }
}

void parseArgs(char ** argv){
    int i;
    int j;
    lim = atoi(argv[1]);
    if(lim >1){
        biglim=lim*lim*lim;
        square=(int**)malloc(sizeof(int*)*lim);
        testArray=(int*)malloc(sizeof(int)*biglim);
        testList=(xlist*)malloc(sizeof(xlist)*biglim);
        for(i=0;i<lim;i++){
            square[i]=(int*)malloc(sizeof(int)*lim);
            for(j=0;j<lim;j++){
                square[i][j]=-2;
            }
        }
        for(i=1;i<biglim-1;i++){
            testArray[i]=i;
            testList[i].next=&(testList[i+1]);
            testList[i].prev=&(testList[i-1]);
        }
        testArray[biglim-1]=biglim-1;
        testArray[0]=0;
        testList[0].next=&(testList[1]);
        testList[0].prev=&(testList[biglim-1]);
        testList[biglim-1].next=&(testList[0]);
        testList[biglim-1].prev=&(testList[biglim-2]);
        setSqaure(argv[2]);
        printSquare();
        clearVolatiles();
    }
}

int main (int argc, char ** argv){
    if(argc>2){
        parseArgs(argv);
    }
    return 0;
}
