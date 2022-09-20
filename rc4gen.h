class Rc4gen {
  public:
    Rc4gen(int size, char * seed);
    ~Rc4gen();
  private:
    int l;
    int x;
    int y;
    int t;
    int * a;
    void pump();
};
