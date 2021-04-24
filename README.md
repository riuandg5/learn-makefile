# learn-makefile

## What is a Makefile?
A Makefile contains a set of tasks to be executed by the [GNU make](https://www.gnu.org/software/make/) utility.

GNU make is a build automation tool that automatically builds executable programs and libraries from source code by reading files called Makefiles which specify how to derive the target program.

## Why Makefile?
Building an executable from a single source code file is not the point of discussion here. We are talking about projects which follow the multi-file programming concept of having multiple source code files, dependencies, libraries, etc. Managing such projects from small to medium or large size need multiple sets of instructions to complete a build process and here comes in action the Makefile.

Makefile helps in grouping these sets of instructions in a proper fashion so that we can focus more on writing code than on building it. Other than just building executables, we can write Makefiles to perform tests, analyze codes, cleanup, etc. with the help of other utilities of course.