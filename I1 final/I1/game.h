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

/**
 * @brief Game
 *
 * This struct stores all the information of a game.
 */
typedef struct _Game
{
  Player *player; /*Id of the player location*/
  Object *object; /*Id of the object location*/
  Space *spaces[MAX_SPACES]; /*an array with all the spaces */
  T_Command last_cmd; /*the last command entered*/
} Game;

STATUS game_add_space(Game *game, Space *space);

/**
  * @brief game_create initializes its members
  * @author Profesores PPROG
  * @param game a pointer to the game that must be initialized
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS game_create(Game *game);

/**
  * @brief game_create_from_file sets the position of the player and the object
  * @author Profesores PPROG
  * @param game a pointer to the game that must be initialized
  * @param filename a pointer the file with the data
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS game_create_from_file(Game *game, char *filename);

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
Id game_get_object_location(Game *game);

STATUS game_set_player_location(Game *game, Id id);
STATUS game_set_object_location(Game *game, Id id);

/**
  * @brief game_get_last_command gets the last command entered
  * @author Profesores PPROG
  * @param game a pointer to the game
  * @return the last command entered
  */
T_Command game_get_last_command(Game *game);
#endif
