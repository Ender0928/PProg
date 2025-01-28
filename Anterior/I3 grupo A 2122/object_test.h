/** 
 * @brief It declares the tests for the object module
 * 
 * @file object_test.h
 * @author Daniel Tirado
 * @version 2.0 
 * @date 24-03-2022
 * @copyright GNU Public License
 */

#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H

/**
 * @test Test object creation
 * @pre Object ID 
 * @post Non NULL pointer to object 
 */
void test1_object_create();

/**
 * @test Test object creation
 * @pre Object ID 
 * @post Object_ID == Supplied Object Id
 */
void test2_object_create();

/**
 * @test Test object destruction
 * @pre Object ID
 * @post Output==OK 
 */
void test1_object_destroy();

/**
 * @test Test object destruction
 * @pre Object ID
 * @post Ouput==ERROR
 */
void test2_object_destroy();

/**
 * @test Test function for object_id setting
 * @pre Object ID
 * @post Object_ID == Supplied Object Id
 */
void test1_object_set_id();

/**
 * @test Test function for object_id setting
 * @pre Object ID
 * @post Output==ERROR
 */
void test2_object_set_id();

/**
 * @test Test function for object_id getting
 * @pre Object ID
 * @post Object_ID == Supplied Object Id
 */
void test1_object_get_id();

/**
 * @test Test function for object_id setting
 * @pre Object ID
 * @post Object_ID == NO_ID
 */
void test2_object_get_id();

/**
 * @test Test function for object_name setting
 * @pre String with object name
 * @post Ouput==OK 
 */
void test1_object_set_name();

/**
 * @test Test function for object_name setting
 * @pre String with object name
 * @post Ouput==ERROR
 */
void test2_object_set_name();

/**
 * @test Test function for object_name setting
 * @pre pointer to object_name = NULL (point to object = NON NULL) 
 * @post Output==ERROR
 */
void test3_object_set_name();

/**
 * @test Test function for object_name getting
 * @pre Object name
 * @post Output==ERROR
 */
void test1_object_get_name();

/**
 * @test Test function for object_name getting
 * @pre pointer to object = NULL
 * @post Output==NULL
 */
void test2_object_get_name();

#endif