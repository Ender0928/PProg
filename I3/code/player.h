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
  * @brief It gets the id of the object of the player
  * @author Javier and Rubén
  * @param player a pointer to the player  
  * @return the id of the object of the player
  */
Id player_get_object(Player *player);

/**
  * @brief It sets the object of the player
  * @author Javier and Rubén
  * @param player a pointer to the player
  * @param object the id of the object
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status player_set_object (Player *player, Id object); /*It set the object of the player*/

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
  * @brief It prints the player
  * @param player a pointer to the player
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status player_print(Player *player);

#endif




