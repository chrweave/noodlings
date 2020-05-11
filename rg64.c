#include<stdio.h>
#include<stdlib.h>

#define LROT64(x,y) (x<<y)|(x>>(64-y))

typedef unsigned __int128 Uint128;
typedef unsigned long Uint64;
typedef unsigned int Uint;

Uint pa[]={191,132,149,149,5,13,129,0,77,46,71,130,147,60,221,181};
Uint pb[]={194,47,232,23,93,176,14,23,68,214,163,112,177,0,177,83};
Uint pc[]={66,49,156,139,44,96,160,160,64,2,129,170,205,224,26,107};
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
void loadUint128(Uint * px, Uint128* x){
	int i;
	*x=0u;
	for(i=0;i<16;i++){
		*x=*x<<8|px[i];
	}
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
