#include<cstdio>
#include<cstdlib>
#include "rc4gen.h"

int main (int argc,char ** argv){
  if(argc>3){
    int v= atoi (argv[1])
    Rc4gen * rc = new Rc4gen(v,argv[2]);
    int i = 0;
    int l=atoi(argv[3]);
    int * pr =rc->getPerm();
    for(i=0;i<l;i++){
      printf("%d ",rc->getNext());
    }
    printf("\n");
    for(i=0;i<v;i++){
      printf("%d",pr[i]%2);
    }
    printf("\n");
  }
}
