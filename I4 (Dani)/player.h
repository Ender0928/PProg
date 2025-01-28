/**
 * @brief It defines the player interface
 *
 * @file space.h
 * @author Daniel Tirado and Alfonso Crespo
 * @version 2.0
 * @date 12-02-2022
 */


#ifndef PLAYER_H
#define PLAYER_H
#include "types.h"

#define P 1


typedef struct _Player Player;


/**
  * @brief It creates a new player
  * @author Daniel Tirado and Alfonso Crespo
  *
  * player_create allocates memory for a new player and initializes its members
  * @param id the identification number for the new object
  * @return a new Player, initialized
  */
Player * player_create (Id id);

/**
  * @brief It destroys a new player
  * @author Daniel Tirado and Alfonso Crespo
  * player_destroy frees the previous memory allocation 
  *  for a player
  * @param player pointer to the player that must be destroyed
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS player_destroy (Player *player);

/**
  * @brief It gets the id of a player
  * @author Daniel Tirado and Alfonso Crespo
  * @param player a pointer to the player  
  * @return the id of the player
  */
Id player_get_id(Player *player);

/**
  * @brief It gets the name of a player
  * @author Daniel Tirado and Alfonso Crespo
  * @param player a pointer to the player  
  * @return the name of the player
  */
const char * player_get_name(Player *player);

/**
  * @brief It sets the name of a player
  * @author Daniel Tirado and Alfonso Crespo
  * @param player a pointer to the player
  * @param name a pointer to the name  
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS player_set_name(Player *player, char *name);

/**
  * @brief It gets the position of a player
  * @author Daniel Tirado and Alfonso Crespo
  * @param player a pointer to the player  
  * @return the id of the location of the player
  */
Id player_get_location(Player *player);

/**
  * @brief It sets the location of a player
  * @author Daniel Tirado and Alfonso Crespo
  * @param player a pointer to the player
  * @param location the id of the location 
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS player_set_location(Player *player, Id location); /*It set the player location*/

/**
  * @brief It gets the id of the object of the player
  * @author Daniel Tirado and Alfonso Crespo
  * @param player a pointer to the player  
  * @return the id of the object of the player
  */
Id player_get_object(Player *player);

/**
  * @brief It sets the object of the player
  * @author Daniel Tirado and Alfonso Crespo
  * @param player a pointer to the player
  * @param object the id of the object
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS player_set_object (Player *player, Id object);


/**
  * @brief It gets the id of the object of the player
  * @author Daniel Tirado and Alfonso Crespo
  * @param player a pointer to the player  
  * @return the id of the object of the player
  */
int player_get_health(Player *player);


/**
  * @brief It sets the health of the player
  * @author Alfonso Crespo
  * @param player a pointer to the player
  * @param health the new health of the player
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS player_set_health(Player *player, int health);

/**
  * @brief It prints the player information
  * @author Alfonso Crespo
  * This fucntion shows the id of the player, his name, his location and his inventory
  * @param player a pointer to the player
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS player_print(Player* player);

/**
  * @brief it finds if the given id is in the inventory of the player
  * @author Alfonso Crespo
  * @param player pointer to the player
  * @param object the id that must be searched
  * @return TRUE, if the id is in the inventory or FALSE if it is not
  */
BOOL player_find_object(Player* player,Id object);

/**
  * @brief It adds a new id to the inventory of the player
  * @author Alfonso Crespo
  * @param player pointer to the set
  * @param object the id that must be added
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS player_inv_add_object(Player* player,Id object);

/**
  * @brief It delates an id from the inventory of the player
  * @author Alfonso Crespo
  * @param player pointer to the set
  * @param object the id that must be delated
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS player_inv_del_object(Player* player,Id object);

/**
  * @brief it verifies if the inventory of the player is full or not
  * @author Alfonso Crespo
  * @param player pointer to the player
  * @return TRUE, if the inventory is full or FALSE if it is not
  */
BOOL player_inv_isFull(Player* player);

/**
 * @brief player_set_MaxInv set the max num of objects a player can carry
 * 
 * @param player 
 * @param MaxInv 
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS player_set_MaxInv(Player* player,int MaxInv);

#endif




