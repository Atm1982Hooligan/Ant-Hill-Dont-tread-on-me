CC=gcc
CFLAGS=-Wall -g -pedantic

.PHONY: clean_object clean_exe clean

all: test_count

test_count: test_count.o count.o libstack.a
	gcc -o $@ test_count.o count.o -L. -lstack

count.o: count.c count.h stack.h types.h
	$(CC) $(CFLAGS) -c $< -o $@

test_count.o: test_count.c count.h stack.h types.h
	$(CC) $(CFLAGS) -c $< -o $@

clean_object:
	rm -f *.o

clean_exe :
	rm -f test_count

clean: clean_object clean_exe