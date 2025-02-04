CC = gcc
CFLAGS = -Wall -pedantic -ansi -g -DDEBUG
CLIB = -lscreen -L.

.PHONY: clean all

all: anthill

anthill: command.o game.o game_actions.o game_loop.o graphic_engine.o space.o game_reader.o player.o object.o
	$(CC) -o $@ $^ $(CLIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f anthill *.o