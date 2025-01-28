/** 
 * @brief It defines the game interface
 * 
 * @file game.h
 * @author Profesores PPROG
 * @version 2.0 
 * @date 29-11-2021 
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"
#include "object.h"
#include "player.h"
#include "enemy.h"
#include "link.h"

/**
 * @brief Game
 *
 * This struct stores all the information of a game.
 */
typedef struct _Game Game;

STATUS game_add_space(Game *game, Space *space);
STATUS game_add_object(Game* game, Object* object);
STATUS game_add_player(Game* game, Player* player);
STATUS game_add_enemy(Game* game, Enemy* enemy);
STATUS game_add_link(Game* game, Link* link);
Object* game_get_object(Game* game, int pos);
Player* game_get_player(Game* game);

/**
  * @brief game_create initializes its members
  * @author Profesores PPROG
  * @param game a pointer to the game that must be initialized
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Game* game_create();

/**
  * @brief game_create_from_file sets the position of the player and the object
  * @author Profesores PPROG
  * @param game a pointer to the game that must be initialized
  * @param filename a pointer the file with the data
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS game_create_from_file(Game* game,char *filename);

/**
  * @brief game_update calls one function or another according to the command entered
  * @author Profesores PPROG
  * @param game a pointer to the game that must be initialized
  * @param cmd the last command entered
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS game_update(Game *game, T_Command cmd);

/**
  * @brief game_destroy frees the memory of all spaces
  * @author Profesores PPROG
  * @param game a pointer to the game that must be freesed
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS game_destroy(Game *game);

/**
  * @brief return false always
  * @author Profesores PPROG
  * @param game a pointer to the game 
  * @return False
  */
BOOL game_is_over(Game *game);

/**
  * @brief game_print_data prints all the relevant data, object location, player location and all the spaces
  * @author Profesores PPROG
  * @param game a pointer to the game that must be printed
  * @return nothing, void function
  */
void game_print_data(Game *game);


/**
  * @brief game_get_space gets the space according to the Id
  * @author Profesores PPROG
  * @param game a pointer to the game
  * @param Id with the id of the space
  * @return a pointer to a space
  */
Space *game_get_space(Game *game, Id id);

/**
  * @brief game_get_player_location gets the player location
  * @author Profesores PPROG
  * @param game a pointer to the game
  * @return the Id of the location of the player
  */
Id game_get_player_location(Game *game);



/**
  * @brief game_get_object_location gets the object location
  * @author Profesores PPROG
  * @param game a pointer to the game
  * @return the Id of the location of the object
  */
Id game_get_object_location(Game *game,Id id);

STATUS game_set_player_location(Game *game, Id id);
STATUS game_set_object_location(Game *game, Id space, Id object);

BOOL game_inventory_find_object(Game* game, Id id);
/**
  * @brief game_get_last_command gets the last command entered
  * @author Profesores PPROG
  * @param game a pointer to the game
  * @return the last command entered
  */
T_Command game_get_last_command(Game *game);

/**
  * @brief game_get_enemy_locaton gets the location of the enemy
  * @author Daniel Tirado
  * @param game a pointer to the game
  * @return the id of the space where is the enemy
  */
Id game_get_enemy_location(Game *game);

/**
  * @brief game_set_enemy_locaton sets the location of the enemy
  * @author Daniel Tirado
  * @param game a pointer to the game
  * @param id the id of the space
  * @return OK, if everything goes well or ERROR if there was some mistakes
  */
STATUS game_set_enemy_location(Game *game,Id id);

/**
  * @brief game_set_enemy get the pointer of the enemy
  * @author Daniel Tirado
  * @param game a pointer to the game
  * @return A pointer to the enemy
  */
Enemy* game_get_enemy(Game* game);

/**
  * @brief game_set_enemy gets the enemy health
  * @author Daniel Tirado
  * @param game a pointer to the game
  * @return n >= 0, if everything goes whell or -1 if there was some mistakes
  */
int game_get_enemy_health(Game *game);

/**
  * @brief game_set_enemy_health sets the health of the enemy
  * @author Daniel Tirado
  * @param game a pointer to the game
  * @param health the health of the enemy
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS game_set_enemy_health(Game *game, int health);

/**
  * @brief game_get_player_health gets the player health
  * @author Daniel Tirado
  * @param game a pointer to the game
  * @return n >= 0, if everything goes whell or -1 if there was some mistakes
  */
int game_get_player_health(Game *game);
/**
 * @brief game_set_MaxInv set the max num of objects a player can carry
 * 
 * @param game 
 * @param MaxInv 
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_set_player_MaxInv(Game* game,int MaxInv);

/**
 * @brief game_set_player_name set tne name of a player
 * 
 * @param game 
 * @param name 
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_set_player_name(Player* player, char* name);

/**
  * @brief game_set_enemy_health sets the health of the enemy
  * @author Daniel Tirado
  * @param game a pointer to the game
  * @param health the health of the player
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS game_set_player_health(Game *game, int health);

STATUS game_get_connection_status(Game* game, Id space, DIRECTION dir);
Id game_get_connection(Game* game, Id space, DIRECTION dir);
char* game_get_descr(Game* game);
STATUS game_clean_descr(Game* game);
#endif
