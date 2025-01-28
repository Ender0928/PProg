/** 
 * @brief It tests inventory module
 * 
 * @file inventory_test.c
 * @author Alfonso Crespo
 * @version 3.0 
 * @date 22-03-2021
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "inventory_test.h"

#define MAX_TEST2 12

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


  if (all || test == 1) test1_inventory_create();
  if (all || test == 2) test1_inventory_destroy();
  if (all || test == 3) test2_inventory_destroy();
  if (all || test == 4) test1_inventory_add_object();
  if (all || test == 5) test2_inventory_add_object();
  if (all || test == 6) test1_inventory_del_object();
  if (all || test == 7) test2_inventory_del_object();
  if (all || test == 8) test1_inventory_isFull();
  if (all || test == 9) test2_inventory_isFull();
  if (all || test == 10) test3_inventory_isFull();
  if (all || test == 11) test1_inventory_find_object();
  if (all || test == 12) test2_inventory_find_object();

PRINT_PASSED_PERCENTAGE;

return 1;
}


void test1_inventory_create(){
    int result;
    Inventory *inv;
    inv = inventory_create();
    result=inv!=NULL;
    PRINT_TEST_RESULT(result);
    inventory_destroy(inv);

}

void test1_inventory_destroy(){
    Inventory* inv;
    inv = inventory_create();
    PRINT_TEST_RESULT(inventory_destroy(inv)==OK);
    
}

void test2_inventory_destroy(){
    Inventory* inv=NULL;
    PRINT_TEST_RESULT(inventory_destroy(inv)==ERROR);

}

void test1_inventory_add_object(){
    Inventory *inv;
    Id id = 1;
    inv=inventory_create();
    PRINT_TEST_RESULT(inventory_add_object(inv,id)==OK);
    inventory_destroy(inv);

}

void test2_inventory_add_object(){
    Inventory* inv=NULL;
    Id id = 1;
    PRINT_TEST_RESULT(inventory_add_object(inv,id)==ERROR);
    
}

void test1_inventory_del_object(){
    Inventory *inv;
    Id id = 1;
    inv=inventory_create();
    inventory_add_object(inv,id);
    PRINT_TEST_RESULT(inventory_del_object(inv,id)==OK);
    inventory_destroy(inv);
}

void test2_inventory_del_object(){
    Inventory *inv;
    Id id = 1;
    inv=inventory_create();
    PRINT_TEST_RESULT(inventory_del_object(inv,id)==OK);
    inventory_destroy(inv);

}

void test1_inventory_isFull(){
    Inventory *inv;
    Id i;
    inv=inventory_create();
    for(i=0;i<3;i++){
        inventory_add_object(inv,i);
    }
    PRINT_TEST_RESULT(inventory_is_full(inv)==TRUE);

    inventory_destroy(inv);
}

void test2_inventory_isFull(){
    Inventory *inv;
    Id id = 1;
    inv=inventory_create();
    inventory_add_object(inv,id);

    PRINT_TEST_RESULT(inventory_is_full(inv)==FALSE);
    
    inventory_destroy(inv);
}

void test3_inventory_isFull(){
    Inventory *inv;
    inv=inventory_create();
    PRINT_TEST_RESULT(inventory_is_full(inv)==FALSE);
    inventory_destroy(inv);

}

void test1_inventory_find_object(){
    Inventory *inv;
    Id id = 1;
    inv=inventory_create();
    inventory_add_object(inv,id);
    PRINT_TEST_RESULT(inventory_find_object(inv,id)==TRUE);
    inventory_destroy(inv);

}

void test2_inventory_find_object(){
    Inventory *inv;
    Id id = 1;
    inv=inventory_create();

    PRINT_TEST_RESULT(inventory_find_object(inv,id)==FALSE);

    inventory_destroy(inv);
}