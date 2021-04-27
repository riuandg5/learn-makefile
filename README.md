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

All the versions of Makefile can be found in the folder named `versions`. Read this documentation further to know about the stepwise evolution.

### C project structure:
```console
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
```console
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
```console
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
```console
⟩ make clean
rm -f main.out

⟩ make
gcc main.c src/am.c src/gm.c src/hm/hm.c -Iinc -o main.out -lm

⟩ make
make: Nothing to be done for 'build'.

⟩ code -r main.c

⟩ git status main.c
On branch main
Your branch is up to date with 'origin/main'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   main.c

no changes added to commit (use "git add" and/or "git commit -a")

⟩ make
gcc main.c src/am.c src/gm.c src/hm/hm.c -Iinc -o main.out -lm

⟩ make run
./main.out
AM of 5.000000 and 9.000000 = 7.000000
GM of 5.000000 and 9.000000 = 6.708204
HM of 5.000000 and 9.000000 = 6.428571
```
* We invoked the `clean` target to remove the `main.out` program.
* We invoked the `build` target (by just calling `make` in the shell as it is the default make target) which depends on `main.out` hence invoked the `main.out` target to compile itself using given dependencies (`main.c src/am.c src/gm.c src/hm/hm.c`).
* We again invoked the `build` target which depends on `main.out` hence invoked the `main.out` target but it doesn't run the compiling recipe because none of the dependency has changed.
* We made a change in `main.c` using VSCode. We changed the value of `n1` to `5`. The modification can be verified by the output of `git status main.c`.
* We again invoked the `build` target which depends on `main.out` hence invoked the `main.out` target and this time it detects a change in dependency and runs the compiling recipe.
* We invoked the `run` target which depends on the `build` target which itself depends on the `main.out` target which is up to date and hence directly processes the recipe of `run` target. You can view the output that the value of `n1` is `5`.

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

#### Limitations to v3:
* It is still not automated. We have to edit the `main.out` dependency whenever we add or remove new files to the `src` folder. Even if we add more include directories we have to edit the recipe of `main.out` target specifying more include paths with `-I` prefix in `gcc` command.
* It tracks changes to the files given in dependency and doesn't build from scratch if no change is detected in them
but a change in a single file leads to re-compilation of other files too.
* Tracking of files inside the `inc` folder is still missing and hence making a change in those files does not invoke compiling recipe.

### Makefile v4
```Makefile
# default make target
build: main.out

# Build executable by linking object files
main.out: main.o src/am.o src/gm.o src/hm/hm.o
	gcc $^ -o $@ -lm

# Compile C source files
%.o: %.c
	gcc -Iinc -MMD -MP -c $< -o $@

# Include dependencies generated for every object file
-include main.d src/am.d src/gm.d src/hm/hm.d

run: build
	./main.out

clean:
	rm -f main.out
	rm -f main.o src/am.o src/gm.o src/hm/hm.o
	rm -f main.d src/am.d src/gm.d src/hm/hm.d
```

#### Output:
```console
⟩ make clean
rm -f main.out
rm -f main.o src/am.o src/gm.o src/hm/hm.o
rm -f main.d src/am.d src/gm.d src/hm/hm.d

⟩ make
gcc -Iinc -MMD -MP -c main.c -o main.o
gcc -Iinc -MMD -MP -c src/am.c -o src/am.o
gcc -Iinc -MMD -MP -c src/gm.c -o src/gm.o
gcc -Iinc -MMD -MP -c src/hm/hm.c -o src/hm/hm.o
gcc main.o src/am.o src/gm.o src/hm/hm.o -o main.out -lm

⟩ make
make: Nothing to be done for 'build'.

⟩ code -r main.c

⟩ git status main.c
On branch main
Your branch is up to date with 'origin/main'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   main.c

no changes added to commit (use "git add" and/or "git commit -a")

⟩ make
gcc -Iinc -MMD -MP -c main.c -o main.o
gcc main.o src/am.o src/gm.o src/hm/hm.o -o main.out -lm

⟩ make
make: Nothing to be done for 'build'.

⟩ code -r inc/am.h

⟩ git status inc/am.h 
On branch main
Your branch is up to date with 'origin/main'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   inc/am.h

no changes added to commit (use "git add" and/or "git commit -a")

