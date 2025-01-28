/** 
 * @brief It tests enemy module
 * 
 * @file enemy_test.c
 * @author Alfonso Crespo
 * @version 3.0 
 * @date 02-03-2021
 * @copyright GNU Public License
 */


#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "enemy.h"
#include "enemy_test.h"
#include "test.h"

#define MAX_TEST3 14
#define ENEMY_TEST_LOC 122
#define ENEMY_TEST_HEAL 10

int main(int argc, char** argv) {

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Enemy:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TEST3) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1) test1_enemy_create();
  if (all || test == 2) test1_enemy_destroy();
  if (all || test == 3) test2_enemy_destroy();
  if (all || test == 4) test1_enemy_get_id();
  if (all || test == 5) test2_enemy_get_id();
  if (all || test == 6) test1_enemy_get_name();
  if (all || test == 7) test2_enemy_get_name();
  if (all || test == 8) test1_enemy_set_name();
  if (all || test == 9) test2_enemy_set_name();
  if (all || test == 10) test3_enemy_set_name();
  if (all || test == 11) test1_enemy_get_location();
  if (all || test == 12) test2_enemy_get_location();
  if (all || test == 13) test1_enemy_set_location();
  if (all || test == 14) test2_enemy_set_location();



  PRINT_PASSED_PERCENTAGE;




return 1;
}

void test1_enemy_create(){
    Enemy *e;
    int result;
    e = enemy_create(ENEMY_ID);
    result=e!=NULL;
    PRINT_TEST_RESULT(result);
    enemy_destroy(e);

}

void test1_enemy_destroy(){
    Enemy *e;
    e = enemy_create(ENEMY_ID);
    PRINT_TEST_RESULT(enemy_destroy(e)==OK);

}

void test2_enemy_destroy(){
    Enemy *e=NULL;
    PRINT_TEST_RESULT(enemy_destroy(e)==ERROR);

}

void test1_enemy_get_id(){
    Enemy *e;
    e = enemy_create(ENEMY_ID);
    PRINT_TEST_RESULT(enemy_get_id(e) == ENEMY_ID);
    enemy_destroy(e);

}

void test2_enemy_get_id(){
    Enemy *e=NULL;
    PRINT_TEST_RESULT(enemy_get_id(e)==NO_ID);

}

void test1_enemy_get_name(){
    Enemy *e;
    e = enemy_create(ENEMY_ID);
    enemy_set_name(e, "bicho");
    PRINT_TEST_RESULT(strcmp(enemy_get_name(e), "bicho") == ERROR);
    enemy_destroy(e);

}

void test2_enemy_get_name(){
    Enemy *e=NULL;
    PRINT_TEST_RESULT(enemy_get_name(e)==NULL);


}

void test1_enemy_set_name(){
    Enemy *e;
    e = enemy_create(ENEMY_ID);
    PRINT_TEST_RESULT(enemy_set_name(e,"bicho")==OK);
    enemy_destroy(e);

}

void test2_enemy_set_name(){
    Enemy *e=NULL;
    PRINT_TEST_RESULT(enemy_set_name(e, "bicho")==ERROR);
    
}

void test3_enemy_set_name(){
    Enemy *e;
    e = enemy_create(ENEMY_ID);
    PRINT_TEST_RESULT(enemy_set_name(e,NULL)==ERROR);
    enemy_destroy(e);


}

void test1_enemy_get_location(){
    Enemy *e;
    e = enemy_create(ENEMY_ID);
    enemy_set_location(e,ENEMY_TEST_LOC);
    PRINT_TEST_RESULT(enemy_get_location(e)==ENEMY_TEST_LOC);
    enemy_destroy(e);

}

void test2_enemy_get_location(){
    Enemy *e;
    e = enemy_create(ENEMY_ID);
    PRINT_TEST_RESULT(enemy_get_location(e)==NO_ID);
    enemy_destroy(e);

}

void test1_enemy_set_location(){
    Enemy *e;
    e = enemy_create(ENEMY_ID);
    PRINT_TEST_RESULT(enemy_set_location(e,ENEMY_TEST_LOC)==OK);
    enemy_destroy(e);

}

void test2_enemy_set_location(){
    Enemy *e;
    e = enemy_create(ENEMY_ID);
    PRINT_TEST_RESULT(enemy_set_location(e,NO_ID)==ERROR);
    enemy_destroy(e);

}

void test1_enemy_get_health(){
    Enemy *e;
    e = enemy_create(ENEMY_ID);
    enemy_set_health(e,ENEMY_TEST_HEAL);
    PRINT_TEST_RESULT(enemy_get_health(e)==ENEMY_TEST_HEAL);
    enemy_destroy(e);


}

void test2_enemy_get_health(){
    Enemy *e;
    e = enemy_create(ENEMY_ID);
    PRINT_TEST_RESULT(enemy_get_health(e)==-1);
    enemy_destroy(e);


}

void test1_enemy_set_health(){
    Enemy *e;
    e = enemy_create(ENEMY_ID);
    PRINT_TEST_RESULT(enemy_set_health(e,ENEMY_TEST_HEAL)==OK);
    enemy_destroy(e);
    
}

void test2_enemy_set_health(){
    Enemy *e;
    e = enemy_create(ENEMY_ID);
    PRINT_TEST_RESULT(enemy_set_health(e,-1)==ERROR);
    enemy_destroy(e);


}