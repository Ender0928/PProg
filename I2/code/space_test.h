#ifndef SPACE_TEST_H
#define SPACE_TEST_H

#include "space.h"
#include "test.h"

/** 
 * @brief Test the space creation function
 */
void test1_space_create();
void test2_space_create();

/** 
 * @brief Test the function for setting the name of a space
 */
void test1_space_set_name();
void test2_space_set_name();

/** 
 * @brief Test the function for setting the north link of a space
 */
void test1_space_set_north();
void test2_space_set_north();

/** 
 * @brief Test the function for setting the south link of a space
 */
void test1_space_set_south();
void test2_space_set_south();

/** 
 * @brief Test the function for setting the east link of a space
 */
void test1_space_set_east();
void test2_space_set_east();

/** 
 * @brief Test the function for setting the west link of a space
 */
void test1_space_set_west();
void test2_space_set_west();

/** 
 * @brief Test the function for adding an object to a space
 */
void test1_space_add_object();
void test2_space_add_object();

/** 
 * @brief Test the function for removing an object from a space
 */
void test1_space_remove_object();
void test2_space_remove_object();

/** 
 * @brief Test the function for checking if a space has an object
 */
void test1_space_has_object();
void test2_space_has_object();

/** 
 * @brief Test the function for retrieving objects from a space
 */
void test1_space_get_objects();
void test2_space_get_objects();

/** 
 * @brief Test the function for getting the graphic description of a space
 */
void test1_space_get_gdesc();
void test2_space_get_gdesc();

/** 
 * @brief Test the function for setting the graphic description of a space
 */
void test1_space_set_gdesc();
void test2_space_set_gdesc();

/** 
 * @brief Test the function for printing a space
 */
void test1_space_print();
void test2_space_print();

#endif /* SPACE_TEST_H */