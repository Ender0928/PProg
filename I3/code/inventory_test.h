 /** 
 * @brief It declares the tests for the inventory module
 *
 * @file inventory_test.h
 * @author Carlos Tabernero
 * @version 2.0
 * @date 20-03-2025
 */

 #ifndef INVENTORY_TEST_H
 #define INVENTORY_TEST_H
 
 #include "inventory.h"
 #include "test.h"

 /** 
  * @brief Tests for inventory_create
  */
void test1_inventory_create();
void test2_inventory_create();
 
 /**
  * @brief Tests for inventory_set_name
  */
void test1_inventory_is_full();
void test2_inventory_is_full();
 
 /**
  * @brief Tests for inventory_get_name
  */
void test1_inventory_is_empty();
void test2_inventory_is_empty();
 
 /**
  * @brief Tests for inventory_set_origin
  */
void test1_inventory_add_object();
void test2_inventory_add_object();
 
 /**
  * @brief Tests for inventory_get_origin
  */
void test1_inventory_remove_object();
void test2_inventory_remove_object();
 
 /**
  * @brief Tests for inventory_set_destination
  */
void test1_inventory_find_object();
void test2_inventory_find_object();
 
 /**
  * @brief Tests for inventory_get_destination
  */
void test1_inventory_set_max_value();
void test2_inventory_set_max_value();
 
 /**
  * @brief Tests for inventory_set_direction
  */
void test1_inventory_print();
void test2_inventory_print();
 
 #endif /* INVENTORY_TEST_H */
 