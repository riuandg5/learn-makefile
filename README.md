# learn-makefile

## What is a Makefile?
A Makefile contains a set of tasks to be executed by the [GNU make](https://www.gnu.org/software/make/) utility.

GNU make is a build automation tool that automatically builds executable programs and libraries from source code by reading files called Makefiles which specify how to derive the target program.

## Why Makefile?
Building an executable from a single source code file is not the point of discussion here. We are talking about projects which follow the multi-file programming concept of having multiple source code files, dependencies, libraries, etc. Managing such projects from small to medium or large size need multiple sets of instructions to complete a build process and here comes in action the Makefile.

Makefile helps in grouping these sets of instructions in a proper fashion so that we can focus more on writing code than on building it. Other than just building executables, we can write Makefiles to perform tests, analyze codes, cleanup, etc. with the help of other utilities of course.

## Example

![GitHub Workflow Status](https://img.shields.io/github/workflow/status/riuandg5/learn-makefile/C%20CI?style=for-the-badge) ![GitHub issues](https://img.shields.io/github/issues/riuandg5/learn-makefile?style=for-the-badge) ![GitHub](https://img.shields.io/github/license/riuandg5/learn-makefile?style=for-the-badge)

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

### Makefile v1
```Makefile
# default make target
build:
	gcc main.c src/am.c src/gm.c src/hm/hm.c -Iinc -o main.out -lm

run:
	./main.out

clean:
	rm -f main.out
```

#### Output:
```shell
⟩ make
gcc main.c src/am.c src/gm.c src/hm/hm.c -Iinc -o main.out -lm

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
├── main.out
└── Makefile

4 directories, 10 files

⟩ make run
./main.out
AM of 4.000000 and 9.000000 = 6.500000
GM of 4.000000 and 9.000000 = 6.000000
HM of 4.000000 and 9.000000 = 5.538462

⟩ make clean
rm -f main.out

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
* We invoked the `build` target which compiles the `main.out` program. It is the same as we would have done it in the shell using the same `gcc` command.
* We invoked the `run` target which just executes the `main.out` program.
* We invoked the `clean` target which just deletes the `main.out` program.

#### Learning:
* Writing standalone rules in a Makefile:
  ```Makefile
  target:
    recipe
  ```

  `target`: name of the rule which can be invoked by writing `make target` in the shell.

  `recipe`: these are the instructions to run when the target is invoked.

* Try yourself
  
  Write this into a Makefile and call `make my_target` in the shell.
  ```Makefile
  my_target:
    echo done my_target
  ```

* We can define many rules in a Makefile.

* By default GNU make processes the rule it encounters first when reading a Makefile from top to bottom.

* By default GNU make finds a Makefile to process in the current working directory. For other options like mentioning the directory to look into (`make -C dir_name`), mentioning the file itself(`make -f makefile_name`), etc. see `make --help` in the shell.

#### Limitations to v1:
* It is not automation at all. We have to edit the `build` recipe whenever we add or remove new files to the `src` folder.
* It does not track changes to the files and builds from scratch every time the `build` target is invoked.
* `run` target cannot be invoked before invoking `build` target successfully.

### Makefile v2
```Makefile
# default make target
build: main.c src/am.c src/gm.c src/hm/hm.c
	gcc $^ -Iinc -o main.out -lm

run: build
	./main.out

clean:
	rm -f main.out
```

#### Output:
```shell
⟩ make clean
rm -f main.out

⟩ make run
gcc main.c src/am.c src/gm.c src/hm/hm.c -Iinc -o main.out -lm
./main.out
AM of 4.000000 and 9.000000 = 6.500000
GM of 4.000000 and 9.000000 = 6.000000
HM of 4.000000 and 9.000000 = 5.538462
```
* We invoked the `clean` target to remove the `main.out` program.
* We invoked the `run` target directly which invoked the `build` target as it depends on `build` target to compile the `main.out` program first and then executes it.

#### Learning:
* Writing dependent rules in a Makefile:
  ```Makefile
  target: dependencies or pre-requisites
    recipe
  ```

  `target`: name of the rule which can be invoked by writing `make target` in the shell.

  `dependencies`: things on which our target depends.

  `recipe`: these are the instructions to run only when the target is invoked and all dependencies exist or prerequisites fulfill.

* A dependency of a target can be in itself a target. If a dependency exists or fulfills the pre-requisites then the main target recipe is processed directly else the dependency target is first invoked, processing its recipes and then the main target recipe is processed.

* Try yourself

  Write this into a Makefile and call `make my_target` in shell.
  ```Makefile
  # default make target
  my_target: my_dependency
    echo done my_target
  
  my_dependency:
    echo done my_dependency
  ```

* `$^` is an automatic variable which has the names of all the prerequisites, with spaces between them. If you list a prerequisite more than once for a target, the value of `$^` will contain just one copy of the name.

* Try yourself

  Write this into a Makefile and call `make my_target` in shell.
  ```Makefile
  # default make target
  my_target: dependency_1 dependency_2 dependency_3
    echo done my_target after completing $^
  
  dependency_1:
    echo done dependency_1

  dependency_2:
    echo done dependency_1

  dependency_3:
    echo done dependency_1
  ```

#### Limitations to v2:
* It is still not automated. We have to edit the `build` dependency whenever we add or remove new files to the `src` folder. Even if we add more include directories we have to edit the recipe of `build` target specifying more include paths with `-I` prefix in `gcc` command.
* It still does not track changes to the files and builds from scratch every time the `build` target is invoked.

### Makefile v3
```Makefile
# default make target
build: main.out

main.out: main.c src/am.c src/gm.c src/hm/hm.c
	gcc $^ -Iinc -o $@ -lm

run: build
	./main.out

clean:
	rm -f main.out
```

#### Output:
```shell
⟩ make clean
rm -f main.out

⟩ make
gcc main.c src/am.c src/gm.c src/hm/hm.c -Iinc -o main.out -lm

⟩ make
make: Nothing to be done for 'build'.
```
* We invoked the `clean` target to remove the `main.out` program.
* We invoked the `build` target (by just calling `make` in the shell as it is the default make target) which depends on `main.out` hence invoked the `main.out` target to compile itself using given dependencies (`main.c src/am.c src/gm.c src/hm/hm.c`).
* We again invoked the `build` target which depends on `main.out` hence invoked the `main.out` target but it doesn't run the compiling recipe because none of the dependency has changed.
* Now if we make any changes in dependencies of the `main.out` target then only the compiling recipe will be processed.

#### Learning:
* Writing file name as target name enables dependency tracking.

* `$@` is an automatic variable which has the name of the target of the rule.

* Try yourself

  Write this into a Makefile and call `make my_target` in shell.
  ```Makefile
   # default make target
  my_target: my_dependency
    echo done $@
  
  my_dependency:
    echo done $@
  ```