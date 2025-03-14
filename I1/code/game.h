/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"
#include "object.h"
#include "player.h"

#define MAX_SPACES 100

typedef struct _Game {
  Player *player;             /*!< Player of the game */
  Object *object;             /*!< Object of the game */
  Space *spaces[MAX_SPACES];  /*!< Spaces of the game */
  int n_spaces;               /*!< Number of spaces in the game */
  Command *last_cmd;          /*!< Last command written */
  Bool finished;              /*!< Finished status of the game */
} Game; 

/**  
   * @brief It creates a new game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @return a new Game, initialized
   */
Status game_create(Game *game);

/**  
   * @brief It creates a new game from a file
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param filename a pointer to the name of the file
   * @return a new Game, initialized
   */
Status game_create_from_file(Game *game, char *filename);

/**  
   * @brief It destroys a game and frees its memory allocation
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game that must be destroyed
   * @return OK, if everything goes well or ERROR if there was some mistake
   */
Status game_destroy(Game *game);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Space *game_get_space(Game *game, Id id);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Status game_add_space(Game *game, Space *space);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Id game_get_player_location(Game *game);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Status game_set_player_location(Game *game, Id id);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Id game_get_object_location(Game *game);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Status game_set_object_location(Game *game, Id id);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Command* game_get_last_command(Game *game);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Status game_set_last_command(Game *game, Command *command);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Bool game_get_finished(Game *game);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Status game_set_finished(Game *game, Bool finished);

/**  
   * @brief It returns the id of a space in a game
   * @author Javier and Rubén
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Id game_get_object_id(Game *game);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
void game_print(Game *game);

#endif
