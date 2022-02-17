#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<memory.h>

int charLook[256];
int rates[20440];

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

void getRates(char * fname){
  FILE * f = NULL;
  int i = 0;
  char s[4] ={0,0,0,0};
  int r = 0;
  int h = 0;
  for(i=0;i<20440;i++){
    rates[i]=0;
  }
  f = fopen(fname,"r");
  if(f!=NULL){
    while((fscanf(f,"%d %s",&r,s))!=EOF){
      h=threeHash(s);
      rates[h]=r;
    }
  }
}

int main (int argc, char ** argv){
  int i = 0;
  char t[4]={0,0,0,0};
  char *s=argv[1];
  setLookup();
  getRates(argv[1]);
  for(i=0;i<20400;i++){
    printf("%d ",rates[i]);
    if(i%80==79){
      printf("\n");
    }
  }
  return 0;
}
