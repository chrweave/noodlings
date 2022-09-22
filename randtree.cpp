#include<cstdio>
#include<cstdlib>
#include "rc4gen.h"

class RandTree {
public:
  RandTree();
    ~RandTree();
  void getTree(int size, char * seed);
private:
  void flip(int * in , int * out, int size);
  void setVecsFromRc4gen();
  void clearVecs();
  int * vecs[2];
  Rc4gen * rc;
};

RandTree::RandTree() {
  rc = vecs[0] = vecs[1] = NULL;
}
void RandTree::clearVecs() {
  int i = 0;
  for (i = 0; i < 2; i++) {
    if (vecs[i] != NULL) {
      delete[] vecs[i];
      vecs[i] = NULL;
    }
  }
}

RandTree::~RandTree() {
  clearVecs();
}

void RandTree::flip(int * in , int * out, int size) {
  int i = 0;
  for (i = 0; i < size; i++) {
    out[i] = in [i] * (-1);
  }
}
RandTree::void setVecsFromRc4gen(Rc4gen * rc){
}
void RandTree::getTree(int size, char * seed) {  
  int i;
  int vtest = 1;
  if(rc ==NULL){
    rc = new Rc4gen(size, seed);
  } else
    rc->setSate(size,seed);
  }
  for (i = 0; i < 2; i++) {
    vecs[i] = new int[size];
    vtest=vtest&&(vecs[i] !=NULL);
  }
  if(vtest){
    setVecsFromRc4gen();
  }
}
