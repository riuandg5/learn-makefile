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