#include<stdio.h>
#include<stdlib.h>

#define LROT64(x,y) (x<<y)|(x>>(64-y))

typedef unsigned __int128 Uint128;
typedef unsigned long Uint64;
typedef unsigned int Uint;

Uint64
pb[]={0xf8177e08,0x9100d65e,0x02fb4a94,0xe5dcc50a},
pc[]={0xf1e441c0,0x7efb5761,0xf9fc76df,0x29c75871},
pa[]={0xba6a677d,0x85e295d2,0x0d152a5f,0xe1d281bd};

Uint128 a=0u,b=0u,c=0u;

void db(Uint128 x){
	int i;
	for (i=0;i<128; i++){
		printf("%u",(x>>(127-i))&1u);
	}
	printf("\n");
}
void db64(Uint64 x){
	int i;
	for (i=0;i<64; i++){
		printf("%u",(x>>(63-i))&1u);
	}
	printf("\n");
}
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
int main(int argc, char ** argv){
	int i,j,k;
	Uint128 q;
	Uint64 o,*s;
	if(argc > 1){
		k=atoi(argv[1]);
	} else {
		k=1000;
	}
	loadUint128(pa,&a);
	loadUint128(pb,&b);
	loadUint128(pc,&c);
	s=(Uint64*)malloc(k*64);
	for(i=0;i<k;i++){
		b*=a;
		b+=c;
		q=b^(b>>37);
		o=(Uint64)q;
		j=59u-(Uint)(b>>123));
		printf("%u\n",j);
		o=LROT64(o,j);
		s[k]=o;
		printf("%016llX\n",o);
	}
	db64(o);
	free(s);
	return 0;
}
