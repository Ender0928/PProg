#include <stdio.h>
#include <stdlib.h>

#include "test.h"
#include "game.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include "types.h"

void test1_game_create() {
  int result;
  Game *g;
  g = game_create();
  result=g!=NULL;
  PRINT_TEST_RESULT(result);
  game_destroy(g);
}

void test2_game_create() {
  Game *g=NULL;
  g = game_create();
  PRINT_TEST_RESULT(g == NULL);
  game_destroy(g);
}

void test1_game_destroy() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_destroy(g) == OK);
    game_destroy(g);
}

void test2_game_destroy() {
    Game *g=NULL;
    PRINT_TEST_RESULT(game_destroy(g)==ERROR);
}

void test1_game_create_from_file() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_create_from_file(g, "hormiguero.dat") == OK);
    game_destroy(g);
}

void test2_game_create_from_file() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_create_from_file(g, "") == ERROR);
    game_destroy(g);
}

void test3_game_create_from_file() {
    Game *g=NULL;
    PRINT_TEST_RESULT(game_create_from_file(g, "hormiguero.dat") == ERROR);
}

void test4_game_create_from_file() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_create_from_file(g, "") == ERROR);
    game_destroy(g);
}

void test1_game_add_space() {
    Game *g;
    Space *s;
    g = game_create();
    s = space_create(4);
    PRINT_TEST_RESULT(game_add_space(g, s) == OK);
    game_destroy(g);
    space_destroy(s);
}

void test2_game_add_space() {
    Game *g=NULL;
    Space *s;
    s = space_create(4);
    PRINT_TEST_RESULT(game_add_space(g, s) == ERROR);
    space_destroy(s);
}

void test3_game_add_space() {
    Game *g;
    Space *s=NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_add_space(g, s) == ERROR);
    game_destroy(g);
}

void test1_game_get_space_id_at() {
    Game *g;
    Space *s;
    g = game_create();
    s = space_create(4);
    PRINT_TEST_RESULT(game_get_space_id_at(g, 4) == 4);
    game_destroy(g);
    space_destroy(s);
}

void test2_game_get_space_id_at() {
    Game *g;
    Space *s;
    g = game_create();
    s = space_create(4);
    PRINT_TEST_RESULT(game_get_space_id_at(g, 4) == 4);
    game_destroy(g);
    space_destroy(s);
}

void test3_game_get_space_id_at() {
    Game *g;
    Space *s=NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_get_space_id_at(g, 4) == NULL);
    game_destroy(g);
}

void test4_game_get_space_id_at() {
    Game *g=NULL;
    Space *s;
    s = space_create(4);
    PRINT_TEST_RESULT(game_get_space_id_at(g, 4) == NULL);
    space_destroy(s);
}

void test1_game_get_space() {
    Game *g=NULL;
    Space *s;
    s = space_create(0);
    PRINT_TEST_RESULT(game_get_space(g, 0) == NULL);
    space_destroy(s);
}

void test2_game_get_space() {
    Game *g;
    Space *s=NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_get_space(g, 0) == NULL);
    game_destroy(g);
}

void test1_game_set_player_location() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_set_player_location(g, 13) == OK);
    game_destroy(g);
}

void test2_game_set_player_location() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_set_player_location(g, NO_ID) == ERROR);
    game_destroy(g);
}

void test1_game_set_object_location() {
    Game *g=NULL;
    PRINT_TEST_RESULT(game_set_object_location(g, 124, 21) == ERROR);
}

void test2_game_set_object_location() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_set_object_location(g, NO_ID, 21) == ERROR);
    game_destroy(g);
}

void test3_game_set_object_location() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_set_object_location(g, 124, NO_ID) == ERROR);
    game_destroy(g);
}

void test4_game_set_object_location() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_set_object_location(g, 124, 21) == OK);
    game_destroy(g);
}

void test1_game_get_object() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_get_object(g, 3));
    game_destroy(g);
}

void test2_game_get_object() {
    Game *g=NULL;
    PRINT_TEST_RESULT(game_get_object(g, 3) == NULL);
}

void test3_game_get_object() {
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_get_object(g, 5) == NULL);
    game_destroy(g);
}

void test1_game_get_player() {
    Game *g=NULL;
    PRINT_TEST_RESULT(game_get_player(g) == 0);
}

