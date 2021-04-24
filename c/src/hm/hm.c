#include "hm.h"

int harmonic_mean(float *n1, float *n2, float *am)
{
    *am = 2 * (*n1 * *n2) / (*n1 + *n2);

    return 0;
}