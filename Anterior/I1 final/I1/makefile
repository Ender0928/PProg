game: game.o game_reader.o command.o game_loop.o graphic_engine.o space.o player.o object.o
	gcc -o game game.o game_reader.o command.o game_loop.o graphic_engine.o space.o player.o object.o -L. -lscreen -Wall 

game.o: game.c game.h game_reader.h 
	gcc -c game.c -Wall 

game_reader.o: game_reader.c game_reader.h types.h space.h command.h
	gcc -c game_reader.c -Wall 

command.o: command.c command.h
	gcc -c command.c -Wall

game_loop.o: game_loop.c graphic_engine.h game.h command.h
	gcc -c game_loop.c -Wall 

graphic_engine.o: graphic_engine.c game.h graphic_engine.h libscreen.h command.h space.h types.h
	gcc -c graphic_engine.c -Wall

space.o: space.c space.h
	gcc -c space.c -Wall

player.o: player.c player.h
	gcc -c player.c -Wall

object.o: object.c object.h
	gcc -c object.c -Wall





	

.PHONY: clean
clean: 
	rm -f game *.o game