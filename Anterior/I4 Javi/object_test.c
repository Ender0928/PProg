#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "object.h"
#include "object_test.h"
#include "test.h"

#define MAX_TEST2 14

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
 
 
  if (all || test == 1) test1_object_create();
  if (all || test == 1) test2_object_create();
  if (all || test == 3) test1_object_destroy();
  if (all || test == 4) test2_object_destroy();
  if (all || test == 5) test1_object_set_id();
  if (all || test == 6) test2_object_set_id();
  if (all || test == 7) test1_object_get_id();
  if (all || test == 8) test2_object_get_id();
  if (all || test == 9) test1_object_set_name();
  if (all || test == 10) test2_object_set_name();
  if (all || test == 11) test3_object_set_name();
  if (all || test == 12) test1_object_get_name();
  if (all || test == 13) test2_object_get_name();
  if (all || test == 14) test1_object_set_mobable();
  if (all || test == 15) test2_object_set_mobable();
  if (all || test == 16) test1_object_get_mobable();
  if (all || test == 17) test2_object_get_mobable();
  if (all || test == 18) test1_object_set_dependecy();
  if (all || test == 19) test2_object_set_dependecy();
  if (all || test == 20) test1_object_get_dependecy();
  if (all || test == 21) test2_object_get_dependecy();
  if (all || test == 22) test1_object_set_open();
  if (all || test == 23) test2_object_set_open();
  if (all || test == 24) test1_object_get_open();
  if (all || test == 25) test2_object_get_open();
  if (all || test == 26) test1_object_set_illuminate();
  if (all || test == 27) test2_object_set_illuminate();
  if (all || test == 28) test1_object_get_illuminate();
  if (all || test == 29) test2_object_get_illuminate();
  if (all || test == 30) test1_object_set_turnedon();
  if (all || test == 31) test2_object_set_turnedon();
  if (all || test == 32) test1_object_get_turnedon();
  if (all || test == 33) test2_object_get_turnedon();



PRINT_PASSED_PERCENTAGE;

return 1;
}



void test1_object_create() {
    int result;
    Object *o;
    o = object_create(21);
    result=o!=NULL;
    PRINT_TEST_RESULT(result);
    object_destroy(o);
}

void test2_object_create() {
  Object *o;
  o = object_create(21);
  PRINT_TEST_RESULT(object_get_id(o) == 21);
  object_destroy(o);
}

void test1_object_destroy() {
    Object *o;
    o = object_create(21);
    PRINT_TEST_RESULT(object_destroy(o)==OK);
}

void test2_object_destroy() {
    Object *o=NULL;
    PRINT_TEST_RESULT(object_destroy(o)==ERROR);
}


void test1_object_set_id() {
    Object *o;
    o = object_create(21);
    PRINT_TEST_RESULT(object_set_id(o, 21));
    object_destroy(o);
}

void test2_object_set_id() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_id(o, 21) == ERROR);
}


void test1_object_get_id() {
    Object *o;
    o = object_create(21);
    object_set_id(o, 21);
    PRINT_TEST_RESULT(object_get_id(o) == 21);
    object_destroy(o);
}

void test2_object_get_id() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_id(o) == NO_ID);
}





void test1_object_set_name() {
    Object *o;
    o = object_create(21);
    PRINT_TEST_RESULT(object_set_name(o, "hola") == OK);
    object_destroy(o);
}

void test2_object_set_name() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_name(o, "hola") == ERROR);
}

void test3_object_set_name() {
    Object *o;
    o = object_create(21);
    PRINT_TEST_RESULT(object_set_name(o, NULL) == ERROR);
    object_destroy(o);
}


void test1_object_get_name() {
    Object *o;
    o = object_create(21);
    object_set_name(o, "adios");
    PRINT_TEST_RESULT(strcmp(object_get_name(o), "adios") == ERROR);
    object_destroy(o);
}

void test2_object_get_name() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_name(o) == NULL);
}

