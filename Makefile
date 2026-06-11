CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -Iinclude

SRC=$(wildcard src/**/*.c src/*.c)
TESTS=$(wildcard tests/*.c)

all:
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o bin/main

run:
	./bin/main

test:
	mkdir -p bin
	$(CC) $(CFLAGS) $(TESTS) $(filter-out src/main.c, $(SRC)) -o bin/tests
	./bin/tests

clean:
	rm -rf bin/*
