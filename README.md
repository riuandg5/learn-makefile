# learn-makefile

## What is a Makefile?
A Makefile contains a set of tasks to be executed by the [GNU make](https://www.gnu.org/software/make/) utility.

GNU make is a build automation tool that automatically builds executable programs and libraries from source code by reading files called Makefiles which specify how to derive the target program.

## Why Makefile?
Building an executable from a single source code file is not the point of discussion here. We are talking about projects which follow the multi-file programming concept of having multiple source code files, dependencies, libraries, etc. Managing such projects from small to medium or large size need multiple sets of instructions to complete a build process and here comes in action the Makefile.

Makefile helps in grouping these sets of instructions in a proper fashion so that we can focus more on writing code than on building it. Other than just building executables, we can write Makefiles to perform tests, analyze codes, cleanup, etc. with the help of other utilities of course.

## Example
We will try to learn and understand the use of Makefile by writing our own for a very simple C project.

All files related to this example can be found in the folder named `c`. We have updated the Makefile from a very basic version to the latest one explaining all the new things introduced.

We haven't stored the older versions of Makefile but you can read this documentation to know about the stepwise evolution or can compare the changes in commits.

### C project structure:
```shell
⟩ tree --dirsfirst
.
├── inc
│   ├── gm
│   │   └── gm.h
│   ├── am.h
│   ├── hm.h
│   └── mean.h
├── src
│   ├── hm
│   │   └── hm.c
│   ├── am.c
│   └── gm.c
├── main.c
└── Makefile

4 directories, 9 files
```
This is our project structure but you can use yours and then tune your Makefile accordingly.

Here we have `main.c` file in the root folder which depends upon `mean.h` which includes all headers `am.h`, `gm.h`, and `hm.h` in one place inside the `inc` folder. These headers contains some function declarations and the definitions of these functions are written in `am.c`, `gm.c`, and `hm.c` inside the `src` folder.

The `gm.h` and `hm.c` files are nested inside one more folder to make sure that our Makefile is capable of operating over complex structures.

`Makefile` is the one in which we will write instructions to build our project.

#### ./main.c
```c
#include <stdio.h>
#include "mean.h"

int main()
{
    float n1 = 4, n2 = 9;
    float am, gm, hm;

    arithmetic_mean(&n1, &n2, &am);
    geometric_mean(&n1, &n2, &gm);
    harmonic_mean(&n1, &n2, &hm);

    printf("AM of %f and %f = %f\n", n1, n2, am);
    printf("GM of %f and %f = %f\n", n1, n2, gm);
    printf("HM of %f and %f = %f\n", n1, n2, hm);

    return 0;
}

```

#### ./inc/mean.h
```c
#ifndef __MEAN_H__
#define __MEAN_H__

#include "am.h"
#include "gm/gm.h"
#include "hm.h"

#endif /* #define __MEAN_H__ */
```

#### ./inc/am.h
```c
#ifndef __AM_H__
#define __AM_H__

int arithmetic_mean(float *n1, float *n2, float *am);

#endif /* #define __AM_H__ */
```

#### ./inc/gm/gm.h
```c
#ifndef __GM_H__
#define __GM_H__

int geometric_mean(float *n1, float *n2, float *gm);

#endif /* #define __GM_H__ */
```

#### ./inc/hm.h
```c
#ifndef __HM_H__
#define __HM_H__

int harmonic_mean(float *n1, float *n2, float *hm);

#endif /* #define __HM_H__ */
```

#### ./src/am.c
```c
#include "am.h"

int arithmetic_mean(float *n1, float *n2, float *am)
{
    *am = (*n1 + *n2) / 2;

    return 0;
}
```

#### ./src/gm.c
```c
#include <math.h>
#include "gm/gm.h"

int geometric_mean(float *n1, float *n2, float *gm)
{
    *gm = sqrt(*n1 * *n2);

    return 0;
}
```

#### ./src/hm/hm.c
```c
#include "hm.h"

int harmonic_mean(float *n1, float *n2, float *am)
{
    *am = 2 * (*n1 * *n2) / (*n1 + *n2);

    return 0;
}
```

We hope you are comfortable enough in the C programming language to understand these simple codes.

So let's now dive into building our project.