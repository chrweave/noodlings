#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "rc4gen.h"

Rc4gen::Rc4gen(int size, char * seed) {
  int i = 0;
  int pl = strlen(seed);
  x = 0;
  y = 0;
  l = size;
  a = NULL;
  a = new int[l];
  if (a != NULL) {
    for (i = 0; i < l; i++) {
      a[i] = i;
    }
    for (i = 0; i < l; i++) {
      y += ((256 + (int) seed[i % pl]) % 256);
      pump();
    }
    for (i = 0; i < 3 * l; i++) {
      pump();
    }
  }
}

Rc4gen::~Rc4gen() {
  if (a != NUL) {
    delete[] a;
  }
}

int Rc4gen::getNext() {
  pump();
  t += a[x];
  t %= l;
  return a[t];
}

int * Rc4gen::getPerm() {
  int * ret = NULL;
  ret = new int[l];
  if (ret != NULL) {
    int i = 0;
    for (i = 0; i < l; i++) {
      ret[i] = a[i];
    }
  }
  return ret;
}

void Rc4gen::pump() {
  x++;
  x %= l;
  t = a[x];
  y += t;
  y %= l;
  a[x] = a[y];
  a[y] = t;
}
