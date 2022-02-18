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

void rateTerms(void){
  char t[4]={0,0,0,0};
  char s[8];
  char top[6]={0,0,0,0,0,0};
  int topScore = -1;
  int x;
  int i;
  s[0]=s[6]='.';
  s[8]=0;
  for(s[1]='A';s[1]<='Z';s[1]++){
    for(s[2]='A';s[2]<='Z';s[2]++){
      for(s[3]='A';s[3]<='Z';s[3]++){
        for(s[4]='A';s[4]<='Z';s[4]++){
          for(s[5]='A';s[5]<='Z';s[5]++){
            x=0;
            for(i=0;i<5;i++){
              memcpy(t,&s[i],3);
              x+=threeHash(t);
            }
            if(x>topScore){
              topScore=x;
              memcpy(top,&s[1],5);
              printf("%d %s\n",topScore,top);
            }
          }
        }
      }
    }
  }
  printf("%d %s\n",topScore,top);
}

int main (int argc, char ** argv){
  setLookup();
  getRates(argv[1]);
  rateTerms();
  return 0;
}
