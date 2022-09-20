#ifndef RC4GEN_H
#define RC4GEN_H
class Rc4gen
{
public:
  Rc4gen (int size, char *seed);
  ~Rc4gen ();
  getNext ();
  getPerm ();
private:
  int l;
  int x;
  int y;
  int t;
  int *a;
  void pump ();
};
#endif
