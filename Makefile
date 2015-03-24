CC = gcc
INCLUDE_DIR = ./src/include
CC_FLAGS = -O2 -I$(INCLUDE_DIR)
TEST_SRCS = $(wildcard test/*.c)
TEST_EXES = $(patsubst test/%.c,build/%.exe,$(TEST_SRCS))

.PHONY: all clean test

build/%.exe: test/%.c
	@mkdir -p build
	@$(CC) $(CC_FLAGS) -o $@ $<

test: $(TEST_EXES)

clean:
	@rm -rf build

all: test

