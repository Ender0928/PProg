CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
CLIB = -lscreen -L.

.PHONY: clean all

all: anthill

anthill: command.o game.o game_actions.o game_loop.o graphic_engine.o space.o game_reader.o player.o object.o set.o
	$(CC) -o $@ $^ $(CLIB)

command.o: command.c command.h
	$(CC) -c command.c $(CFLAGS) 

game.o: game.c game.h game_reader.h
	$(CC) -c game.c $(CFLAGS)

game_actions.o: game_actions.c game_actions.h game.h types.h
	$(CC) -c game_actions.c $(CFLAGS)

game_loop.o: game_loop.c 

space.o: space.c space.h
	gcc -c space.c -Wall

player.o: player.c player.h
	gcc -c player.c -Wall

object.o: object.c object.h
	gcc -c object.c -Wall

set.o: set.c set.h
	gcc -c set.c -Wall
clean:
	rm -f anthill *.o