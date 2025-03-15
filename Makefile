########################################################
CC=gcc
CFLAGS= -g -Wall -ansi -pedantic
EJS = p2_e1a p2_e1b
########################################################
OBJECTSP2E1A = p2_e1a.o utils.o file_utils.o vertex.o
OBJECTSP2E1B = p2_e1b.o utils.o file_utils.o vertex.o
########################################################

all: $(EJS) clear

p2_e1a: $(OBJECTSP2E1A)
	$(CC) $(CFLAGS) -o p2_e1a $(OBJECTSP2E1A) -L. -lstack

p2_e1b: $(OBJECTSP2E1B)
	$(CC) $(CFLAGS) -o p2_e1b $(OBJECTSP2E1B) -L. -lstack

p2_e1b.o: p2_e1b.c utils.h stack.h types.h vertex.h
	$(CC) $(CFLAGS) -c p2_e1b.c

p2_e1a.o: p2_e1a.c utils.h stack.h types.h vertex.h
	$(CC) $(CFLAGS) -c p2_e1a.c

utils.o: utils.c utils.h stack.h types.h
	$(CC) $(CFLAGS) -c utils.c

file_utils.o: file_utils.c file_utils.h types.h
	$(CC) $(CFLAGS) -c file_utils.c

vertex.o: vertex.c vertex.h types.h
	$(CC) $(CFLAGS) -c vertex.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run_e1a:
	@echo ">>>>>>Running p2_e1a"
	./p2_e1a

run_e1b:
	@echo ">>>>>>Running p2_e1b"
	./p2_e1b cities1.txt cities2.txt

runv_e1a:
	@echo ">>>>>>Running p2_e1a with valgrind"
	valgrind --leak-check=full ./p2_e1a

runv_e1b:
	@echo ">>>>>>Running p2_e1b with valgrind"
	valgrind --leak-check=full ./p2_e1b cities1.txt cities2.txt
