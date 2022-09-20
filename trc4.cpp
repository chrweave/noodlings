#include<cstdio>
#include<cstdlib>
#include "rc4gen.h"

int main (int argc,char ** argv){
  if(argc>3){
    Rc4gen * rc = new Rc4gen(atoi (argv[1]),argv[2]);
    int i = 0;
    int l=atoi(argv[3]);
    for(i=0;i<l;i++){
      printf("%d ",rc->getNext());
    }
    printf("\n");
  }
}
