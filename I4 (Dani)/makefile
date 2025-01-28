CC = gcc
CFLAGS = -c -Wall -ansi -pedantic -g
LFLAGS = -L. -lscreen

exec_game: game
	valgrind ./game hormiguero.dat

game: game.o game_reader.o command.o game_loop.o graphic_engine.o space.o player.o object.o set.o enemy.o inventory.o link.o
	$(CC) -o game game.o game_reader.o command.o game_loop.o graphic_engine.o space.o player.o object.o enemy.o set.o inventory.o link.o $(LFLAGS)

space_test: space_test.o space.o set.o
	$(CC) -ospace_test space_test.o space.o set.o

set_test: set_test.o set.o
	$(CC) -oset_test set_test.o set.o

enemy_test: enemy_test.o enemy.o
	$(CC) -oenemy_test enemy_test.o enemy.o

inventory_test: inventory_test.o inventory.o set.o
	$(CC) -oinventory_test inventory_test.o inventory.o set.o

player_test: player_test.o player.o inventory.o set.o
	$(CC) -o player_test player_test.o player.o inventory.o set.o

object_test: object_test.o object.o 
	$(CC) -o object_test object_test.o object.o

link_test: link_test.o link.o
	$(CC) -o link_test link_test.o link.o





game.o: game.c game.h game_reader.h
	$(CC) $(CFLAGS) game.c

game_reader.o: game_reader.c game.h game_reader.h types.h space.h command.h
	$(CC) $(CFLAGS) game_reader.c

command.o: command.c command.h
	$(CC) $(CFLAGS) command.c

game_loop.o: game_loop.c graphic_engine.h game.h command.h
	$(CC) $(CFLAGS) game_loop.c

graphic_engine.o: graphic_engine.c game.h graphic_engine.h libscreen.h command.h space.h types.h enemy.h
	$(CC) $(CFLAGS) graphic_engine.c

space.o: space.c set.h space.h
	$(CC) $(CFLAGS) space.c

player.o: player.c player.h inventory.h
	$(CC) $(CFLAGS) player.c

object.o: object.c object.h
	$(CC) $(CFLAGS) object.c

set.o: set.c set.h
	$(CC) $(CFLAGS) set.c

enemy.o: enemy.c enemy.h
	$(CC) $(CFLAGS) enemy.c

inventory.o: inventory.c inventory.h set.h
	$(CC) $(CFLAGS) inventory.c

link.o: link.c link.h
	$(CC) $(CFLAGS) link.c



space_test.o: space_test.c space.h test.h space_test.h
	$(CC) $(CFLAGS) space_test.c

set_test.o: set_test.c set_test.h set.h test.h
	$(CC) $(CFLAGS) set_test.c

enemy_test.o: enemy_test.c enemy_test.h enemy.h test.h
	$(CC) $(CFLAGS) enemy_test.c	

inventory_test.o: inventory_test.c inventory.h inventory_test.h test.h set.h
	$(CC) $(CFLAGS) inventory_test.c

object_test.o: object_test.c object_test.h test.h object.h
	$(CC) $(CFLAGS) object_test.c

player_test.o: player_test.c player_test.h test.h 
	$(CC) $(CFLAGS) player_test.c

link_test.o: link_test.c link_test.h test.h link.h
	$(CC) $(CFLAGS) link_test.c

.PHONY: clean
clean: 
	rm -f game -f *.o -f *test