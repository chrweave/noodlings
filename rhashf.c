#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdint.h>

typedef uint64_t U64;

/* Computes the Chi Squared Statistic for arrays of expected and observed values*/
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

U64 hash(U64 * data, U64 multiplier, U64, addend, int rotation, int length){
    int i = 0;
    U64 return_value = 0u;
    int r=rotation%64;   
    int l=0;
    /* ensure 0 <= r < 64 */  
    if (r<0){
        r+=64;
    }
    l=64-r;
    for(i=0;i<length;i++){
        return_value ^= data[i];
        return_value += addend;
        return_value *= multiplier;
        return_value = (return_value >> r)|(return_value << l); /*rorq r in Gnu assembly*/
    }
    for(i=0;i<16;i++){ /*finalize*/
        return_value += addend;
        return_value *= multiplier;
        return_value = (return_value >> r)|(return_value << l); /*rorq r in Gnu assembly*/
    }
    return return_value;
}

/* Computes the binomial probabilities for 64 events with probability 1/2 times a number of experiments*/
void binom64(double * dist, double x){
    int i = 0;
    double d = 0.0;
    double g = log(x);

    g -= 64*log(2);
    g += lgamma(65);
    for(i=0;i<65;i++){
        d = g;
        d -= lgamma((double)(i+1));
        d -= lgamma((double)(65-i));
        dist[i]=exp(d);
    }
}

int main(int argc, char ** argv){
    return 0;
}