CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
CLIB = -lscreen -L.

.PHONY: clean all 

all: anthill  test clean_o

test: space_test set_test character_test inventory_test link_test player_test
	

test_all: 
	./space_test; \
	./set_test; \
	./character_test; \
	./inventory_test; \
	./link_test; \
	./player_test;



doc:
	@if [ ! -d doc ]; then mkdir doc; fi
	doxygen -g Doxyfile
	sed -i 's|^OUTPUT_DIRECTORY.*|OUTPUT_DIRECTORY = doc|' Doxyfile
	sed -i 's|^GENERATE_HTML.*|GENERATE_HTML = YES|' Doxyfile
	sed -i 's|^GENERATE_LATEX.*|GENERATE_LATEX = NO|' Doxyfile
	doxygen Doxyfile



anthill: command.o game.o game_actions.o game_loop.o graphic_engine.o space.o game_reader.o player.o object.o set.o character.o inventory.o link.o
	$(CC) -o $@ $^ $(CLIB)

space_test: space_test.o space.o set.o
	$(CC) -o $@ $^ $(CLIB)

set_test: set_test.o set.o
	$(CC) -o $@ $^ $(CLIB)

character_test: character_test.o character.o
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

player.o: player.c player.h inventory.h
	$(CC) -c player.c $(CFLAGS)

object.o: object.c object.h
	$(CC) -c object.c $(CFLAGS)

set.o: set.c set.h
	$(CC) -c set.c $(CFLAGS)

link.o: link.c link.h
	$(CC) -c link.c $(CFLAGS)
	
inventory.o: inventory.c inventory.h set.h
	$(CC) -c inventory.c $(CFLAGS)

inventory_test: inventory_test.o inventory.o set.o
	$(CC) -o $@ $^ $(CLIB)

link_test: link_test.o link.o
	$(CC) -o $@ $^ $(CLIB)

link_test.o: link_test.c link_test.h test.h
	$(CC) -c link_test.c $(CFLAGS)

inventory_test.o: inventory_test.c inventory_test.h inventory.h
	$(CC) -c inventory_test.c $(CFLAGS)

character.o: character.c character.h
	$(CC) -c character.c $(CFLAGS)

space_test.o: space_test.c space_test.h test.h
	$(CC) -c space_test.c $(CFLAGS)

set_test.o: set_test.c set_test.h test.h
	$(CC) -c set_test.c $(CFLAGS)

character_test.o: character_test.c character_test.h test.h
	$(CC) -c character_test.c $(CFLAGS)

player_test: player_test.o player.o inventory.o set.o
	$(CC) -o $@ $^ $(CLIB)

player_test.o: player_test.c player_test.h test.h
	$(CC) -c player_test.c $(CFLAGS)
clean:
	rm -f anthill *.o
	rm -f space_test *.o
	rm -f set_test *.o
	rm -f character_test *.o
	rm -f inventory_test *.o
	rm -f link_test *.o
	rm -f player_test *.o
	

clean_o:
	rm -f *.o