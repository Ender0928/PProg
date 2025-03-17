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

 #include "character_test.h" 

 
 #define MAX_TESTS 20
 
 int main(int argc, char **argv) {
     int test = 0;
     int all = 1;
 
     if (argc < 2) {
         printf("Running all tests for module Character:\n");
     } else {
         test = atoi(argv[1]);
         all = 0;
         printf("Running test %d:\t", test);
         if (test < 1 || test > MAX_TESTS) {
             printf("Error: unknown test %d\t", test);
             exit(EXIT_SUCCESS);
         }
     }
 
     if (all || test == 1) test1_character_create();
     if (all || test == 2) test2_character_create();
     if (all || test == 3) test1_character_set_name();
     if (all || test == 4) test2_character_set_name();
     if (all || test == 5) test1_character_set_gdesc();
     if (all || test == 6) test2_character_set_gdesc();
     if (all || test == 7) test1_character_set_health();
     if (all || test == 8) test2_character_set_health();
     if (all || test == 9) test1_character_set_friendly();
     if (all || test == 10) test2_character_set_friendly();
     if (all || test == 11) test1_character_set_message();
     if (all || test == 12) test2_character_set_message();
     if (all || test == 13) test1_character_set_location();
     if (all || test == 14) test2_character_set_location();
     if (all || test == 15) test1_character_print();
     if (all || test == 16) test2_character_print();
     
     PRINT_PASSED_PERCENTAGE;
     
     return 0;
 }
 
 void test1_character_create() {
     Character *c = character_create(1);
     PRINT_TEST_RESULT(c != NULL);
     character_destroy(c);
 }
 
 void test2_character_create() {
     Character *c = character_create(NO_ID);
     PRINT_TEST_RESULT(c == NULL);
 }
 
 void test1_character_set_name() {
     Character *c = character_create(1);
     PRINT_TEST_RESULT(character_set_name(c, "Hero") == OK);
     character_destroy(c);
 }
 
 void test2_character_set_name() {
     Character *c = NULL;
     PRINT_TEST_RESULT(character_set_name(c, "Hero") == ERROR);
 }
 
 void test1_character_set_gdesc() {
     Character *c = character_create(1);
     PRINT_TEST_RESULT(character_set_gdesc(c, "@----") == OK);
     character_destroy(c);
 }
 
 void test2_character_set_gdesc() {
     Character *c = NULL;
     PRINT_TEST_RESULT(character_set_gdesc(c, "@----") == ERROR);
 }
 
 void test1_character_set_health() {
     Character *c = character_create(1);
     PRINT_TEST_RESULT(character_set_health(c, 5) == OK);
     character_destroy(c);
 }
 
 void test2_character_set_health() {
     Character *c = NULL;
     PRINT_TEST_RESULT(character_set_health(c, 5) == ERROR);
 }
 
 void test1_character_set_friendly() {
     Character *c = character_create(1);
     PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == OK);
     character_destroy(c);
 }
 
 void test2_character_set_friendly() {
     Character *c = NULL;
     PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == ERROR);
 }
 
 void test1_character_set_message() {
     Character *c = character_create(1);
     PRINT_TEST_RESULT(character_set_message(c, "Hello!") == OK);
     character_destroy(c);
 }
 
 void test2_character_set_message() {
     Character *c = NULL;
     PRINT_TEST_RESULT(character_set_message(c, "Hello!") == ERROR);
 }
 
 void test1_character_set_location() {
     Character *c = character_create(1);
     PRINT_TEST_RESULT(character_set_location(c, 10) == OK);
     character_destroy(c);
 }
 
 void test2_character_set_location() {
     Character *c = NULL;
     PRINT_TEST_RESULT(character_set_location(c, 10) == ERROR);
 }
 
 void test1_character_print() {
     Character *c = character_create(1);
     PRINT_TEST_RESULT(character_print(c) == OK);
     character_destroy(c);
 }
 
 void test2_character_print() {
     Character *c = NULL;
     PRINT_TEST_RESULT(character_print(c) == ERROR);
 }
 