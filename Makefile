CC = gcc
INCLUDE_DIR = ./src/include
CC_FLAGS = -g -ggdb -I$(INCLUDE_DIR)
TEST_SRCS = $(wildcard test/*.c)
TEST_EXES = $(patsubst test/%.c,build/%.exe,$(TEST_SRCS))

.PHONY: all clean build

build/%.exe: test/%.c
	@mkdir -p build
	@$(CC) $(CC_FLAGS) -o $@ $<

build: $(TEST_EXES)

clean:
	@rm -rf build

all: build

