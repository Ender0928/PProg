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
 * @test Test function for object_mobable setting
 * @pre object_mobable = FALSE (point to object = NON NULL)
 * @post Output==OK
 */
void test1_object_set_mobable();

/**
 * @test Test function for object_mobable setting
 * @pre pointer to object_mobable = TRUE (point to object = NULL) 
 * @post Output==ERROR
 */
void test2_object_set_mobable();

/**
 * @test Test function for object_mobable getting
 * @pre object_mobable = FALSE (point to object = NON NULL) 
 * @post Output==FALSE
 */
void test1_object_get_mobable();

/**
 * @test Test function for object_mobable getting
 * @pre object_mobable = TRUE (point to object = NULL) 
 * @post Output==NO_ID
 */
void test2_object_get_mobable();

/**
 * @test Test function for object_dependecy setting
 * @pre Object DEPENDECY (Pointed to object = NON NULL)
 * @post Object_ID==OK
 */
void test1_object_set_dependecy();

/**
 * @test Test function for object_dependecy setting
 * @pre Object DEPENDECY (Pointed to object = NULL)
 * @post Object_dependecy==ERROR
 */
void test2_object_set_dependecy();

/**
 * @test Test function for object_dependecy getting
 * @pre Object DEPENDECY (Pointed to object = NON NULL)
 * @post Object_DEPENDECY == Supplied Object id dependecy
 */
void test1_object_get_dependecy();

/**
 * @test Test function for object_dependecy getting
 * @pre Pointed to object = NULL
 * @post Output==NO_ID
 */
void test2_object_get_dependecy();

/**
 * @test Test function for object_open setting
 * @pre Object OPEN (Pointed to object = NON NULL)
 * @post Object_OPEN==OK
 */
void test1_object_set_open();

/**
 * @test Test function for object_open setting
 * @pre Object OPEN (Pointed to object = NULL)
 * @post Object_OPEN==ERROR
 */
void test2_object_set_open();

/**
 * @test Test function for object_open getting
 * @pre Object OPEN (Pointed to object = NON NULL)
 * @post Object_OPEN == Supplied Object id open
 */
void test1_object_get_open();

/**
 * @test Test function for object_open getting
 * @pre Pointed to object = NULL
 * @post Output==NO_ID
 */
void test2_object_get_open();

/**
 * @test Test function for object_illuminate setting
 * @pre object_illuminate = FALSE (point to object = NON NULL)
 * @post Output==OK
 */
void test1_object_set_illuminate();

/**
 * @test Test function for object_illuminate setting
 * @pre object_illuminate = TRUE (point to object = NULL)
 * @post Output==ERROR
 */
void test1_object_set_illuminate();

/**
 * @test Test function for object_illuminate getting
 * @pre object_illuminate = FALSE (point to object = NON NULL) 
 * @post Output==FALSE
 */
void test1_object_get_illuminate();

/**
 * @test Test function for object_illuminate getting
 * @pre Point to object = NULL 
 * @post Output==NO_ID
 */
void test2_object_get_illuminate();

/**
 * @test Test function for object_turnedon setting
 * @pre object_turnedon = FALSE (point to object = NON NULL)
 * @post Output==OK
 */
void test1_object_set_turnedon();

/**
 * @test Test function for object_turnedon setting
 * @pre object_turnedon = TRUE (point to object = NULL)
 * @post Output==ERROR
 */
void test2_object_set_turnedon();

/**
 * @test Test function for object_open getting
 * @pre object_illuminate = FALSE (point to object = NON NULL)
 * @post Output==FALSE
 */
void test1_object_get_turnedon();

/**
 * @test Test function for object_turnedon getting
 * @pre Pointed to object = NULL
 * @post Output==NO_ID
 */
void test2_object_get_turnedon();

#endif