void test1_object_set_mobable() {
    Object *o;
    BOOL m = FALSE; 
    o = object_create(21);
    PRINT_TEST_RESULT(object_set_mobable(o, m) == OK);
    object_destroy(o);
}

void test2_object_set_mobable() {
    Object *o = NULL;
    BOOL m = TRUE; 
    PRINT_TEST_RESULT(object_set_mobable(o, m) == ERROR);
    object_destroy(o);
}

void test1_object_get_mobable() {
    Object *o;
    BOOL m = FALSE; 
    o = object_create(21);
    object_set_mobable(o, m);
    PRINT_TEST_RESULT(object_get_mobable(o, m) == FALSE);
    object_destroy(o);
}

void test2_object_get_mobable() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_mobable(o) == NO_ID);
    object_destroy(o);
}

void test1_object_set_dependecy() {
    Object *o;
    Id id = 20; 
    o = object_create(21);
    PRINT_TEST_RESULT(object_set_dependecy(o, id) == OK);
    object_destroy(o);
}

void test2_object_set_dependecy() {
    Object *o = NULL;
    Id id = 20; 
    PRINT_TEST_RESULT(object_set_dependecy(o, id) == ERROR);
    object_destroy(o);
}

void test1_object_get_dependecy() {
    Object *o;
    Id id = 20;
    o = object_create(21);
    object_set_dependecy(o, id);
    PRINT_TEST_RESULT(object_get_dependecy(o) == 20);
    object_destroy(o);
}

void test2_object_get_dependecy() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_dependecy(o) == NO_ID);
}

void test1_object_set_open() {
    Object *o;
    Id id = 20; 
    o = object_create(21);
    PRINT_TEST_RESULT(object_set_open(o, id) == OK);
    object_destroy(o);
}

void test2_object_set_open() {
    Object *o = NULL;
    Id id = 20; 
    PRINT_TEST_RESULT(object_set_open(o, id) == ERROR);
    object_destroy(o);
}

void test1_object_get_open() {
    Object *o;
    Id id = 20;
    o = object_create(21);
    object_set_open(o, id);
    PRINT_TEST_RESULT(object_get_open(o) == 20);
    object_destroy(o);
}

void test2_object_get_open() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_open(o) == NO_ID);
}

void test1_object_set_illuminate() {
    Object *o;
    BOOL *m = FALSE; 
    o = object_create(21);
    PRINT_TEST_RESULT(object_set_illuminate(o, m) == OK);
    object_destroy(o);
}

void test2_object_set_illuminate() {
    Object *o = NULL;
    BOOL *m = TRUE; 
    PRINT_TEST_RESULT(object_set_illuminate(o, m) == ERROR);
    object_destroy(o);
}

void test1_object_get_illuminate() {
    Object *o;
    BOOL *m = FALSE; 
    o = object_create(21);
    object_set_illuminate(o, m);
    PRINT_TEST_RESULT(object_set_illuminate(o, m) == FALSE);
    object_destroy(o);
}

void test2_object_get_illuminate() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_illuminate(o) == NO_ID);
    object_destroy(o);
}

void test1_object_set_turnedon() {
    Object *o;
    BOOL *m = FALSE; 
    o = object_create(21);
    PRINT_TEST_RESULT(object_set_turnedon(o, m) == OK);
    object_destroy(o);
}

void test2_object_set_turnedon() {
    Object *o = NULL;
    BOOL *m = TRUE; 
    PRINT_TEST_RESULT(object_set_turnedon(o, m) == ERROR);
    object_destroy(o);
}

void test1_object_get_turnedon() {
    Object *o;
    BOOL *m = FALSE; 
    o = object_create(21);
    object_set_illuminate(o, m);
    PRINT_TEST_RESULT(object_set_turnedon(o, m) == FALSE);
    object_destroy(o);
}

void test2_object_get_turnedon() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_turnedon(o) == NO_ID);
    object_destroy(o);
}
