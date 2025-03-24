/**
 * @brief It defines the player interface
 *
 * @file space.h
 * @author Javier and Rubén
 * @version 1.0
 */


#ifndef PLAYER_H
#define PLAYER_H
#include "types.h"
#include "inventory.h"

#define P 1


typedef struct _Player Player;


/**
  * @brief It creates a new player
  * @author Javier and Rubén
  *
  * player_create allocates memory for a new player and initializes its members
  * @param id the identification number for the new object
  * @return a new Player, initialized
  */
Player * player_create (Id id);

/**
  * @brief It destroys a new player
  * @author Javier and Rubén
  * player_destroy frees the previous memory allocation 
  *  for a player
  * @param player pointer to the player that must be destroyed
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status player_destroy (Player *player);

/**
  * @brief It gets the id of a player
  * @author Javier and Rubén
  * @param player a pointer to the player  
  * @return the id of the player
  */
Id player_get_id(Player *player);

/**
  * @brief It gets the name of a player
  * @author Javier and Rubén
  * @param player a pointer to the player  
  * @return the name of the player
  */
const char * player_get_name(Player *player);

/**
  * @brief It sets the name of a player
  * @author Javier and Rubén
  * @param player a pointer to the player
  * @param name a pointer to the name  
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status player_set_name(Player *player, char *name);

/**
  * @brief It gets the position of a player
  * @author Javier and Rubén
  * @param player a pointer to the player  
  * @return the id of the location of the player
  */
Id player_get_location(Player *player);

/**
  * @brief It sets the location of a player
  * @author Javier and Rubén
  * @param player a pointer to the player
  * @param location the id of the location 
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status player_set_location(Player *player, Id location); /*It set the player location*/

/**
  * @brief It adds the object of the player's inventory
  * @author Javier and Rubén
  * @param player a pointer to the player
  * @param object the id of the object
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status player_add_object (Player *player, Id object); /*It set the object of the player*/

/**
  * @brief It removes the object of the player's inventory
  * @param player a pointer to the player
  * @param object the id of the object
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status player_remove_object(Player *player, Id object);
/**
  * @brief It gets the health of the player
  * @param player a pointer to the player  
  * @return the health of the player
  */
int player_get_health(Player *player);

/**
  * @brief It sets the health of the player
  * @param player a pointer to the player
  * @param health the health of the player
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status player_set_health(Player *player, int health);

/**
  * @brief It gets the backpack of the player
  * @param player a pointer to the player  
  * @return the backpack of the player
  */
Inventory *player_get_backpack(Player *player);

/**
  * @brief It sets the backpack of the player
  * @param player a pointer to the player
  * @param backpack the backpack of the player
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status player_set_backpack(Player *player, Inventory *backpack);
/**
  * @brief It prints the player
  * @param player a pointer to the player
  * @return OK, if everything goes well or ERROR if there was some mistake
  */

/**
 * @brief It checks if the player inventory is empty
 * @param player a pointer to the player
 * @return TRUE if the inventory is empty, FALSE otherwise
 */
Bool player_inventory_is_empty(Player *player);

/**
 * @brief It checks if the player inventory is full
 * @param player a pointer to the player
 * @return TRUE if the inventory is full, FALSE otherwise
 */
Bool player_inventory_is_full(Player *player);

/**
 * @brief It checks if the player has an object
 * @param player a pointer to the player
 * @param object the id of the object
 * @return TRUE if the player has the object, FALSE otherwise
 */
Status player_has_object(Player *player, Id object);

/**
 * @brief It sets the maximum number of objects of the backpack of the player
 * @param player a pointer to the player
 * @param max_objects the maximum number of objects
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_max_objects(Player *player, int max_objects);

/**
 * @brief It sets the graphic description of the player
 * @param player a pointer to the player
 * @param gdesc the graphic description
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_graphic_desc(Player *player, char *gdesc);

/**
 * @brief It gets the graphic description of the player
 * @param player a pointer to the player
 * @return the graphic description of the player
 */
char * player_get_graphic_desc(Player *player);

/**
 * @brief It sets the turn of the player
 * @param player a pointer to the player
 * @param turn the turn of the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_turn(Player *player, Bool turn);

/**
 * @brief It gets the turn of the player
 * @param player a pointer to the player
 * @return the turn of the player
 */
Bool player_get_turn(Player *player);

Status player_print(Player *player);

#endif




