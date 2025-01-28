CC = gcc
CFLAGS = -c -Wall -ansi -pedantic -g
LFLAGS = -L. -lscreen

exec_game: game
	valgrind ./game hormiguero.dat

game: game.o game_reader.o command.o game_loop.o graphic_engine.o space.o player.o object.o set.o enemy.o
	$(CC) -o game game.o game_reader.o command.o game_loop.o graphic_engine.o space.o player.o object.o enemy.o set.o $(LFLAGS)

space_test: space_test.o space.o set.o
	$(CC) -ospace_test space_test.o space.o set.o

set_test: set_test.o set.o
	$(CC) -oset_test set_test.o set.o

enemy_test: enemy_test.o enemy.o
	$(CC) -oenemy_test enemy_test.o enemy.o

game.o: game.c game.h game_reader.h
	$(CC) $(CFLAGS) game.c

game_reader.o: game_reader.c game_reader.h types.h space.h command.h
	$(CC) $(CFLAGS) game_reader.c

command.o: command.c command.h
	$(CC) $(CFLAGS) command.c

game_loop.o: game_loop.c graphic_engine.h game.h command.h
	$(CC) $(CFLAGS) game_loop.c

graphic_engine.o: graphic_engine.c game.h graphic_engine.h libscreen.h command.h space.h types.h enemy.h
	$(CC) $(CFLAGS) graphic_engine.c

space.o: space.c set.h space.h
	$(CC) $(CFLAGS) space.c

player.o: player.c player.h
	$(CC) $(CFLAGS) player.c

object.o: object.c object.h
	$(CC) $(CFLAGS) object.c

set.o: set.c set.h
	$(CC) $(CFLAGS) set.c

space_test.o: space_test.c space.h test.h space_test.h
	$(CC) $(CFLAGS) space_test.c

set_test.o: set_test.c set_test.h set.h test.h
	$(CC) $(CFLAGS) set_test.c

enemy_test.o: enemy_test.c enemy_test.h enemy.h test.h
	$(CC) $(CFLAGS) enemy_test.c	

enemy.o: enemy.c enemy.h
	$(CC) $(CFLAGS) enemy.c


.PHONY: clean
clean: 
	rm -f game *.o game space_test set_test enemy_test