#include <math.h>
#include "gm/gm.h"

int geometric_mean(float *n1, float *n2, float *gm)
{
    *gm = sqrt(*n1 * *n2);

    return 0;
}