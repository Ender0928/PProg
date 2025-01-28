/** 
 * @brief It declares the tests for the inventory module
 * 
 * @file inventory_test.h
 * @author Alfonso Crespo
 * @version 2.0 
 * @date 22-03-2021
 * @copyright GNU Public License
 */

#ifndef INVENTORY_TEST_H
#define INVENTORY_TEST_H

#include "set.h"
#include "test.h"
#include "inventory.h"

void test1_inventory_create();

void test1_inventory_destroy();
void test2_inventory_destroy();

void test1_inventory_add_object();
void test2_inventory_add_object();

void test1_inventory_del_object();
void test2_inventory_del_object();

void test1_inventory_isFull();
void test2_inventory_isFull();
void test3_inventory_isFull();

void test1_inventory_find_object();
void test2_inventory_find_object();



#endif