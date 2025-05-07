CC = gcc 
CFLAGS = -Wall -pedantic -g -Iinclude
CLIB = -lscreen -Llib
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = include

.PHONY: all clean

all: cosmos test

test: space_test set_test character_test inventory_test link_test player_test

test_all: 
	$(OBJ_DIR)/space_test; \
	$(OBJ_DIR)/set_test; \
	$(OBJ_DIR)/character_test; \
	$(OBJ_DIR)/object_test; \
	$(OBJ_DIR)/inventory_test; \
	$(OBJ_DIR)/link_test; \
	$(OBJ_DIR)/player_test;

doc:
	@if [ ! -d doc ]; then mkdir doc; fi
	doxygen -g Doxyfile
	sed -i 's|^OUTPUT_DIRECTORY.*|OUTPUT_DIRECTORY = doc|' Doxyfile
	sed -i 's|^GENERATE_HTML.*|GENERATE_HTML = YES|' Doxyfile
	sed -i 's|^GENERATE_LATEX.*|GENERATE_LATEX = NO|' Doxyfile
	doxygen Doxyfile

cosmos: $(SRC_DIR)/game_loop.c $(OBJ_DIR)/command.o $(OBJ_DIR)/game.o $(OBJ_DIR)/game_actions.o $(OBJ_DIR)/graphic_engine.o $(OBJ_DIR)/space.o $(OBJ_DIR)/game_reader.o $(OBJ_DIR)/player.o $(OBJ_DIR)/object.o $(OBJ_DIR)/set.o $(OBJ_DIR)/character.o $(OBJ_DIR)/inventory.o $(OBJ_DIR)/link.o $(OBJ_DIR)/game_management.o $(OBJ_DIR)/game_rules.o $(OBJ_DIR)/battle.o
	$(CC) -o $@ $^ $(CLIB)

space_test: $(OBJ_DIR)/space_test.o $(OBJ_DIR)/space.o $(OBJ_DIR)/set.o
	$(CC) -o $@ $^ $(CLIB)

set_test: $(OBJ_DIR)/set_test.o $(OBJ_DIR)/set.o
	$(CC) -o $@ $^ $(CLIB)

character_test: $(OBJ_DIR)/character_test.o $(OBJ_DIR)/character.o
	$(CC) -o $@ $^ $(CLIB)

inventory_test: $(OBJ_DIR)/inventory_test.o $(OBJ_DIR)/inventory.o $(OBJ_DIR)/set.o
	$(CC) -o $@ $^ $(CLIB)

link_test: $(OBJ_DIR)/link_test.o $(OBJ_DIR)/link.o
	$(CC) -o $@ $^ $(CLIB)

player_test: $(OBJ_DIR)/player_test.o $(OBJ_DIR)/player.o $(OBJ_DIR)/inventory.o $(OBJ_DIR)/set.o
	$(CC) -o $@ $^ $(CLIB)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f cosmos
	rm -f space_test set_test character_test inventory_test link_test player_test
	rm -rf $(OBJ_DIR)