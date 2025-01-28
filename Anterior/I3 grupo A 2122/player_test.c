#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 


#include "player.h"
#include "player_test.h"
#include "set.h"
#include "inventory.h"
#include "test.h"

#define MAX_TEST2 31

int main(int argc, char** argv) {

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Object:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TEST2) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }
 
 
  if (all || test == 1) test1_player_create();
  if (all || test == 1) test2_player_create();
  if (all || test == 3) test1_player_destroy();
  if (all || test == 4) test2_player_destroy();
  if (all || test == 5) test1_player_get_id();
  if (all || test == 6) test2_player_get_id();
  if (all || test == 7) test1_player_set_name();
  if (all || test == 8) test2_player_set_name();
  if (all || test == 9) test3_player_set_name();
  if (all || test == 10) test1_player_get_name();
  if (all || test == 11) test2_player_get_name();
  if (all || test == 12) test1_player_set_location();
  if (all || test == 13) test2_player_set_location();
  if (all || test == 14) test3_player_set_location();
  if (all || test == 15) test1_player_get_location();
  if (all || test == 16) test2_player_get_location();
  if (all || test == 17) test3_player_get_location();
  if (all || test == 18) test1_player_set_health();
  if (all || test == 19) test2_player_set_health();
  if (all || test == 20) test3_player_set_health();
  if (all || test == 21) test1_player_get_health();
  if (all || test == 22) test2_player_get_health();
  if (all || test == 23) test3_player_get_health();
  if (all || test == 24) test1_player_find_object();
  if (all || test == 25) test2_player_find_object();
  if (all || test == 26) test1_player_inv_add_object();
  if (all || test == 27) test2_player_inv_add_object();
  if (all || test == 28) test3_player_inv_add_object();
  if (all || test == 29) test1_player_inv_del_object();
  if (all || test == 30) test2_player_inv_del_object();
  if (all || test == 31) test1_player_inv_isFull();


PRINT_PASSED_PERCENTAGE;

return 1;
}




void test1_player_create() {
    int result;
    Player *p;
    p = player_create(P);
    result = p != NULL;
    PRINT_TEST_RESULT(result);
    player_destroy(p);
}

void test2_player_create() {
    Player *p;
    p = player_create(P);
    PRINT_TEST_RESULT(player_get_id(p) == P);
    player_destroy(p);
}

void test1_player_destroy() {
    Player *p;
    p = player_create(P);
    PRINT_TEST_RESULT(player_destroy(p)==OK);
}

void test2_player_destroy() {
    Player *p=NULL;
    PRINT_TEST_RESULT(player_destroy(p)==ERROR);
}

void test1_player_get_id() {
    Player *p;
    p = player_create(P);
    PRINT_TEST_RESULT(player_get_id(p) == P);
    player_destroy(p);
}

void test2_player_get_id() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_get_id(p) == NO_ID);
}

void test1_player_set_name() {
  Player *p;
  p = player_create(P);
  PRINT_TEST_RESULT(player_set_name(p, "hola") == OK);
  player_destroy(p);
}

void test2_player_set_name() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_name(p, "hola") == ERROR);
}

void test3_player_set_name() {
  Player *p;
  p = player_create(P);
  PRINT_TEST_RESULT(player_set_name(p, NULL) == ERROR);
  player_destroy(p);
}

void test1_player_get_name() {
    Player *p;
    p = player_create(P);
    player_set_name(p, "adios");
    PRINT_TEST_RESULT(strcmp(player_get_name(p), "adios") == ERROR);
    player_destroy(p);
}

void test2_player_get_name() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_get_name(p) == NULL);
}


void test1_player_set_location() {
    Player *p;
    p = player_create(P);
    PRINT_TEST_RESULT(player_set_location(p, 11) == OK);
    player_destroy(p);
}

void test2_player_set_location() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_set_location(p, 11) == ERROR);
}

void test3_player_set_location() {
    Player *p;
    p = player_create(P);
    PRINT_TEST_RESULT(player_set_location(p, NO_ID) == ERROR);
    player_destroy(p);
}


void test1_player_get_location() {
    Player *p;
    p = player_create(P);
    PRINT_TEST_RESULT(player_get_location(p) == NO_ID);
    player_destroy(p);
}

void test2_player_get_location() {
  Player *p;
  p = player_create(P);
  player_set_location(p, 11);
  PRINT_TEST_RESULT(player_get_location(p) == 11);
  player_destroy(p);
}

void test3_player_get_location() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_location(p) == NO_ID);
}



void test1_player_set_health() {
    Player *p;
    p = player_create(P);
    PRINT_TEST_RESULT(player_set_health(p, 5) == OK);
    player_destroy(p);
}

void test2_player_set_health() {
  Player *p;
  p = player_create(P);
  PRINT_TEST_RESULT(player_set_health(p, -1) == ERROR);
  player_destroy(p);
}

void test3_player_set_health() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_health(p, 5) == ERROR);
}



void test1_player_get_health() {
    Player *p;
    p = player_create(P);
    PRINT_TEST_RESULT(player_get_health(p) != -1);
    player_destroy(p);
}

void test2_player_get_health() {
  Player *p;
  p = player_create(P);
  PRINT_TEST_RESULT(player_set_location(p, NO_ID) == ERROR);
  player_destroy(p);
}

void test3_player_get_health() {
  Player *p=NULL;
  PRINT_TEST_RESULT(player_get_health(p) == -1);
}


void test1_player_find_object() {
    Player *p;
    p = player_create(P);
    PRINT_TEST_RESULT(player_find_object(p, NO_ID) == FALSE);
    player_destroy(p);
}

void test2_player_find_object() {
    Player *p=NULL;
    PRINT_TEST_RESULT(player_find_object(p, 21) == FALSE);
}

void test1_player_inv_add_object() {
    Player *p;
    p = player_create(P);
    PRINT_TEST_RESULT(player_inv_add_object(p, NO_ID) == ERROR);
    player_destroy(p);
}

void test2_player_inv_add_object() {
    Player *p=NULL;
    PRINT_TEST_RESULT(player_inv_add_object(p, 21) == ERROR);
}

void test3_player_inv_add_object() {
    Player *p;
    p = player_create(P);
    PRINT_TEST_RESULT(player_inv_add_object(p, 21) == OK);
    player_destroy(p);
}

void test1_player_inv_del_object() {
    Player *p;
    p = player_create(P);
    PRINT_TEST_RESULT(player_inv_del_object(p, NO_ID) == ERROR);
    player_destroy(p);
}

void test2_player_inv_del_object() {
    Player *p=NULL;
    PRINT_TEST_RESULT(player_inv_del_object(p, 21) == ERROR);
}

void test1_player_inv_isFull() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_inv_isFull(p) == TRUE);
}
