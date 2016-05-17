CC=gcc
CFLAGS=-g -Wall
LIB=./

all: sort test_sort

sort: $(LIB)sort.c
	$(CC) $(CFLAGS) -I$(LIB) -c $(LIB)$@.c

test_sort: $(LIB)sort.o $(LIB)test_sort.c
	$(CC) $(CFLAGS) -I$(LIB) $(LIB)sort.o $@.c -o $@