/**
 * @brief It tests the object module
 *
 * @file object_test.c
 * @author Carlos Tabernero
 * @version 2.0
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "object.h"
 #include "object_test.h" 

 
 #define MAX_TESTS 20
 
 int main(int argc, char **argv) {
     int test = 0;
     int all = 1;
 
     if (argc < 2) {
         printf("Running all tests for module Object:\n");
     } else {
         test = atoi(argv[1]);
         all = 0;
         printf("Running test %d:\t", test);
         if (test < 1 || test > MAX_TESTS) {
             printf("Error: unknown test %d\t", test);
             exit(EXIT_SUCCESS);
         }
     }
 
     if (all || test == 1) test1_object_create();
     if (all || test == 2) test2_object_create();
     if (all || test == 3) test1_object_get_id();
     if (all || test == 4) test2_object_get_id();
     if (all || test == 5) test1_object_set_id();
     if (all || test == 6) test2_object_set_id();
     if (all || test == 7) test1_object_set_name();
     if (all || test == 8) test2_object_set_name();
     if (all || test == 9) test1_object_get_name();
     if (all || test == 10) test2_object_get_name();
     if (all || test == 11) test1_object_set_description();
     if (all || test == 12) test2_object_set_description();
     if (all || test == 13) test1_object_get_desciption();
     if (all || test == 14) test2_object_get_description();
     if (all || test == 15) test1_object_get_health();
     if (all || test == 16) test2_object_get_health();
     if (all || test == 17) test1_object_set_health();
     if (all || test == 18) test2_object_set_health();
     if (all || test == 19) test1_object_get_movable();
     if (all || test == 20) test2_object_get_movable();
     if (all || test == 21) test1_object_set_movable();
     if (all || test == 22) test2_object_set_movable();
     if (all || test == 23) test1_object_get_dependency();
     if (all || test == 24) test2_object_get_dependency();
     if (all || test == 25) test1_object_set_dependency();
     if (all || test == 26) test2_object_set_dependency();
     if (all || test == 27) test1_object_get_open();
     if (all || test == 28) test2_object_get_open();
     if (all || test == 29) test1_object_set_open();
     if (all || test == 30) test2_object_set_open();
     if (all || test == 31) test1_object_print();
     if (all || test == 32) test2_object_print();
     
     PRINT_PASSED_PERCENTAGE;
     
     return 0;
 }
 
 void test1_object_create() {
     Object *o = object_create(1);
     PRINT_TEST_RESULT(o != NULL);
     object_destroy(o);
 }
 
 void test2_object_create() {
     Object *o = object_create(NO_ID);
     PRINT_TEST_RESULT(o == NULL);
 }

 void test1_object_get_id() {
    Object *o = object_create(1);
    object_set_id(o ,5);
    PRINT_TEST_RESULT(object_get_id(o) == 5);
    object_destroy(o);
}

void test2_object_get_id() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_id(o) == NO_ID);
}

void test1_object_set_id() {
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_id(o, 12) == OK);
    object_destroy(o);
}

void test2_object_set_id() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_id(o, 12) == ERROR);
}

void test1_object_set_name() {
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_name(o, "Apple") == OK);
    object_destroy(o);
}
 
void test2_object_set_name() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_name(o, "Apple") == ERROR);
}

void test1_object_get_name() {
    Object *o = object_create(1);
    object_set_name(o, "Apple");
    PRINT_TEST_RESULT(object_get_name(o) == "hola");
    object_destroy(o);
}

void test2_object_get_name() {
    Object *o = object_create(1);
    object_set_name(o, NULL);
    PRINT_TEST_RESULT(object_get_name(o) == NULL);
    object_destroy(o);
}

void test1_object_set_description() {
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_description(o, "Caracola") == OK);
    object_destroy(o);
}

void test2_object_set_description() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_description(o, "caracola") == ERROR);
}

void test1_object_get_description() {
    Object *o = object_create(1);
    object_set_description(o, "caracola");
    PRINT_TEST_RESULT(object_get_description(o) == "caracola");
    object_destroy(o);
}

void test2_object_get_desciption() {
    Object *o = object_create(1);
    object_set_description(o, NULL);
    PRINT_TEST_RESULT(object_get_description(o) == NULL);
    object_destroy(o);
}
 
 void test1_object_set_health() {
     Object *o = object_create(1);
     PRINT_TEST_RESULT(object_set_health(o, 5) == OK);
     object_destroy(o);
 }
 
 void test2_object_set_health() {
     Object *o = NULL;
     PRINT_TEST_RESULT(object_set_health(o, 5) == ERROR);
 }
 
 void test1_object_get_health() {
    Object *o = NULL;
    player_set_health(o, 20);
    PRINT_TEST_RESULT(object_get_health(o) == -1);
    player_destroy(o);
  }

  void test2_object_get_health() {
    Object *o = object_create(1);
    player_set_health(o, 20);
    PRINT_TEST_RESULT(object_get_health(o) == 20);
    object_destroy(o);
  }

  void test1_object_get_movable(){
    Object *o = object_create(1);
    object_set_movable(o, 1);
    PRINT_TEST_RESULT(object_get_movable(o) == 1);
    object_destroy(o);
  }

  void test2_object_get_movable(){
    Object *o = NULL;
    object_set_movable(o, 1);
    PRINT_TEST_RESULT(object_get_movable(o) == FALSE);
  }

  void test1_object_set_movable() {
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_friendly(o, TRUE) == OK);
    character_destroy(o);
}

void test2_object_set_movable() {
    Object *o = NULL;
    PRINT_TEST_RESULT(character_set_friendly(o, TRUE) == ERROR);
}

void test1_character_set_dependency() {
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_dependency(o, 10) == OK);
    character_destroy(o);
}

void test2_character_set_dependency() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_dependency(o, 10) == ERROR);
}

void test1_object_get_dependency() {
    Object *o = object_create(1);
    object_set_dependency(o ,5);
    PRINT_TEST_RESULT(object_get_dependency(o) == 5);
    object_destroy(o);
}

void test2_object_get_dependency() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_dependency(o) == NO_ID);
}

void test1_character_set_open() {
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_open(o, 10) == OK);
    character_destroy(o);
}

void test2_character_set_open() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_open(o, 10) == ERROR);
}

void test1_object_get_open() {
    Object *o = object_create(1);
    object_set_open(o ,5);
    PRINT_TEST_RESULT(object_get_open(o) == 5);
    object_destroy(o);
}

void test2_object_get_open() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_open(o) == NO_ID);
}

 void test1_object_print() {
     Object *o = object_create(1);
     PRINT_TEST_RESULT(object_print(o) == OK);
     object_destroy(o);
 }
 
 void test2_object_print() {
     Object *o = NULL;
     PRINT_TEST_RESULT(object_print(o) == ERROR);
 }
 