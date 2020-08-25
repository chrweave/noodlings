#include<stdio.h>

typedef unsigned long long V;

int main (int argc, char ** argv){
    FILE* f;
    V a=0xE328D93B7C7102DDu;
    V c=0xC96D90E9C729D203u;
    V b;
    V h;
    if(argc>1 && (f=fopen(argv[1],"r"))!=NULL){
        char buff [1024];
        char * q;
        do{
            fscanf(f,"%s",buff);
            if(feof(f)){
                break;
            }
            q=buff;
            h=c;
            while(b=(V)(*q++)){
                h ^= b;
                h *= a;
                h += c;
            }
            printf("%016llX %s\n",h,buff);
        }while(1);
    }
}
