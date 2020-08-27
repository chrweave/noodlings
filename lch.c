#include<stdio.h>

typedef unsigned __int128 U128;
typedef unsigned long long U64;
typedef unsigned int U;

U128 a,b,c;
void init(void){
    int i;
    U
            pb[]={0xf8177e08,0x9100d65e,0x02fb4a94,0xe5dcc50a},
            pc[]={0xf1e441c0,0x7efb5761,0xf9fc76df,0x29c75871},
            pa[]={0xba6a677d,0x85e295d2,0x0d152a5f,0xe1d281bd};


    for(i=0;i<4;i++){
        a=(a<<32)|pa[i];
        b=(b<<32)|pb[i];
        c=(c<<32)|pc[i];
    }
}
int main (int argc, char ** argv){
    FILE* f;
    U128 l;
    U128 h;
    int i,j;
    U128 q;
    U64 o;
    char buff [1024];
    char * r;
    if(argc>1 && (f=fopen(argv[1],"r"))!=NULL){
        init();
        do{
            i=fscanf(f,"%s",buff);
            if(feof(f)){
                break;
            }
            r=buff;
            h=b;
            while((j=(U128)(*r++))){
                h ^= j;
                h *= a;
                h += c;
            }
            q=h^(h>>37);
            o=(U64)q;
            j=59u-(U)(b>>123);
            o=(o<<j)|(o>>(64-j));
            printf("%016llX %s\n",o,buff);
        }while(1);
    }
}
