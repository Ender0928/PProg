/**
 * @brief It tests the character module
 *
 * @file character_test.c
 * @author Javier Pérez
 * @version 2.0
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "../include/set.h"
#include "../include/set_test.h"
#include "../include/test.h"

#define MAX_TEST2 9


int main(int argc, char** argv) {

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Set:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TEST2) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_set_create();
  if (all || test == 2) test1_set_destroy();
  if (all || test == 3) test2_set_destroy();
  if (all || test == 4) test1_set_add_object();
  if (all || test == 5) test2_set_add_object();
  if (all || test == 6) test1_set_del_object();
  if (all || test == 7) test2_set_del_object();
  if (all || test == 8) test1_set_find_object();
  if (all || test == 9) test2_set_find_object();

PRINT_PASSED_PERCENTAGE;

return 1;
}


void test1_set_create(){
    int result;
    Set* s;
    s = set_create();
    result=s!=NULL;
    PRINT_TEST_RESULT(result);
    set_destroy(s);

}

void test1_set_destroy() {
    Set *s;
    s = set_create();
    PRINT_TEST_RESULT(set_destroy(s)==OK);

}

void test2_set_destroy(){
    Set* s = NULL;
    PRINT_TEST_RESULT(set_destroy(s)==ERROR);

}

void test1_set_add_object(){
    Set* s;
    s = set_create();
    PRINT_TEST_RESULT(set_add_object(s,TRUE)==OK);
    set_destroy(s);

}

void test2_set_add_object(){
    Set* s = NULL;
    PRINT_TEST_RESULT(set_add_object(s,TRUE)==ERROR);


}

void test1_set_del_object(){
    Set* s;
    s = set_create();
    set_add_object(s,TRUE);
    PRINT_TEST_RESULT(set_remove_object(s,TRUE)==OK);
    set_destroy(s);

}

void test2_set_del_object(){
    Set* s;
    s = set_create();
    PRINT_TEST_RESULT(set_remove_object(s,TRUE)==ERROR);
    set_destroy(s);

}



void test1_set_find_object(){
    Set *s;
    s = set_create();
    PRINT_TEST_RESULT(set_find_object(s,TRUE)==FALSE);
    set_destroy(s);

}

void test2_set_find_object(){
    Set *s;
    s = set_create();
    set_add_object(s,TRUE);
    PRINT_TEST_RESULT(set_find_object(s,TRUE)==TRUE);
    set_destroy(s);



}