#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct dll{
    void* data;
    struct dll * l;
    struct dll * r;
};

typedef struct dll Dll;


char repo[4096];


void parseArgs(int argc, char ** argv){
    int i = 0;
    for (i=0;i<argc,i++){
        if(strcmp(argv[i],"-w")==0){
            strcpy(repo,argv[i+1]);
            i++;
        }
    }
}


int main (int argc, char ** argv){

    return 0;
}