⟩ make
gcc -Iinc -MMD -MP -c main.c -o main.o
gcc -Iinc -MMD -MP -c src/am.c -o src/am.o
gcc main.o src/am.o src/gm.o src/hm/hm.o -o main.out -lm

⟩ make run
./main.out
AM of 6.000000 and 9.000000 = 7.500000
GM of 6.000000 and 9.000000 = 7.348469
HM of 6.000000 and 9.000000 = 7.200000
```
* We invoked the `clean` target to remove the `main.out` program, object files (`*.o`) and dependency files (`*.d`).
* We invoked the `build` target (by just calling `make` in the shell as it is the default make target) which depends on `main.out` hence invoked the `main.out` target to compile itself using given dependencies (`main.o src/am.o src/gm.o src/hm/hm.o`). As these object files do not exist so they invoke compilation of C source codes in sequence which generates corresponding object file and dependency file. For example, `src/am.o` invokes `src/am.o` target which depends on `src/am.c` and `src/am.d` and since `src/am.c` exists and `src/am.d` is missing but its error is suppressed by `-` before `include`, the compilation recipe of `src/am.o` is processed which generates `src/am.o` and `src/am.d` After having all object files ready, the linking recipe of `main.out` target is processed.
  ```Makefile
  # Example of src/am.d file
  # It is generated by reading the #include statements of src/am.c

  # Adds *.h as a dependency to *.o file
  # Enables tracking of changes inside the inc folder
  src/am.o: src/am.c inc/am.h

  inc/am.h:
  ```
* We again invoked the `build` target which depends on `main.out` hence invoked the `main.out` target but it doesn't run the linking recipe because none of the dependency (object files `*.o`) has changed. Object files are not changed because none of the C source code files (`*.c`), the dependency files (`*.d`) or the header files (`*.h`) has changed inside the `inc` folder.
* We made a change in `main.c` using VSCode. We changed the value of `n1` to `6`. The modification can be verified by the output of `git status main.c`.
* We again invoked the `build` target which depends on `main.out` hence invoked the `main.out` target and this time it detects a change in `main.o` target which detects a change in `main.c` and hence re-compiles and generates `main.o` and then links all object files to generate `main.out` program.
* We again invoked `build` target and nothing happens as nothing is changed.
* We made a change in `inc/am.h` using VSCode. We just added a comment. The modification can be verified by the output of `git status inc/am.h`.
* We again invoked the `build` target which depends on `main.out` hence invoked the `main.out` target and this time it detects a change in `main.o` and `src/am.o` target as they detect a change in `inc/am.h` and hence re-compiles and generates `main.o` and `src/am.o`, and then links all object files to generate `main.out` program.
* We invoked the `run` target which depends on the `build` target which itself depends on the `main.out` target which is up to date and hence directly processes the recipe of `run` target. You can view the output that the value of `n1` is `6`.

#### Learning:
* Breaking the build process into compiling and linking enables tracking of header files and mainly distributes the dependencies to decrease the load of build process by building only the changed files.

* `%` works like pattern matching and is replaced by the stem. For example `%.c` will match `test.c` and hence `%` is replaced by `test` in `%.c`.

* `$<` is an automatic variable which has the name of the first prerequisite.

* Try yourself

	Write this into a Makefile and call `make my_target` in shell.
	```Makefile
	# default make target
	my_target: dependency_1 dependency_2
		echo first dependency name is $<

	dependency_1:
		echo done dependency_1

	dependency_2:
		echo done dependency_1
	```

* `include some_makefile` includes `some_makefile` inside the current Makefile.

* `-include some_makefile` ignores `some_makefile` if it does not exists without any error.

#### Limitations to v4:
* It is still not automated. We have to edit the `main.out` dependency whenever we add or remove new files to the `src` folder. Even if we add more include directories we have to edit the recipe of `%.o` target specifying more include paths with `-I` prefix in `gcc` command.
* Build process makes `*.o` and `*.d` files inside the `src` folder which is not a good practice as it clutters the `src` folder.

### Makefile v5
```Makefile
# Variable to store name of final executable
PROJECT_NAME = main

# Variable to store all object files
OBJS = main.o src/am.o src/gm.o src/hm/hm.o
# Variable to store all dependency files
DEPS = main.d src/am.d src/gm.d src/hm/hm.d

# Default compiler
CC = gcc
# C preprocessor settings
CPPFLAGS = -MMD -MP
# Linker flags
LDFLAGS = -lm

