#include<cstdio>
#include<cstdlib>
#include "rc4gen.h"

class RandTree {
public:
private:
  void flip(int *in, int* out, int size);
  int * old;
  int * vec;
};

void RandTree::flip(int *in, int* out, int size){
  int i = 0;
  for(i=0;i<size;i++){
    out[i]=in[i]*(-1);
  }
}
