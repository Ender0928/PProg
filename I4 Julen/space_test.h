/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Profesores Pprog
 * @version 2.0 
 * @date 09-03-2021
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Non NULL pointer to space 
 */
void test1_space_create();

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Space_ID == Supplied Space Id
 */
void test2_space_create();

/**
 * @test Test function for space_name setting
 * @pre String with space name
 * @post Ouput==OK 
 */
void test1_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space = NULL 
 * @post Output==ERROR
 */
void test2_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space_name = NULL (point to space = NON NULL) 
 * @post Output==ERROR
 */
void test3_space_set_name();
void test1_space_get_id();
void test2_space_get_id();
void test1_space_set_object();
void test2_space_set_object();
void test1_space_get_name();
void test2_space_get_name();
void test1_space_get_object();
void test2_space_get_object();
void test3_space_get_object();
void test1_space_find_object();
void test2_space_find_object();
void test3_space_find_object();
void test1_space_add_object();
void test2_space_add_object();
void test1_space_del_object();
void test2_space_del_object();

/**
 * @test Test function for space_light getting
 * @pre space light
 * @post Output==TRUE
 */
void test1_space_get_light();

/**
 * @test Test function for space_light getting
 * @pre  pointer to space = NULL
 * @post Output==NULL
 */
void test2_space_get_light();

/**
 * @test Test function for space_light setting
 * @pre pointer to space = NON NULL
 * @post Output==OK
 */
void test1_space_set_light();

/**
 * @test Test function for space_light setting
 * @pre pointer to space = NULL
 * @post Output==ERROR
 */
void test2_space_set_light();


#endif
