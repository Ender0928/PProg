#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "link.h"
#include "link_test.h"
#include "test.h"
#include "types.h"


int main(int argc, char** argv) {

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Link:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_LINK_TEST) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }
  
  if (all || test == 1) test1_link_create();

  if (all || test == 2) test1_link_destroy();
  if (all || test == 3) test2_link_destroy();

  if (all || test == 4) test1_link_get_id();
  if (all || test == 5) test2_link_get_id();
  
  if (all || test == 6) test1_link_set_name();
  if (all || test == 7) test2_link_set_name();
  if (all || test == 8) test3_link_set_name();

  if (all || test == 8) test1_link_get_name();
  if (all || test == 9) test2_link_get_name();

  if (all || test == 10) test1_link_set_origin();
  if (all || test == 11) test2_link_set_origin();
  if (all || test == 12) test3_link_set_origin();

  if (all || test == 13) test1_link_get_origin();
  if (all || test == 14) test2_link_get_origin();

  if (all || test == 15) test1_link_set_destination();
  if (all || test == 16) test2_link_set_destination();

  if (all || test == 17) test1_link_get_destination();
  if (all || test == 18) test2_link_get_destination();

  if (all || test == 19) test1_link_set_direction();
  if (all || test == 20) test2_link_set_direction();
  if (all || test == 21) test3_link_set_direction();

  if (all || test == 22) test1_link_get_direction();
  if (all || test == 23) test2_link_get_direction();

  if (all || test == 24) test1_link_set_status();
  if (all || test == 25) test2_link_set_status();
  
  if (all || test == 26) test1_link_get_status();
  if (all || test == 27) test2_link_get_status();
  
PRINT_PASSED_PERCENTAGE;

return 1;
}


void test1_link_create(){
    int result;
    Link* l;
    l = link_create(1);
    result=l!=NULL;
    PRINT_TEST_RESULT(result);
    link_destroy(l);

}

void test1_link_destroy() {
    Link *l;
    l = link_create(1);
    PRINT_TEST_RESULT(link_destroy(l)==OK);

}

void test2_link_destroy(){
    Link* l = NULL;
    
    PRINT_TEST_RESULT(link_destroy(l)==ERROR);

}
void test1_link_get_id(){
    Link *l;
    
    l = link_create(20);
    PRINT_TEST_RESULT(link_get_id(l) == 20);
    link_destroy(l);
}

void test2_link_get_id(){
    Link *l = NULL;
  PRINT_TEST_RESULT(link_get_id(l) == NO_ID);
}

void test1_link_set_name(){
    Link *l;
  l = link_create(1);
  link_set_name(l, "adios");
  PRINT_TEST_RESULT(strcmp(link_get_name(l), "adios") == 0);
  link_destroy(l);
}

void test2_link_set_name(){
    Link *l = NULL;
  PRINT_TEST_RESULT(link_set_name(l, "hola") == ERROR);
}

void test3_link_set_name() {
  Link *l;
  l = link_create(5);
  PRINT_TEST_RESULT(link_set_name(l, NULL) == ERROR);
  link_destroy(l);
}

void test1_link_get_name() {
  Link *l;
  l = link_create(5);
  link_set_name(l, "hola");
  PRINT_TEST_RESULT(strcmp(link_get_name(l), "hola") == 0);
  link_destroy(l);
}

void test2_link_get_name() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_direction(l) == NO_ID);
}

void test1_link_set_origin() {
  Link *l;
  l = link_create(5);
  PRINT_TEST_RESULT(link_set_origin(l, 4) == OK);
  link_destroy(l);
}

void test2_link_set_origin() {
  Link *l = NULL;
  Id id = 5;
  PRINT_TEST_RESULT(link_set_origin(l, id) == ERROR);
}

void test3_link_set_origin() {
  Link *l;
  l = link_create(5);
  PRINT_TEST_RESULT(link_set_origin(l, NO_ID) == ERROR);
  link_destroy(l);
}

void test1_link_get_origin(){
  Link *l;
  l = link_create(5);
  link_set_origin(l, 3);
  PRINT_TEST_RESULT(link_get_origin(l) == 3);
  link_destroy(l);
}

void test2_link_get_origin(){
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_origin(l) == NO_ID);
}

void test1_link_set_destination() {
  Link *l;
  l = link_create(5);
  PRINT_TEST_RESULT(link_set_destination(l, 4) == OK);
  link_destroy(l);
}

void test2_link_set_destination() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_set_destination(l, 4) == ERROR);
}

void test1_link_get_destination() {
  Link *l;
  l = link_create(5);
  link_set_destination(l, 11);
  PRINT_TEST_RESULT(link_get_destination(l) == 11);
  link_destroy(l);
}

void test2_link_get_destination() {
  Link *l=NULL;
  PRINT_TEST_RESULT(link_get_destination(l) == NO_ID);
}



void test1_link_set_direction(){
  Link *l;
  DIRECTION d = -1;
  l = link_create(5);
  PRINT_TEST_RESULT(link_set_direction(l, d)== ERROR);
  link_destroy(l);
}

void test2_link_set_direction(){
  Link *l = NULL;
  DIRECTION d = W;
  PRINT_TEST_RESULT(link_set_direction(l, d) == ERROR);
}

void test3_link_set_direction(){
  Link *l;
  DIRECTION d = W;
  l = link_create(5);
  PRINT_TEST_RESULT(link_set_direction(l, d) == OK);
  link_destroy(l);
}

void test1_link_get_direction() {
  Link *l;
  DIRECTION d = W;
  l = link_create(5);
  link_set_direction(l, d);
  PRINT_TEST_RESULT(link_get_direction(l) == d);
  link_destroy(l);
}

void test2_link_get_direction() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_direction(l) == NO_ID);
}





void test1_link_set_status() {
  Link *l;
  l = link_create(5);
  PRINT_TEST_RESULT(link_set_status(l, ERROR)== OK);
  link_destroy(l);
}

void test2_link_set_status() {
  Link *l=NULL;
  PRINT_TEST_RESULT(link_set_status(l, ERROR) == ERROR);
}

void test1_link_get_status(){
  Link *l;
  l = link_create(5);
  link_set_status(l, OK);
  PRINT_TEST_RESULT(link_get_status(l) == OK);
  link_destroy(l);
}

void test2_link_get_status(){
  Link *l=NULL;
  PRINT_TEST_RESULT(link_get_status(l) == ERROR);
    
}