# Variable to store extension of final executable
EXEC = out
# Variable to store full name of final executable
PROJECT_OUTPUT = $(PROJECT_NAME).$(EXEC)

# default make target
build: $(PROJECT_OUTPUT)

# Build executable by linking object files
$(PROJECT_OUTPUT): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile C source files
%.o: %.c
	$(CC) -Iinc $(CPPFLAGS) -c $< -o $@

# Include dependencies generated from every c source file
-include $(DEPS)

run: build
	./$(PROJECT_OUTPUT)

clean:
	rm -f $(PROJECT_OUTPUT)
	rm -f $(OBJS)
	rm -f $(DEPS)
```

#### Output:
```console
⟩ make clean
rm -f main.out
rm -f main.o src/am.o src/gm.o src/hm/hm.o
rm -f main.d src/am.d src/gm.d src/hm/hm.d

⟩ make
gcc -Iinc -MMD -MP -c main.c -o main.o
gcc -Iinc -MMD -MP -c src/am.c -o src/am.o
gcc -Iinc -MMD -MP -c src/gm.c -o src/gm.o
gcc -Iinc -MMD -MP -c src/hm/hm.c -o src/hm/hm.o
gcc main.o src/am.o src/gm.o src/hm/hm.o -o main.out -lm

⟩ make run
./main.out
AM of 6.000000 and 9.000000 = 7.500000
GM of 6.000000 and 9.000000 = 7.348469
HM of 6.000000 and 9.000000 = 7.200000
```
* We invoked the `clean` target to remove the `main.out` program, object files (`*.o`) and dependency files (`*.d`).
* We invoked the `build` target (by just calling `make` in the shell as it is the default make target) which depends on `main.out` hence invoked the `main.out` target to compile itself using given dependencies (`main.o src/am.o src/gm.o src/hm/hm.o`). As these object files do not exist so they invoke compilation of C source codes in sequence which generates corresponding object file and dependency file. After having all object files ready, the linking recipe of `main.out` target is processed.
* We invoked the `run` target which depends on the `build` target which itself depends on the `main.out` target which is up to date and hence directly processes the recipe of `run` target.

#### Learning:
* Nothing changed but the use of variables made the rules look more generalized.

* `var_name = var_value` is used to assign value to a variable.

* To substitute a variable’s value, `$(var_name)` or `${var_name}` is used.

* When `=` is used to assign values to variables, it is called recursively expanded variable. That is, it can be used to substitute values recursively.

* Try yourself

	Write this into a Makefile and call `make my_target` in shell.
	```Makefile
	foo1 = $(foo2)
	foo2 = $(my_var)

	my_var = hi_var_value

	bar1 = $(my_var)
	bar2 = $(bar1)

	# default make target
	my_target:
		@echo foo1 = $(foo1)
		@echo foo2 = $(foo2)
		@echo my_var = $(my_var)
		@echo bar1 = $(bar1)
		@echo bar2 = $(bar2)
	```

#### Limitations to v5:
* It is still not automated. We have to edit the `OBJS`, `DEPS` variables whenever we add or remove new files to the `src` folder. Even if we add more include directories we have to edit the recipe of `%.o` target specifying more include paths with `-I` prefix in `gcc` command.
* Build process makes `*.o` and `*.d` files inside the `src` folder which is not a good practice as it clutters the `src` folder.

### Makefile v6
```Makefile
# Variable to store name of final executable
PROJECT_NAME = main

# Variable to store name of src folder
SRC_DIR = src
# Variable to store names of include folders
INC_DIRS = inc

# Variable to store path of all sources
SRCS = main.c $(shell find $(SRC_DIR) -name '*.c')
# Variable to store path of all object files mapped from path of all sources
OBJS = $(SRCS:.c=.o)
# Variable to store path of all dependency files mapped from path of all objects
DEPS = $(OBJS:.o=.d)

# Variable to store name of default compiler
CC = gcc
# Variable to store include flags by prefixing -I to include folders
INC_FLAGS = $(addprefix -I,$(INC_DIRS))
# Vriable to store C preprocessor settings
CPPFLAGS = $(INC_FLAGS) -MMD -MP
# Variable to store linker flags
LDFLAGS = -lm

