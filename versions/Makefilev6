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