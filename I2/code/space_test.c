/** 
 * @brief It tests space module
 * 
 * @file space_test.c
 * @author Profesores Pprog
 * @version 0.0 
 * @date 17-02-2025
 * @copyright GNU Public License
 */

 #include <stdio.h> 
 #include <stdlib.h> 
 #include <string.h> 
 #include "space.h"
 #include "space_test.h"
 #include "test.h"
 
 #define MAX_TESTS 50
 
 int main(int argc, char** argv) {
     int test = 0;
     int all = 1;
 
     if (argc < 2) {
         printf("Running all test for module Space:\n");
     } else {
         test = atoi(argv[1]);
         all = 0;
         printf("Running test %d:\t", test);
         if (test < 1 || test > MAX_TESTS) {
             printf("Error: unknown test %d\t", test);
             exit(EXIT_SUCCESS);
         }
     }
 
     if (all || test == 1) test1_space_create();
     if (all || test == 2) test2_space_create();
     if (all || test == 3) test1_space_set_name();
     if (all || test == 4) test2_space_set_name();
     if (all || test == 5) test1_space_set_north();
     if (all || test == 6) test2_space_set_north();
     if (all || test == 7) test1_space_set_south();
     if (all || test == 8) test2_space_set_south();
     if (all || test == 9) test1_space_set_east();
     if (all || test == 10) test2_space_set_east();
     if (all || test == 11) test1_space_set_west();
     if (all || test == 12) test2_space_set_west();
     if (all || test == 13) test1_space_add_object();
     if (all || test == 14) test2_space_add_object();
     if (all || test == 15) test1_space_remove_object();
     if (all || test == 16) test2_space_remove_object();
     if (all || test == 17) test1_space_has_object();
     if (all || test == 18) test2_space_has_object();
     if (all || test == 19) test1_space_get_objects();
     if (all || test == 20) test2_space_get_objects();
     if (all || test == 21) test1_space_get_gdesc();
     if (all || test == 22) test2_space_get_gdesc();
     if (all || test == 23) test1_space_set_gdesc();
     if (all || test == 24) test2_space_set_gdesc();
     if (all || test == 25) test1_space_print();
     if (all || test == 26) test2_space_print();
 
     PRINT_PASSED_PERCENTAGE;
     return 1;
 }
 
 void test1_space_create() {
     Space *s = space_create(5);
     PRINT_TEST_RESULT(s != NULL);
     space_destroy(s);
 }
 
 void test2_space_create() {
     Space *s = space_create(NO_ID);
     PRINT_TEST_RESULT(s == NULL);
 }
 
 void test1_space_set_name() {
     Space *s = space_create(1);
     PRINT_TEST_RESULT(space_set_name(s, "Test Space") == OK);
     space_destroy(s);
 }
 
 void test2_space_set_name() {
     PRINT_TEST_RESULT(space_set_name(NULL, "Test Space") == ERROR);
 }
 
 void test1_space_set_north() {
     Space *s = space_create(1);
     PRINT_TEST_RESULT(space_set_north(s, 2) == OK);
     space_destroy(s);
 }
 
 void test2_space_set_north() {
     PRINT_TEST_RESULT(space_set_north(NULL, 2) == ERROR);
 }
 
 void test1_space_set_south() {
     Space *s = space_create(1);
     PRINT_TEST_RESULT(space_set_south(s, 3) == OK);
     space_destroy(s);
 }
 
 void test2_space_set_south() {
     PRINT_TEST_RESULT(space_set_south(NULL, 3) == ERROR);
 }
 
 void test1_space_set_east() {
     Space *s = space_create(1);
     PRINT_TEST_RESULT(space_set_east(s, 4) == OK);
     space_destroy(s);
 }
 
 void test2_space_set_east() {
     PRINT_TEST_RESULT(space_set_east(NULL, 4) == ERROR);
 }
 
 void test1_space_set_west() {
     Space *s = space_create(1);
     PRINT_TEST_RESULT(space_set_west(s, 5) == OK);
     space_destroy(s);
 }
 
 void test2_space_set_west() {
     PRINT_TEST_RESULT(space_set_west(NULL, 5) == ERROR);
 }
 
 void test1_space_add_object() {
     Space *s = space_create(1);
     PRINT_TEST_RESULT(space_add_object(s, 10) == OK);
     space_destroy(s);
 }
 
 void test2_space_add_object() {
     PRINT_TEST_RESULT(space_add_object(NULL, 10) == ERROR);
 }
 
 void test1_space_remove_object() {
     Space *s = space_create(1);
     space_add_object(s, 10);
     PRINT_TEST_RESULT(space_remove_object(s, 10) == OK);
     space_destroy(s);
 }
 
 void test2_space_remove_object() {
     PRINT_TEST_RESULT(space_remove_object(NULL, 10) == ERROR);
 }
 
 void test1_space_has_object() {
     Space *s = space_create(1);
     space_add_object(s, 10);
     PRINT_TEST_RESULT(space_has_object(s, 10) == TRUE);
     space_destroy(s);
 }
 
 void test2_space_has_object() {
     PRINT_TEST_RESULT(space_has_object(NULL, 10) == FALSE);
 }
 
 void test1_space_get_objects() {
     Space *s = space_create(1);
     PRINT_TEST_RESULT(space_get_objects(s) != NULL);
     space_destroy(s);
 }
 
 void test2_space_get_objects() {
     PRINT_TEST_RESULT(space_get_objects(NULL) == NULL);
 }
 
  void test1_space_get_gdesc() {
      Space *s = space_create(1);
      PRINT_TEST_RESULT(space_get_gdesc(s) != NULL);
      space_destroy(s);
  }

  void test2_space_get_gdesc() {
      PRINT_TEST_RESULT(space_get_gdesc(NULL) == NULL);
  }

  void test1_space_set_gdesc() {
      Space *s = space_create(1);
      PRINT_TEST_RESULT(space_set_gdesc(s, "Test graphic description") == OK);
      space_destroy(s);
  }

  void test2_space_set_gdesc() {
      PRINT_TEST_RESULT(space_set_gdesc(NULL, "Test graphic description") == ERROR);
  }

 void test1_space_print() {
     Space *s = space_create(1);
     PRINT_TEST_RESULT(space_print(s) == OK);
     space_destroy(s);
 }
 
 void test2_space_print() {
     PRINT_TEST_RESULT(space_print(NULL) == ERROR);
 }

