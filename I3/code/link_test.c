/** 
 * @brief It tests link module
 * 
 * @file link_test.c
 * @author Carlos Tabernero
 * @version 0.0 
 * @date 17-02-2025
 * @copyright GNU Public License
 */

 #include <stdio.h> 
 #include <stdlib.h> 
 #include <string.h> 

 #include "link_test.h"

 
 #define MAX_TESTS 30
 
 /** 
  * @brief Main function for LINK unit tests. 
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
     printf("Running all test for module Link:\n");
   } else {
     test = atoi(argv[1]);
     all = 0;
     printf("Running test %d:\t", test);
     if (test < 1 && test > MAX_TESTS) {
       printf("Error: unknown test %d\t", test);
       exit(EXIT_SUCCESS);
     }
   }

  
   if (all || test == 1) test1_link_create();
   if (all || test == 2) test2_link_create();
   if (all || test == 3) test1_link_set_name();
   if (all || test == 4) test2_link_set_name();
   if (all || test == 5) test1_link_set_origin();
   if (all || test == 6) test2_link_set_origin();
   if (all || test == 7) test1_link_set_destination();
   if (all || test == 8) test2_link_set_destination();
   if (all || test == 9) test1_link_set_direction();
   if (all || test == 10) test2_link_set_direction();
   if (all || test == 11) test1_link_set_open();
   if (all || test == 12) test2_link_set_open();
   if (all || test == 13) test1_link_get_name();
   if (all || test == 14) test2_link_get_name();
   if (all || test == 15) test1_link_get_origin();
   if (all || test == 16) test2_link_get_origin();
   if (all || test == 17) test1_link_get_destination();
   if (all || test == 18) test2_link_get_destination();
   if (all || test == 19) test1_link_get_direction();
   if (all || test == 20) test2_link_get_direction();
   if (all || test == 21) test1_link_is_open();
   if (all || test == 22) test2_link_is_open();
   if (all || test == 23) test1_link_print();
   if (all || test == 24) test2_link_print();
 
   PRINT_PASSED_PERCENTAGE;
 
   return 1;
 }
 
 void test1_link_create() {
   Link *s = link_create(5);
   PRINT_TEST_RESULT(s != NULL);
   link_destroy(s);
 }
 
 void test2_link_create() {
   Link *s = link_create(NO_ID);
   PRINT_TEST_RESULT(s == NULL);
   link_destroy(s);
 }
 
 void test1_link_set_name() {
   Link *s = link_create(5);
   PRINT_TEST_RESULT(link_set_name(s, "norte") == OK);
   link_destroy(s);
 }
 
 void test2_link_set_name() {
   Link *s = NULL;
   PRINT_TEST_RESULT(link_set_name(s, "norte") == ERROR);
 }
 
 void test1_link_set_origin() {
  Link *s = link_create(2);
  PRINT_TEST_RESULT(link_set_origin(s, 10) == OK);
  link_destroy(s);
 }

 void test2_link_set_origin() {
  Link *s = NULL;
  PRINT_TEST_RESULT(link_set_origin(s, 10) == ERROR);
}

void test1_link_set_destination() {
  Link *s = link_create(1);
  PRINT_TEST_RESULT(link_set_destination(s, 5) == OK);
  link_destroy(s);
}

void test2_link_set_destination() {
  Link *s = NULL;
  PRINT_TEST_RESULT(link_set_destination(s, 5) == ERROR);
}

void test1_link_set_direction() {
  Link *s = link_create(1);
  PRINT_TEST_RESULT(link_set_direction(s, N) == OK);
  link_destroy(s);
}

void test2_link_set_direction() {
  Link *s = NULL;
  PRINT_TEST_RESULT(link_set_direction(s, N) == ERROR);
}

void test1_link_set_open(){
  Link *s = link_create(3);
  PRINT_TEST_RESULT(link_set_open(s, TRUE) == OK);
  link_destroy(s);
}

void test2_link_set_open() {
  Link *s = NULL;
  PRINT_TEST_RESULT(link_set_open(s, TRUE) == ERROR);
}

void test1_link_get_name() {
  Link *s = link_create(1);
  link_set_name(s, "norte");
  PRINT_TEST_RESULT(strcmp(link_get_name(s), "norte") == 0);
  link_destroy(s);
}

void test2_link_get_name() {
  Link *s = NULL;
  PRINT_TEST_RESULT(link_get_name(s) == NULL);
}

void test1_link_get_origin() {
  Link *s = link_create(5);
  link_set_origin(s, 4);
  PRINT_TEST_RESULT(link_get_origin(s) == 4);
  link_destroy(s);
}

void test2_link_get_origin() {
  Link *s = NULL;
  PRINT_TEST_RESULT(link_get_origin(s) == NO_ID);
}

void test1_link_get_destination() {
  Link *s = link_create(5);
  link_set_destination(s, 4);
  PRINT_TEST_RESULT(link_get_destination(s) == 4);
  link_destroy(s);
}

void test2_link_get_destination() {
  Link *s = NULL;
  PRINT_TEST_RESULT(link_get_destination(s) == NO_ID);
}

void test1_link_get_direction() {
  Link *s = link_create(5);
  link_set_direction(s, N);
  PRINT_TEST_RESULT(link_get_direction(s) == N);
  link_destroy(s);
}

void test2_link_get_direction() {
  Link *s = NULL;
  PRINT_TEST_RESULT(link_get_direction(s) == U);
}

void test1_link_is_open() {
  Link *s = link_create(5);
  link_set_open(s, TRUE);
  PRINT_TEST_RESULT(link_is_open(s) == TRUE);
  link_destroy(s);
}

void test2_link_is_open() {
  Link *s = NULL;
  PRINT_TEST_RESULT(link_is_open(s) == FALSE);
}

void test1_link_print() {
  Link *s = link_create(4);
  PRINT_TEST_RESULT(link_print(s) == OK);
  link_destroy(s);
}

void test2_link_print(){
  Link *s = NULL;
  PRINT_TEST_RESULT(link_print(s) == ERROR);
}