# Variable to store extension of final executable
EXEC = out
# Variable to store full name of final executable
PROJECT_OUTPUT = $(PROJECT_NAME).$(EXEC)

# default make target
build: $(PROJECT_OUTPUT)

# Build executable by linking object files
$(PROJECT_OUTPUT): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile C source files
%.o: %.c
	$(CC) $(CPPFLAGS) -c $< -o $@

# Include dependencies generated from every c source file
-include $(DEPS)

run: build
	./$(PROJECT_OUTPUT)

clean:
	rm -f $(PROJECT_OUTPUT)
	rm -f $(OBJS)
	rm -f $(DEPS)
```

#### Output:
```console
⟩ make clean
rm -f main.out
rm -f main.o src/am.o src/gm.o src/hm/hm.o
rm -f main.d src/am.d src/gm.d src/hm/hm.d

⟩ make
gcc -Iinc -MMD -MP -c main.c -o main.o
gcc -Iinc -MMD -MP -c src/am.c -o src/am.o
gcc -Iinc -MMD -MP -c src/gm.c -o src/gm.o
gcc -Iinc -MMD -MP -c src/hm/hm.c -o src/hm/hm.o
gcc main.o src/am.o src/gm.o src/hm/hm.o -o main.out -lm

⟩ make run
./main.out
AM of 6.000000 and 9.000000 = 7.500000
GM of 6.000000 and 9.000000 = 7.348469
HM of 6.000000 and 9.000000 = 7.200000
```
* We invoked the `clean` target to remove the `main.out` program, object files (`*.o`) and dependency files (`*.d`).
* We invoked the `build` target (by just calling `make` in the shell as it is the default make target) which depends on `main.out` hence invoked the `main.out` target to compile itself using object files. As these object files do not exist so they invoke compilation of C source codes in sequence which generates corresponding object file and dependency file. After having all object files ready, the linking recipe of `main.out` target is processed.
* We invoked the `run` target which depends on the `build` target which itself depends on the `main.out` target which is up to date and hence directly processes the recipe of `run` target.

#### Learning:
* Nothing changed but the values for variables are generated using `functions` and hence no need to mention them manually. This brings automation in true sense.

* A function call resembles a variable reference. It can appear anywhere a variable reference can appear, and it is expanded using the same rules as variable references. A function call looks like this `$(function_name arguments)`. There are many pre-defined functions in GNU make.

* A `shell function` is called using `$(shell command)`, which does command expansion. It takes command as an argument and evaluates to the output of the command by converting each newline to a single space.

* Try yourself

	Write this into a Makefile and call `make my_target` in shell.
	```Makefile
	my_var = $(shell printf "hello\nworld")

	# default make target
	my_target:
		@echo my_var = $(my_var)
	```

* A `addprefix function` is called using `$(addprefix prefix,names)`, which prepended `prefix` to the front of each individual name.

* Try yourself

	Write this into a Makefile and call `make my_target` in shell.
	```Makefile
	my_var = file_a folder_b
	my_new_var = $(addprefix new_,$(my_var))

	# default make target
	my_target:
		@echo my_var = $(my_var)
		@echo my_new_var = $(my_new_var)
	```

* A `substitution reference` is called using `$(my_var:a=b)`, which takes the value of the variable `my_var`, replaces every `a` at the end of a word with `b` in that value, and substitutes the resulting string. It is shorthand for `$(patsubst %a,%b,my_var)` which is `pattern sustitution function`.

* Try yourself

	Write this into a Makefile and call `make my_target` in shell.
	```Makefile
	my_var = file_a folder_b
	my_new_var = $(my_var:a=b)

	# default make target
	my_target:
		@echo my_var = $(my_var)
		@echo my_new_var = $(my_new_var)
	```

#### Limitations to v6:
* Build process makes `*.o` and `*.d` files inside the `src` folder which is not a good practice as it clutters the `src` folder.
* Values assigned to variables using `=` make variables recursively expandable but none of the variables used are called recursively. It also makes GNU make run slower.
* If a file exists with a name of a target name then the target recipe is not processed. For example, if a file named `run` exist then the recipe of a target named `run` in Makefile is not processed because it misunderstands the target name with the file name.

### Makefile v7
```Makefile
# Variable to store name of final executable
PROJECT_NAME := main

# Variable to store name of src folder
SRC_DIR := src
# Variable to store names of include folders
INC_DIRS := inc
# Variable to store name of build folder
BUILD_DIR := build

