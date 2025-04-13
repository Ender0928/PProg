#ifndef SET_TEST_H
#define SET_TEST_H

#include "set.h"
#include "test.h"

/** 
 * @brief Test the set creation function
 */
void test1_set_create();

/** 
 * @brief Test the set destruction function (valid case)
 */
void test1_set_destroy();

/** 
 * @brief Test the set destruction function (invalid case)
 */
void test2_set_destroy();

/** 
 * @brief Test the function for adding an object to a set (valid case)
 */
void test1_set_add_object();

/** 
 * @brief Test the function for adding an object to a set (invalid case)
 */
void test2_set_add_object();

/** 
 * @brief Test the function for deleting an object from a set (valid case)
 */
void test1_set_del_object();

/** 
 * @brief Test the function for deleting an object from a set (invalid case)
 */
void test2_set_del_object();

/** 
 * @brief Test the function for finding an object in a set (object not present)
 */
void test1_set_find_object();

/** 
 * @brief Test the function for finding an object in a set (object present)
 */
void test2_set_find_object();

#endif /* SET_TEST_H */