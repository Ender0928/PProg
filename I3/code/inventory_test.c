/** 
 * @brief It tests inventory module
 * 
 * @file inventory_test.c
 * @author Carlos Tabernero
 * @version 0.0 
 * @date 20-03-2025
 * @copyright GNU Public License
 */

 #include <stdio.h> 
 #include <stdlib.h> 
 #include <string.h> 

 #include "inventory_test.h"
 #include "inventory.h"

 
 #define MAX_TESTS 30
 
 /** 
  * @brief Main function for INVENTORY unit tests. 
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
     printf("Running all test for module Inventory:\n");
   } else {
     test = atoi(argv[1]);
     all = 0;
     printf("Running test %d:\t", test);
     if (test < 1 && test > MAX_TESTS) {
       printf("Error: unknown test %d\t", test);
       exit(EXIT_SUCCESS);
     }
   }

  
   if (all || test == 1) test1_inventory_create();

   if (all || test == 2) test1_inventory_is_full();
   if (all || test == 3) test2_inventory_is_full();
   if (all || test == 4) test1_inventory_is_empty();
   if (all || test == 5) test2_inventory_is_empty();
   if (all || test == 6) test1_inventory_add_object();
   if (all || test == 7) test2_inventory_add_object();
   if (all || test == 8) test1_inventory_remove_object();
   if (all || test == 9) test2_inventory_remove_object();
   if (all || test == 10) test1_inventory_find_object();
   if (all || test == 11) test2_inventory_find_object();
   if (all || test == 12) test1_inventory_set_max_value();
   if (all || test == 13) test2_inventory_set_max_value();
   if (all || test == 14) test1_inventory_print();
   if (all || test == 15) test2_inventory_print();
 
   PRINT_PASSED_PERCENTAGE;
 
   return 1;
 }
 
 void test1_inventory_create() {
   Inventory *s = inventory_create();
   PRINT_TEST_RESULT(s != NULL);
   inventory_destroy(s);
 }
 

 
 void test1_inventory_is_full(){
    Inventory *s = inventory_create();
    PRINT_TEST_RESULT(inventory_is_full(s) == FALSE);
    inventory_destroy(s);
  }
  
  void test2_inventory_is_full() {
    Inventory *s = NULL;
    PRINT_TEST_RESULT(inventory_is_full(s) == TRUE);
  }

  void test1_inventory_is_empty(){
    Inventory *s = inventory_create();
    PRINT_TEST_RESULT(inventory_is_empty(s) == TRUE);
    inventory_destroy(s);
  }
  
  void test2_inventory_is_empty() {
    Inventory *s = inventory_create();
    inventory_add_object(s, 3);
    PRINT_TEST_RESULT(inventory_is_empty(s) == FALSE);
    inventory_destroy(s);
  }

  void test1_inventory_add_object() {
    Inventory *s = inventory_create();
    PRINT_TEST_RESULT(inventory_add_object(s, 5) == OK);
    inventory_destroy(s);
  }
  
  void test2_inventory_add_object() {
    Inventory *s = NULL;
    PRINT_TEST_RESULT(inventory_add_object(s, 5) == ERROR);
  }
  
  void test1_inventory_remove_object() {
    Inventory *s = inventory_create();
    inventory_add_object(s, 5);
    PRINT_TEST_RESULT(inventory_remove_object(s, 5) == OK);
    inventory_destroy(s);
  }
  
  void test2_inventory_remove_object() {
    Inventory *s = NULL;
    PRINT_TEST_RESULT(inventory_remove_object(s, 5) == ERROR);
  }
  
  void test1_inventory_find_object() {
    Inventory *s = inventory_create();
    inventory_add_object(s, 5);
    PRINT_TEST_RESULT(inventory_find_object(s, 5)==TRUE);
    inventory_destroy(s);
  }

  void test2_inventory_find_object() {
    Inventory *s = NULL;
    PRINT_TEST_RESULT(inventory_find_object(s, 2)==FALSE);
  }

  void test1_inventory_set_max_value() {
    Inventory *s = inventory_create();
    PRINT_TEST_RESULT(inventory_set_max_value(s, 10)==OK);
    inventory_destroy(s);
  }

  void test2_inventory_set_max_value() {
    Inventory *s = NULL;
    PRINT_TEST_RESULT(inventory_set_max_value(s, 10)==ERROR);
  }

  void test1_inventory_print() {
    Inventory *s = inventory_create();
    PRINT_TEST_RESULT(inventory_print(s)==OK);
    inventory_destroy(s);
  }

  void test2_inventory_print() {
    Inventory *s = NULL;
    PRINT_TEST_RESULT(inventory_print(s)==ERROR);
  }












 