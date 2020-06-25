#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct dll{
    void* data;
    struct dll * l;
    struct dll * r;
};

typedef struct dll Dll;
typedef unsigned int Uint;

struct ll {
    void* data;
    struct ll* next;
};

typedef struct ll Ll;

typedef struct {
    char * text;
    int hash;
    int docArraySize;
    int numDocs;
    int * docArray;
} Term;

char repo[4096];
Dll* table[65536];
Dll* alphaTree;
int allowed[256];

void setAllowed(void){
    int i = 0;
    for(i=0;i<256;i++){
        allowed[i]=0;
    }
    for(i=0;i<26;i++){
        allowed[65+i]=allowed[97+i]=1;
    }
    for(i=0;i<10;i++){
        allowed[i+48]=1;
    }
    allowed[95]=1;
}

void insertStringDll(Dll* root, Dll* tbi){
}

Dll* createDll(void* inData){
    Dll * d=(Dll*)malloc(sizeof(Dll));
    d->l=NULL;
    d->r=NULL;
    d->data=inData;
    return d;
}

Uint fnv(char* p){
    Uint ret=2166136261u;
    Uint c;
    while(c=(Uint)*p++){
        ret^=c;
        ret*=16777619u;
    }
    return ret;
}

void initTable(void){
    int i = 0;
    for(i=0;i<65536;i++){
        table[i] = NULL;
    }
}

void setString(Term* t, char * in){
    t->text=malloc(strlen(in)+1);
    strcpy((char*)t->text,in);
    t->docArray=(int*)malloc(sizeof(int)*128);
    t->docArraySize=128;
    t->numDocs=0;
}

void chewFile(char * fname){
    int c;
    char buff[4096];
    int i = 0;
    int l = 0;
    FILE * f=fopen(fname,"r");
    if(f !=NULL){
        do{
            c=fgetc(f);
            if(feof(f)){
                break;
            }
            if(allowed[(int)((unsigned char)c)]){
                buff[i++]=(char)c;
            } else {
                buff[i]=0;
                if(i>0){
                    printf("%08x %s",fnv(buff),buff);
                }
                i=0;
            }
        }while(1);
        fclose(f);
    }
}

void init(void){
    setAllowed();
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
    parseArgs(argc, argv);
    init();
    chewFile(argv[1]);
    return 0;
}
