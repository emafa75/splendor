NUM_COLORS ?= 5
NUM_LEVELS ?= 2
NUM_TOKENS ?= 25
MUNIFICENCE_FLAGS = -DNUM_COLORS=$(NUM_COLORS) -DNUM_LEVELS=$(NUM_LEVELS) -DNUM_TOKENS=$(NUM_TOKENS)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MUNIFICENCE_FLAGS)

PROJECT_FILES = project.o builder.o color.o
TEST_FILES = test.o builder.o color.o

all: project


test.o: tst/test.c
	$(CC) -c $(CFLAGS) $<


%.o: src/%.c
	$(CC) -c $(CFLAGS) $<


project: $(PROJECT_FILES)
	$(CC) $(CFLAGS) $(PROJECT_FILES) -o project


test_project: $(TEST_FILES)
	$(CC) $(CFLAGS) $(TEST_FILES) -o test_project

clean:
	rm -f project test_project *.o *~
