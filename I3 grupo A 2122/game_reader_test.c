/** 
 * @brief It tests game reader module
 * 
 * @file space_test.c
 * @author Daniel Tirado
 * @version 3.0 
 * @date 04-04-2022
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "game.h"
#include "game_reader.h"
#include "game_reader_test.h"
#include "set.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include "enemy.h"
#include "inventory.h"

#include "test.h"


#define MAX_TESTS 11

/** 
 * @brief Main function for SPACE unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 *  
 */
int main(int argc, char** argv) {

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Space:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_game_reader_load_spaces();
  if (all || test == 2) test2_game_reader_load_spaces();
  if (all || test == 3) test3_game_reader_load_spaces();

  if (all || test == 4) test1_game_reader_load_objects();
  if (all || test == 5) test2_game_reader_load_objects();
  if (all || test == 6) test3_game_reader_load_objects();

  if (all || test == 7) test1_game_reader_load_player();
  if (all || test == 8) test2_game_reader_load_player();
  if (all || test == 9) test3_game_reader_load_player();

  if (all || test == 10) test1_game_reader_load_enemy();
  if (all || test == 11) test2_game_reader_load_enemy();
  if (all || test == 11) test3_game_reader_load_enemy();



  PRINT_PASSED_PERCENTAGE;

  return 1;
}

void test1_game_reader_load_spaces() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_reader_load_spaces(g, "hormiguero.dat") == OK);
    game_destroy(g);
}

void test2_game_reader_load_spaces() {
    Game *g=NULL;
    PRINT_TEST_RESULT(game_reader_load_spaces(g, "hormiguero.dat") == ERROR);
}

void test3_game_reader_load_spaces() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_reader_load_spaces(g, "") == ERROR);
    game_destroy(g);
}

void test1_game_reader_load_objects() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_reader_load_objects(g, "hormiguero.dat") == OK);
    game_destroy(g);
}

void test2_game_reader_load_objects() {
    Game *g=NULL;
    PRINT_TEST_RESULT(game_reader_load_objects(g, "hormiguero.dat") == ERROR);
}

void test3_game_reader_load_objects() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_reader_load_objects(g, "") == ERROR);
    game_destroy(g);
}

void test1_game_reader_load_player() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_reader_load_player(g, "hormiguero.dat") == OK);
    game_destroy(g);
}

void test2_game_reader_load_player() {
    Game *g=NULL;
    PRINT_TEST_RESULT(game_reader_load_player(g, "hormiguero.dat") == ERROR);
}

void test3_game_reader_load_player() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_reader_load_player(g, "") == ERROR);
    game_destroy(g);
}


void test1_game_reader_load_enemy() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_reader_load_enemy(g, "hormiguero.dat") == OK);
    game_destroy(g);
}

void test2_game_reader_load_enemy() {
    Game *g=NULL;
    PRINT_TEST_RESULT(game_reader_load_enemy(g, "hormiguero.dat") == ERROR);
}

void test3_game_reader_load_enemy() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_reader_load_enemy(g, "") == ERROR);
    game_destroy(g);
}