#include<cstdio>

#include<cstdlib>

#include "rc4gen.h"

class BraceResult {
    public:
        BraceResult() {};
    ~BraceResult() {};
    int initial;
    int terminal;
    int defective;
}

class RandTree {
    public:
        RandTree();
    ~RandTree();
    void getTree(int size, char * seed);
    private:
        void flip(int * in , int * out, int size);
    void setVecsFromRc4gen();
    void clearVecs();
    BraceResult * getBraces();
    int vecSize;
    int curentVector;
    int * vecs[2];
    Rc4gen * rc;
};

RandTree::RandTree() {
    rc = vecs[0] = vecs[1] = NULL;
    vecSize = 0;
    curentVector = 0;
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

int RandTree::setVecsFromRc4gen() {
    int ret = 0;
    int i = 0;
    int * p = rc -> getPerm(); /* allocated by rc->getPerm() */
    if (vecSize > 0) {
        ret = 1;
        for (i = 0; i < vecSize; i++) {
            vecs[0][i] = (p[i] % 2) * 2 - 1;
        }
    }
    delete[] p;
    return ret;
}
BraceResult * RandTree::getBraces() {}

void RandTree::getTree(int size, char * seed) {
    int i;
    int vtest = 1;
    if (rc == NULL) {
        rc = new Rc4gen(size, seed);
        vecSize = size;
    } else {
        rc -> setSate(size, seed);
        vecSize = size;
    }
    for (i = 0; i < 2; i++) {
        vecs[i] = new int[size];
        vtest = vtest && (vecs[i] != NULL);
    }
    if (vtest) {
        setVecsFromRc4gen();
    }
}
