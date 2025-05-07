/** 
 * @brief It declares the tests for the player module
 *
 * @file player_test.h
 * @author Carlos Tabernero
 * @version 2.0
 * @date 17-03-2025
 */

 #ifndef PLAYER_TEST_H
 #define PLAYER_TEST_H
 
 #include "player.h"
 #include "test.h"
 
 /**
  * @brief Tests for player_create
  */
 void test1_player_create();
 void test2_player_create();
 
 /**
  * @brief Tests for player_set_name
  */
 void test1_player_set_name();
 void test2_player_set_name();

 /**
  * @brief Tests for player_destroy
  */
 void test1_player_destroy();
 void test2_player_destroy();
 
 /**
  * @brief Tests for player_set_location
  */
 void test1_player_set_location();
 void test2_player_set_location();
 
 /**
  * @brief Tests for player_add_object
  */
 void test1_player_add_object();
 void test2_player_add_object();
 
 /**
  * @brief Tests for player_remove_object
  */
 void test1_player_remove_object();
 void test2_player_remove_object();
 
 /**
  * @brief Tests for player_set_health
  */
 void test1_player_set_health();
 void test2_player_set_health();

 /**
  * @brief Tests for player_set_backpack
  */
 void test1_player_set_backpack();
 void test2_player_set_backpack();
 
 /**
  * @brief Tests for player_set_turn
  */
 void test1_player_set_turn();
 void test2_player_set_turn();
 
 /**
  * @brief Tests for player_set_max_objects
  */
 void test1_player_set_max_objects();
 void test2_player_set_max_objects();
 
 /**
  * @brief Tests for player_set_graphic_desc
  */
 void test1_player_set_graphic_desc();
 void test2_player_set_graphic_desc();
 
 /**
  * @brief Tests for player_get_turn
  */
 void test1_player_get_turn();
 void test2_player_get_turn();
 
 /**
  * @brief Tests for player_get_backpack
  */
 void test1_player_get_backpack();
 void test2_player_get_backpack();
 
 /**
  * @brief Tests for player_get_health
  */
 void test1_player_get_health();
 void test2_player_get_health();
 
 /**
  * @brief Tests for player_get_location
  */
 void test1_player_get_location();
 void test2_player_get_location();
 
 /**
  * @brief Tests for player_get_name
  */
 void test1_player_get_name();
 void test2_player_get_name();
 
 /**
  * @brief Tests for player_get_id
  */
 void test1_player_get_id();
 void test2_player_get_id();
 
 /**
  * @brief Tests for player_get_graphic_desc
  */
 void test1_player_get_graphic_desc();
 void test2_player_get_graphic_desc();
 
  /**
  * @brief Tests for player_has_object
  */
 void test1_player_has_object();
 void test2_player_has_object();
 
 /**
  * @brief Tests for player_inventory_is_full
  */
 void test1_player_inventory_is_full();
 void test2_player_inventory_is_full();
 
 /**
  * @brief Tests for player_inventory_is_empty
  */
 void test1_player_inventory_is_empty();
 void test2_player_inventory_is_empty();
 
 /**
  * @brief Tests for player_print
  */
 void test1_player_print();
 void test2_player_print();
 
 #endif /* PLAYER_TEST_H */
 