#include <cstdlib>
#include <cstdio>
#include <cstring>

Rc4gen::Rc4gen(int size, char * seed){
  int i = 0;
  int pl = strlen(seed);
  x=0;
  y=0;
  l=size;
  a=NULL;
  a=new int[l];
  if(a!=NULL){
    for(i = 0;i<l;i++){
      a[i]=i;
    }
    for(i = 0;i<l;i++){
      y+=((256+(int)seed[i%pl]
    }
  }
}
