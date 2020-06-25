#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct dll{
    void* data;
    struct dll * l;
    struct dll * r;
};

typedef struct dll Dll;

struct ll {
    void* data;
    struct ll* next;
};

typedef struct ll Ll;

char repo[4096];
Dll* table[65536];
Dll* alphaTree;

void initTable(void){
    int i = 0;
    for(i=0;i<65536;i++){
        table[i]=(Dll*) malloc(sizeof(Dll));
    }
}

void setString(Dll* d, char * in){
    d->data=malloc(strlen(in)+1);
    strcpy((char*)d->data,in);
}

void parseArgs(int argc, char ** argv){
    int i = 0;
    for (i=0;i<argc;i++){
        if(strcmp(argv[i],"-w")==0){
            strcpy(repo,argv[i+1]);
            i++;
        }
    }
}


int main (int argc, char ** argv){

    return 0;
}
