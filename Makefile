CC=gcc
CFLAGS=-g -Wall
LIB=./

all: sort comparators

sort: $(LIB)sort.c
	$(CC) $(CFLAGS) -I$(LIB) -c $(LIB)$@.c

comparators: $(LIB)comparators.c
	$(CC) $(CFLAGS) -I$(LIB) -c $(LIB)$@.c
