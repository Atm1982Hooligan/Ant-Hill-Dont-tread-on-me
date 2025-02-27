EXE=anthill 
CFLAGS = -Wall -pedantic -ansi
CC=gcc

all: anthill	

anthill: game_loop.o game.o command.o graphic_engine.o space.o game_actions.o objects.o game_reader.o player.o set.o
	$(CC) -o $@ $^ -lscreen -L.

game_loop.o: game_loop.c
	$(CC) $(CFLAGS) -o $@ -c $< 

game.o: game.c
	$(CC) $(CFLAGS) -o $@ -c $<

command.o: command.c
	$(CC) $(CFLAGS) -o $@ -c $<

graphic_engine.o: graphic_engine.c
	$(CC) $(CFLAGS) -o $@ -c $<

space.o: space.c
	$(CC) $(CFLAGS) -o $@ -c $<

game_actions.o: game_actions.c
	$(CC) $(CFLAGS) -o $@ -c $<

objects.o: objects.c 
	$(CC) $(CFLAGS) -o $@ -c $<

game_reader.o: game_reader.c
	$(CC) $(CFLAGS) -o $@ -c $<

player.o: player.c
	$(CC) $(CFLAGS) -o $@ -c $<

set.o: set.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f anthill *.o
