#include <stdio.h>
#include "mean.h"

int main()
{
    float n1 = 6, n2 = 9;
    float am, gm, hm;

    arithmetic_mean(&n1, &n2, &am);
    geometric_mean(&n1, &n2, &gm);
    harmonic_mean(&n1, &n2, &hm);
    
    printf("AM of %f and %f = %f\n", n1, n2, am);
    printf("GM of %f and %f = %f\n", n1, n2, gm);
    printf("HM of %f and %f = %f\n", n1, n2, hm);

    return 0;
}