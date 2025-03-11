EXE=anthill 
CFLAGS = -Wall -pedantic -ansi
CC=gcc

all: anthill	

anthill: game_loop.o game.o command.o graphic_engine.o space.o game_actions.o objects.o game_reader.o player.o set.o character.o
	$(CC) -o $@ $^ -lscreen -L.

game_loop.o: game_loop.c game.h graphic_engine.h command.h game_actions.h game_reader.h
	$(CC) $(CFLAGS) -o $@ -c $< 

game.o: game.c game.h space.h types.h objects.h player.h command.h
	$(CC) $(CFLAGS) -o $@ -c $<

command.o: command.c command.h types.h
	$(CC) $(CFLAGS) -o $@ -c $<

graphic_engine.o: graphic_engine.c graphic_engine.h game.h command.h libscreen.h space.h types.h
	$(CC) $(CFLAGS) -o $@ -c $<

space.o: space.c space.h types.h objects.h set.h
	$(CC) $(CFLAGS) -o $@ -c $<

game_actions.o: game_actions.c game_actions.h game.h command.h types.h
	$(CC) $(CFLAGS) -o $@ -c $<

objects.o: objects.c objects.h types.h
	$(CC) $(CFLAGS) -o $@ -c $<

game_reader.o: game_reader.c game_reader.h game.h space.h types.h
	$(CC) $(CFLAGS) -o $@ -c $<

player.o: player.c player.h types.h
	$(CC) $(CFLAGS) -o $@ -c $<

set.o: set.c set.h types.h
	$(CC) $(CFLAGS) -o $@ -c $<

character.o: character.c character.h types.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f anthill *.o