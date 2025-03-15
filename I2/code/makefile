CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
CLIB = -lscreen -L.

.PHONY: clean all

all: anthill

test: space_test set_test

anthill: command.o game.o game_actions.o game_loop.o graphic_engine.o space.o game_reader.o player.o object.o set.o character.o
	$(CC) -o $@ $^ $(CLIB)

space_test: space_test.o space.o set.o
	$(CC) -o $@ $^ $(CLIB)

set_test: set_test.o set.o
	$(CC) -o $@ $^ $(CLIB)

command.o: command.c command.h
	$(CC) -c command.c $(CFLAGS) 

game.o: game.c game.h game_reader.h
	$(CC) -c game.c $(CFLAGS)

game_actions.o: game_actions.c game_actions.h game.h types.h
	$(CC) -c game_actions.c $(CFLAGS)

game_loop.o: game_loop.c

space.o: space.c space.h
	$(CC) -c space.c $(CFLAGS)

player.o: player.c player.h
	$(CC) -c player.c $(CFLAGS)

object.o: object.c object.h
	$(CC) -c object.c $(CFLAGS)

set.o: set.c set.h
	$(CC) -c set.c $(CFLAGS)

character.o: character.c character.h
	$(CC) -c character.c $(CFLAGS)

space_test.o: space_test.c space_test.h test.h
	$(CC) -c space_test.c $(CFLAGS)

set_test.o: set_test.c set_test.h test.h
	$(CC) -c set_test.c $(CFLAGS)

clean:
	rm -f anthill *.o
	rm -f space_test *.o