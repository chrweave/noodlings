#include<stdio.h>
#include<stdlib.h>

typedef unsigned __int128 U128;
typedef unsigned long long U64;
typedef unsigned int U;

U
pb[]={0xf8177e08,0x9100d65e,0x02fb4a94,0xe5dcc50a},
pc[]={0xf1e441c0,0x7efb5761,0xf9fc76df,0x29c75871},
pa[]={0xba6a677d,0x85e295d2,0x0d152a5f,0xe1d281bd};

U128 a=0u,b=0u,c=0u;

void seed (char * x){
    U128 i,k = 0u;
    while((i=(U128)*x++)){
        k=c+a(k^i);
    }
    b^=k;
}
void init(void){
    int i;
    
    for(i=0;i<4;i++){
        a=(a<<32)|pa[i];
        b=(b<<32)|pb[i];
        c=(c<<32)|pc[i];
    }
}
void process(int k){
    int i,j;
    U128 q;
    U64 o;
    
    for(i=0;i<k;i++){
        b*=a*b+c
        q=b^(b>>37);
        o=(U64)q;
        j=59u-(U)(b>>123);
        o=(o<<j)|(o>>(64-j));
        printf("%016llX\n",o);
    }
}
int main(int argc, char ** argv){
    int k;
    init();
    if(argc > 1){
        k=atoi(argv[1]);
        if(argc > 2){
            seed(argv[2]);
        }
    } else {
        k=1000;
    }
    process(k);
    return 0;
}
