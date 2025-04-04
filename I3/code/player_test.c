/**
 * @brief It tests the player module
 *
 * @file player_test.c
 * @author Javier Pérez
 * @version 2.0
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #include "player_test.h" 

 
 #define MAX_TESTS 20
 
 int main(int argc, char **argv) {
     int test = 0;
     int all = 1;
 
     if (argc < 2) {
         printf("Running all tests for module player:\n");
     } else {
         test = atoi(argv[1]);
         all = 0;
         printf("Running test %d:\t", test);
         if (test < 1 || test > MAX_TESTS) {
             printf("Error: unknown test %d\t", test);
             exit(EXIT_SUCCESS);
         }
     }
 
     if (all || test == 1) test1_player_create();
     if (all || test == 2) test2_player_create();
     if (all || test == 3) test1_player_set_name();
     if (all || test == 4) test2_player_set_name();
     if (all || test == 5) test1_player_destroy();
     if (all || test == 6) test2_player_destroy();
     if (all || test == 7) test1_player_set_location();
     if (all || test == 8) test2_player_set_location();
     if (all || test == 9) test1_player_add_object();
     if (all || test == 10) test2_player_add_object();
     if (all || test == 11) test1_player_remove_object();
     if (all || test == 12) test2_player_remove_object();
     if (all || test == 13) test1_player_set_health();
     if (all || test == 14) test2_player_set_health();
     if (all || test == 15) test1_player_set_backpack();
     if (all || test == 16) test2_player_set_backpack();
     if (all || test == 17) test1_player_set_turn();
     if (all || test == 18) test2_player_set_turn();
     if (all || test == 19) test1_player_set_max_objects();
     if (all || test == 20) test2_player_set_max_objects();
     if (all || test == 21) test1_player_set_graphic_desc();
     if (all || test == 22) test2_player_set_graphic_desc();
     if (all || test == 23) test1_player_get_turn();
     if (all || test == 24) test2_player_get_turn();
     if (all || test == 25) test1_player_get_backpack();
     if (all || test == 26) test2_player_get_backpack();
     if (all || test == 27) test1_player_get_health();
     if (all || test == 28) test2_player_get_health();
     if (all || test == 29) test1_player_get_location();
     if (all || test == 30) test2_player_get_location();
     if (all || test == 31) test1_player_get_name();
     if (all || test == 32) test2_player_get_name();
     if (all || test == 33) test1_player_get_id();
     if (all || test == 34) test2_player_get_id();
     if (all || test == 35) test1_player_get_graphic_desc();
     if (all || test == 36) test2_player_get_graphic_desc();
     if (all || test == 37) test1_player_has_object();
     if (all || test == 38) test2_player_has_object();
     if (all || test == 39) test1_player_inventory_is_full();
     if (all || test == 40) test2_player_inventory_is_full();
     if (all || test == 41) test1_player_inventory_is_empty();
     if (all || test == 42) test2_player_inventory_is_empty();
     if (all || test == 43) test1_player_print();
     if (all || test == 44) test2_player_print();
     
     PRINT_PASSED_PERCENTAGE;
     
     return 0;
 }
 
 void test1_player_create() {
    Player *p = player_create(5);
    PRINT_TEST_RESULT(p != NULL);
    player_destroy(p);
  }
  
  void test2_player_create() {
    Player *p = player_create(NO_ID);
    PRINT_TEST_RESULT(p == NULL);
    player_destroy(p);
  }
  
  void test1_player_set_name() {
    Player *p = player_create(5);
    PRINT_TEST_RESULT(player_set_name(p, "Juan") == OK);
    player_destroy(p);
  }
  
  void test2_player_set_name() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_set_name(p, "Juan") == ERROR);
  }

  void test1_player_destroy() {
    Player *p = player_create(5);
    PRINT_TEST_RESULT(player_destroy(p) == OK);
  }

  void test2_player_destroy() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_destroy(p) == ERROR);
  }

  void test1_player_set_location() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(player_set_location(p, 11) == OK);
    player_destroy(p);
  }

  void test2_player_set_location() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_set_location(p, 11) == ERROR);
  }

  void test1_player_add_object() {
    Player *p = player_create(2);
    player_set_max_objects(p, 20);
    PRINT_TEST_RESULT(player_add_object(p, 2) == OK);
    player_destroy(p);
  }
  
  void test2_player_add_object() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_add_object(p, 9) == ERROR);
  }

  void test1_player_remove_object() {
    Player *p = player_create(3);
    PRINT_TEST_RESULT(player_remove_object(p, 3));
    player_destroy(p);
  }

  void test2_player_remove_object() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_remove_object(p, 2) == ERROR);
  }

  void test1_player_set_health() {
    Player *p = player_create(3);
    PRINT_TEST_RESULT(player_set_health(p, 20) == OK );
    player_destroy(p);
  }

  void test2_player_set_health() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_set_health(p,  20) == ERROR);
  }

  void test1_player_set_backpack() {
    Player *p = player_create(2);
    Inventory *i = inventory_create();
    PRINT_TEST_RESULT(player_set_backpack(p, i) == OK);
    inventory_destroy(i);
    player_destroy(p);
  }  

  void test2_player_set_backpack() {
    Player *p = NULL;
    Inventory *i = inventory_create();
    PRINT_TEST_RESULT(player_set_backpack(p, i) == ERROR);
    inventory_destroy(i);
  }

  void test1_player_set_turn() {
    Player *p = player_create(2);
    PRINT_TEST_RESULT(player_set_turn(p, TRUE) == OK);
    player_destroy(p);
  }

  void test2_player_set_turn() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_set_turn(p, TRUE) == ERROR);
  } 

  void test1_player_set_max_objects() {
    Player *p = player_create(2);
    PRINT_TEST_RESULT(player_set_max_objects(p, 20) == OK);
    player_destroy(p);
  }

  void test2_player_set_max_objects() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_set_max_objects(p, 20) == ERROR);
  }

  void test1_player_set_graphic_desc() {
    Player *p = player_create(2);
    PRINT_TEST_RESULT(player_set_graphic_desc(p, "@---") == OK);
    player_destroy(p);
  }

  void test2_player_set_graphic_desc() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_set_graphic_desc(p, "@---") == ERROR);
  }

  void test1_player_get_turn() {
   Player *p = player_create(1);
   PRINT_TEST_RESULT(player_get_turn(p) ==  TRUE);
   player_destroy(p);
  }
  
  void test2_player_get_turn() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_get_turn(p) == FALSE);
  }

  void test1_player_get_backpack() {
    Player *p = player_create(2);
    Inventory *i = inventory_create();
    player_set_backpack(p, i);
    PRINT_TEST_RESULT(player_get_backpack(p) == i);
    inventory_destroy(i);
    player_destroy(p);
  }

  void test2_player_get_backpack() {
    Player *p = NULL;
    Inventory *i = NULL;
    player_set_backpack(p, i);
    PRINT_TEST_RESULT(player_get_backpack(p) == NULL);
  }

  void test1_player_get_health() {
    Player *p = NULL;
    player_set_health(p, 20);
    PRINT_TEST_RESULT(player_get_health(p) == 20);
    player_destroy(p);
  }

  void test2_player_get_health() {
    Player *p = NULL;
    player_set_health(p, 20);
    PRINT_TEST_RESULT(player_get_health(p) == -1);
  }

  void test1_player_get_location() {
    Player *p = player_create(3);
    player_set_location(p, 11);
    PRINT_TEST_RESULT(player_get_location(p) == 11);
    player_destroy(p);
  }
  
  void test2_player_get_location() {
    Player *p = NULL;
    player_set_location(p, 11);
    PRINT_TEST_RESULT(player_get_location(p) == NO_ID);
  }

  void test1_player_get_name() {
    Player *p = player_create(2);
    player_set_name(p, "Hola");
    PRINT_TEST_RESULT(player_get_name(p) == "Hola");
    player_destroy(p);
  }

  void test2_player_get_name() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_get_name(p) == NULL);
  }

  void test1_player_get_id() {
    Player *p = player_create(2);
    PRINT_TEST_RESULT(player_get_id(p) == 2);
    player_destroy(p);
  }

  void test2_player_get_id() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_get_id(p) == NO_ID);
  }

  void test1_player_get_graphic_desc() {
    Player *p = player_create(2);
    player_set_graphic_desc(p, "@---");
    PRINT_TEST_RESULT(player_get_graphic_desc(p) == "@---");
    player_destroy(p);
  }

  void test2_player_get_graphic_desc() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_get_graphic_desc(p) == NULL);
  }

  void test1_player_has_object() {
    Player *p = player_create(2);
    player_add_object(p, 2);
    PRINT_TEST_RESULT(player_has_object(p, 2) == OK);
    player_destroy(p);
  }

  void test2_player_has_object() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_has_object(p, 3) == ERROR);
  }

  void test1_player_inventory_is_full() {
    Player *p = player_create(2);
    player_set_max_objects(p, 1);
    player_add_object(p, 1);
    PRINT_TEST_RESULT(player_inventory_is_full(p) == TRUE);
    player_destroy(p);
  }

  void test2_player_inventory_is_full() {
    Player *p = NULL;
    player_set_max_objects(p, 4);
    player_add_object(p, 1);
    PRINT_TEST_RESULT(player_inventory_is_full(p) == FALSE);
    player_destroy(p);
  }

  void test1_player_inventory_is_empty() {
    Player *p = player_create(2);
    PRINT_TEST_RESULT(player_inventory_is_empty(p) == TRUE);
    player_destroy(p);
  }

  void test2_player_inventory_is_empty() {
    Player *p = player_create(2);
    player_set_max_objects(p, 4);
    player_add_object(p, 1);
    PRINT_TEST_RESULT(player_inventory_is_empty(p) == FALSE);
    player_destroy(p);
  }

  void test1_player_print() {
    Player *p = player_create(2);
    PRINT_TEST_RESULT(player_print(p) == OK);
    player_destroy(p);
  }

  void test2_player_print() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_print(p) == ERROR);
  }
 