#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEG 1048576

typedef unsigned long long V;
typedef unsigned int U

struct _bt{
    V hash;
    char* term;
    struct _bt * ch[2];
}
typedef struct _bt T;

V lo=0x768032e13e71e9fbu;
V la=0xf38df1969a680995u;
V lc=0x5686184f5ef9ddb9u;
T* tree
T*stack[65536];
int allowed[256];
long * fileNamePointers;
char readB[MEG];

void init(void){
    int i;
    int c;
    for (i=0;i<256;i++){
        c=(i=='_');
        c|=(i>='0'&&i<='9');
        c|=(i>='A'&&i<='Z');
        c|=(i>='a'&&i<='z');
        allowed[i]=c;
    }
}

void processFile(char* fname){
    FILE* f=NULL;
    int l = 0;
    int c  =0;
    f=fopen(fname,"rb");
    if(f!=NULL){
        while((c=fgetc(f))!=EOF){
            if(allowed(c)){
                readB[l++]=(char)c;
                sp^=c;
                sp*=la;
                sp+=lc;
            } else {
                if(l>1){
                }
            }
        }
    }
}

void processFiles(FILE* f){
    long * fileNamePointers=(long*)malloc(MEG*sizeof(long));
    int max = MEG;
    int numFiles = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    long p = ftell(f);

    while ((nread = getline(&line, &len, f)) != -1) {
        p = ftell(f);
        ret[0]=(long)numFiles;
        ret[1+numFiles++]=p;
        if(numFiles>max-16){
            max*=2;
            ret=(long*)realloc(ret,max*sizeof (long));
        }
        line[nread-1]=0;
        processFile(line);
    }
}

void handleFileList(char * fn){
    FILE * f= NULL;
    f=fopen(fn,"r");
    if(f!=NULL){
        processFiles(f);
        fclose(f);
    }
}

int main (int argc, char ** argv){
    if (argc>1){
        handleFileList(argv[1]);
    }
    return 0;
}
