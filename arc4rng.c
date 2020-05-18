#include <stdio.h>
#include <string.h>
unsigned short b[65536];
int l=65536;
int x=0,y=0,t;
static int q = 0;
void p(void){
    x=(x+1)%l;
    y=(y+b[x])%l;
    t=b[x];
    b[x]=b[y];
    b[y]=t;
    //printf("%d ",q++);
    //fflush(NULL);
}
void d(void){
    p();
    unsigned short m=b[(b[x]+b[y])%l];
    printf("%04x",m);
}
void s(char *k){
    int kl=strlen(k);
    int i;
    for(i=0;i<l;i++){
        b[i]=(unsigned short)i;
    }
    for(i=0;i<l;i++){
        y+=(unsigned short)k[i%kl];
        p();
    }
    //printf("here!");
    for(i=0;i<3*l;i++){
        p();
    }
}
int main(int argc, char ** argv)
{
    int i,j;
    if (argc >1){
        s(argv[1]);
        for(i=0;i<3;i++){
            for(j=0;j<4;j++){
                d();
                d();
                printf(",");
            }
            printf("\n");
        }
    }
    return 0;
}
/*ook*/