# Variable to store path of all sources
SRCS := main.c $(shell find $(SRC_DIR) -name '*.c')
# Variable to store path of all object files mapped from path of all sources
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)
# Variable to store path of all dependency files mapped from path of all objects
DEPS := $(OBJS:.o=.d)

# Variable to store name of default compiler
CC := gcc
# Variable to store include flags by prefixing -I to include folders
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
# Vriable to store C preprocessor settings
CPPFLAGS := $(INC_FLAGS) -MMD -MP
# Variable to store warning flags
WARNINGS := -Wall -Wpedantic -Wextra
# Variable to store linker flags
LDFLAGS := -lm

# Variable to store extension of final executable
EXEC := out
# Variable to store full name of final executable
PROJECT_OUTPUT := $(BUILD_DIR)/$(PROJECT_NAME).$(EXEC)

.PHONY: build
# default make target
build: $(PROJECT_OUTPUT)

# Build executable by linking object files
$(PROJECT_OUTPUT): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile C source files
$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(WARNINGS) -c $< -o $@

# Include dependencies generated from every c source file
-include $(DEPS)

.PHONY: run
# Build executable file and run
run: build
	$(PROJECT_OUTPUT)

.PHONY: clean
# Clean all build files
clean:
	rm -rf $(BUILD_DIR)
```

#### Output:
```console
⟩ make clean
rm -rf build

⟩ make
mkdir -p build/
gcc -Iinc -MMD -MP -Wall -Wpedantic -Wextra -c main.c -o build/main.o
mkdir -p build/src/
gcc -Iinc -MMD -MP -Wall -Wpedantic -Wextra -c src/am.c -o build/src/am.o
mkdir -p build/src/
gcc -Iinc -MMD -MP -Wall -Wpedantic -Wextra -c src/gm.c -o build/src/gm.o
mkdir -p build/src/hm/
gcc -Iinc -MMD -MP -Wall -Wpedantic -Wextra -c src/hm/hm.c -o build/src/hm/hm.o
gcc build/main.o build/src/am.o build/src/gm.o build/src/hm/hm.o -o build/main.out -lm

⟩ make run
build/main.out
AM of 6.000000 and 9.000000 = 7.500000
GM of 6.000000 and 9.000000 = 7.348469
HM of 6.000000 and 9.000000 = 7.200000
```
* We invoked the `clean` target to remove the `build` folder.
* We invoked the `build` target (by just calling `make` in the shell as it is the default make target) which depends on `main.out` hence invoked the `main.out` target to compile itself using object files. As these object files do not exist so they invoke compilation of C source codes in sequence which generates corresponding object file and dependency file inside the build folder. After having all object files ready, the linking recipe of `main.out` target is processed.
* We invoked the `run` target which depends on the `build` target which itself depends on the `main.out` target which is up to date and hence directly processes the recipe of `run` target.

#### Learning:
* `var_name := var_value` is used to assign value to a variable like `=`. But when `:=` is used then variable is called simply expanded variable. That is, it cannot be used to substitute values recursively.

* Try yourself

	Write this into a Makefile and call `make my_target` in shell.
	```Makefile
	foo1 := $(foo2)
	foo2 := $(my_var)

	my_var := hi_var_value

	bar1 := $(my_var)
	bar2 := $(bar1)

	# default make target
	my_target:
		@echo foo1 = $(foo1)
		@echo foo2 = $(foo2)
		@echo my_var = $(my_var)
		@echo bar1 = $(bar1)
		@echo bar2 = $(bar2)
	```

* If a file exists with a name of a target name then the target recipe is not processed. So to avoid this naming conflict we use `phony targets`. A `phony target` is declared like `.PHONY: a_phony_target`. When `make a_phony_target` is invoked then it skips checking for a file named `a_phony_target` and always process its recipe.

* A `dir function` is called using `$(dir paths_of_files)`, which extracts the folder paths by removing the file names.

* Try yourself

	Write this into a Makefile and call `make my_target` in shell.
	```Makefile
	my_var = folder/file.a
	my_new_var = $(dir $(my_var))

	# default make target
	my_target:
		@echo my_var = $(my_var)
		@echo my_new_var = $(my_new_var)
	```

* All objects files, dependency files and the final executable file are generated inside the `build` folder which is also known as `out-of-source` building.