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