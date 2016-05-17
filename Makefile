CC=gcc
CFLAGS=-g -Wall
LIB=./

all: sort test_sort

sort: $(LIB)sort.c
	$(CC) $(CFLAGS) -I$(LIB) -c $(LIB)$@.c
