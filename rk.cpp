#include"rk.h"

int main(int argc, char** argv){
    return 0;
}

template<typename T> Arena<T>::~Arena<T>(){
    Arena<T> * o;
    for (Arena<T> * t=next; t!=NULL;o=t, t=t->next){
        o->next=NULL;
        delete o;
    }
}

template<typename T> T* Arena<T>::fetch(Arena<T> & a){
    T * ret=&supply[index];
    index ++;
    if(index==MEG){
        a->next=new Arena<T>();
        a=a->next;
    }
    return ret;
}
