#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double chiSquaredStatistic(double * observed, double * expected, int length){
    int i = 0;
    double diff;
    double diffsq;
    double return_value = 0;
    for (i=0;i<length;i++){
        diff=expected[i]-observed[i];
        diffsq=diff*diff;
        return_value+=diffsq/expected[i];
    }
    return return_value;
}

void binom64(double * dist){
    int i = 0;
    double d = 0.0;
    double g = lgamma(65);
    for(i=0;i<65;i++){
        d = g;
        d -= lgamma((double)(i+1))
        d -= lgamma((double)(65-i));
        dist[i]=exp(d);
    }
}

int main(int argc, char ** argv){
    return 0;
}