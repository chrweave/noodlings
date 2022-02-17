#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<memory.h>

int charLook[256];
int rates[20440]

void setLookup(void){
  int i = 0;
  for(i=0;i<256;i++){
    if(i==46){
      charLook[i]=0;
    } else if (65<=i&&90>=i) {
      charLook[i]=i-64;
    } else {
      charLook[i]=-1;
    }
  }
}

int threeHash(char * s){
  int ret = -1;
  if(strlen(s)>2){
    ret=charLook[s[0]];
    ret*=27;
    ret+=charLook[s[1]];
    ret*=27;
    ret+=charLook[s[2]];
  }
  return ret;
}

int main (int argc, char ** argv){
  int i = 0;
  char t[4]={0,0,0,0};
  char *s=argv[1];
  setLookup();
  for(i=0;i<strlen(argv[1])-2; i++){
    memcpy(t,s++,3);
    printf("%s %d\n",t,threeHash(t));
  }
  return 0;
}
