/**
 * @brief It defines the enemy interface
 *
 * @file space.h
 * @author Daniel Tirado
 * @version 2.0
 * @date 12-02-2022
 */


#ifndef ENEMY_H
#define ENEMY_H
#include "types.h"

#define TAM_E 256
#define P 1


typedef struct _Enemy Enemy;


/**
  * @brief It creates a new enemy
  * @author Daniel Tirado
  *
  * enemy_create allocates memory for a new enemy and initializes its members
  * @param id the identification number for the new object
  * @return a new Enemy, initialized
  */
Enemy * enemy_create (Id id);

/**
  * @brief It destroys a new enemy
  * @author Daniel Tirado
  * enemy_destroy frees the previous memory allocation 
  *  for a enemy
  * @param enemy pointer to the enemy that must be destroyed
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS enemy_destroy (Enemy *enemy);

/**
  * @brief It gets the id of a enemy
  * @author Daniel Tirado
  * @param enemy a pointer to the enemy  
  * @return the id of the enemy
  */
Id enemy_get_id(Enemy *enemy);

/**
  * @brief It gets the name of a enemy
  * @author Daniel Tirado
  * @param enemy a pointer to the enemy  
  * @return the name of the enemy
  */
const char * enemy_get_name(Enemy *enemy);

/**
  * @brief It sets the name of a enemy
  * @author Daniel Tirado
  * @param enemy a pointer to the enemy
  * @param name a pointer to the name  
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS enemy_set_name(Enemy *enemy, char *name);

/**
  * @brief It gets the position of an enemy
  * @author Daniel Tirado
  * @param enemy a pointer to the enemy  
  * @return the id of the location of the enemy
  */
Id enemy_get_location(Enemy *enemy);

/**
  * @brief It sets the location of a enemy
  * @author Daniel Tirado
  * @param enemy a pointer to the enemy
  * @param location the id of the location 
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS enemy_set_location(Enemy *enemy, Id location); /*It set the enemy location*/

/**
  * @brief It gets the health of the enemy
  * @author Daniel Tirado
  * @param enemy a pointer to the enemy  
  * @return the health of the player
  */
int enemy_get_health(Enemy *enemy);


/**
  * @brief It sets the health of a enemy
  * @author Daniel Tirado
  * @param enemy a pointer to the enemy
  * @param health the new health of the enemy
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS enemy_set_health(Enemy *enemy, int health);
#endif

