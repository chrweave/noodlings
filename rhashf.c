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

int main(int argc, char ** argv){
    return 0;
}