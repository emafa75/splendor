NUM_COLORS ?= 5
NUM_LEVELS ?= 2
NUM_TOKENS ?= 25
MUNIFICENCE_FLAGS = -DNUM_COLORS=$(NUM_COLORS) -DNUM_LEVELS=$(NUM_LEVELS) -DNUM_TOKENS=$(NUM_TOKENS)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MUNIFICENCE_FLAGS)

PROJECT_FILES = src/project.o src/builder.o src/color.o
TEST_FILES = tst/test.o src/builder.o src/color.o

all: project

%.o: %.c
	$(CC) -c $(CFLAGS) $<

project: $(PROJECT_FILES)
	$(CC) $(CFLAGS) $(PROJECT_FILES) -o project

test_project: $(TEST_FILES)
	$(CC) $(CFLAGS) $(TEST_FILES) -o test_project

clean:
	rm -f project test_project *.o *~
