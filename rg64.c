#include<stdio.h>

#define LROT64(x,y) (x<<y)|(x>>(63-y))

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
int main(void){
	int i,j;
	Uint128 q;
	Uint64 o;
	loadUint128(pa,&a);
	loadUint128(pb,&b);
	loadUint128(pc,&c);
	db(a);
	db(b);
	db(c);
	printf("\n\n");
	for(i=0;i<1000;i++){
		b*=a;
		b+=c;
		q=b^(b>>37);
		o=(Uint64)q;
		j=59-(Uint)(b&31u);
		o=LROT64(o,j);
		db64(o);
	}
	return 0;
}
