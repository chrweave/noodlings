#include<stdio.h>
#include<stdlib.h>

typedef unsigned __int128 Uint128;
typedef unsigned long Uint64;
typedef unsigned int Uint;

Uint64
pb[]={0xf8177e08,0x9100d65e,0x02fb4a94,0xe5dcc50a},
pc[]={0xf1e441c0,0x7efb5761,0xf9fc76df,0x29c75871},
pa[]={0xba6a677d,0x85e295d2,0x0d152a5f,0xe1d281bd};

Uint128 a=0u,b=0u,c=0u;

void loadUint128(Uint64 * px, Uint128* x){
	int i;
	*x=0u;
	for(i=0;i<4;i++){
		*x=*x<<32|px[i];
	}
}
void seed (char * x){
	Uint128 i,k = 0u;
	while((i=(Uint128)*x++)){
		k^=i;
		k*=a;
		k+=c;
	}
	b^=k;
}
void init(void){
	loadUint128(pa,&a);
	loadUint128(pb,&b);
	loadUint128(pc,&c);
}
void process(int k){
	int i,j;
	
	for(i=0;i<k;i++){
		b*=a;
		b+=c;
		q=b^(b>>37);
		o=(Uint64)q;
		j=59u-(Uint)(b>>123));
		o=LROT64(o,j)(o<<j)|(o>>(64-j));
		printf("%016llX\n",o);
	}
}
int main(int argc, char ** argv){
	int i,j,k;
	Uint128 q;
	Uint64 o;
	if(argc > 1){
		k=atoi(argv[1]);
		if(argc > 2){
			seed(argv[2]);
		}
	} else {
		k=1000;
	}
	process
	return 0;
}
