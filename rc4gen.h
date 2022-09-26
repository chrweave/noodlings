#ifndef RC4GEN_H
#define RC4GEN_H
class Rc4gen {
    public:
        Rc4gen();
    Rc4gen(int size, char * seed);
    ~Rc4gen();
    int getNext();
    int * getPerm();
    void setState(int size, char * seed);
    private:
        int l;
    int x;
    int y;
    int t;
    int * a;
    void pump();
};
#endif
