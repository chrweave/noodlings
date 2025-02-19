#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#define MEG 1048576
#define M16 16777216

class LinkedList{ //to be extended with data
public:
    LinkedList(){next=NULL;}
    LinkedList* next;
};

template<typename T> class Arena:LinkedList{
public:
    Arena<T>(){index=0;}
    ~Arena<T>();
    T* fetch(Arena &a);
private:
    T supply[MEG];
    int index;
};
