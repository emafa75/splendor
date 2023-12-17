# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)

# Defines
NUM_COLORS ?= 5
NUM_LEVELS ?= 2
NUM_TOKENS ?= 25
DEBUG ?= 1
PRINT ?= 0

MUNIFICENCE_FLAGS := -DNUM_COLORS=$(NUM_COLORS) -DNUM_LEVELS=$(NUM_LEVELS) -DNUM_TOKENS=$(NUM_TOKENS) -DCOLOR_DISPLAY=$(COLOR_DISPLAY) -DDEBUG=$(DEBUG) -DPRINT=$(PRINT)
CFLAGS := -O0 -Wall -Wextra -std=c99 -g3 $(MUNIFICENCE_FLAGS) -lm # -fstack-usage
LDFLAGS := -lm

PROJECT_TARGET_EXEC := project
TEST_TARGET_EXEC := test
EVALUATOR_TARGET_EXEC := evaluator

BUILD_DIR := ./build
SRC_DIRS := ./src
TST_DIRS := ./tst

PROJECT_MAIN_FILE_NAME := ./src/project.c
TEST_MAIN_FILE_NAME := ./tst/test.c
EVALUATOR_MAIN_FILE_NAME := ./evaluator_src/evaluator.c


# Note the single quotes around the * expressions. The shell will incorrectly expand these otherwise, but we want to send the * directly to the find command.
SRCS := $(shell find $(SRC_DIRS) -name '*.c')
SRCS := $(filter-out $(PROJECT_MAIN_FILE_NAME),$(SRCS))

TST_SRCS := $(shell find $(TST_DIRS) -name '*.c')

# Prepends BUILD_DIR and appends .o to every src file
# As an example, ./your_dir/hello.cpp turns into ./build/./your_dir/hello.cpp.o
PROJECT_OBJS := $(PROJECT_MAIN_FILE_NAME:%=$(BUILD_DIR)/%.o) $(SRCS:%=$(BUILD_DIR)/%.o) 
TEST_OBJS := $(SRCS:%=$(BUILD_DIR)/%.o) $(TST_SRCS:%=$(BUILD_DIR)/%.o)
EVALUATOR_OBJS := $(EVALUATOR_MAIN_FILE_NAME:%=$(BUILD_DIR)/%.o) $(SRCS:%=$(BUILD_DIR)/%.o) 


# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d) $(shell find $(TST_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))


# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CFLAGS := $(CFLAGS) $(INC_FLAGS) # -MMD -MP


all: project

evaluator: $(BUILD_DIR)/$(EVALUATOR_TARGET_EXEC)

project: $(BUILD_DIR)/$(PROJECT_TARGET_EXEC)

test: clean $(BUILD_DIR)/$(TEST_TARGET_EXEC)
	clear
	./test


# The final build step for project
$(BUILD_DIR)/$(PROJECT_TARGET_EXEC): $(PROJECT_OBJS)
	#Compiles the project
	@$(CC) $(PROJECT_OBJS) -o $(PROJECT_TARGET_EXEC) $(LDFLAGS)  # $@


# The final build step for tests
$(BUILD_DIR)/$(TEST_TARGET_EXEC): $(TEST_OBJS)
	#Compiles the tests
	@$(CC) $(TEST_OBJS) -o $(TEST_TARGET_EXEC) $(LDFLAGS) # $@


# The final build step for evaluator
$(BUILD_DIR)/$(EVALUATOR_TARGET_EXEC): $(EVALUATOR_OBJS)
	#Compiles the evaluator
	@$(CC) $(EVALUATOR_OBJS) -o $(EVALUATOR_TARGET_EXEC) $(LDFLAGS)  # $@


clang_custom_lib_support:
	(echo $(INC_FLAGS) | sed 's/ /\n/g') > compile_flags.txt


# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	#compiles $@
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean

color: 
	make clean && DEBUG=0 PRINT=1 make
	clear
	@./project

clean:
	rm -rf $(BUILD_DIR)/*
	rm -f $(PROJECT_TARGET_EXEC) $(TEST_TARGET_EXEC) $(EVALUATOR_TARGET_EXEC)

dep:
	gcc -MM $(SRCS) $(INC_FLAGS)



# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
# -include $(DEPS)
