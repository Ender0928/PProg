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
#include "character.h"

#define MAX_SPACES 100

typedef struct _Game Game; 

/**  
   * @brief It creates a new game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @return a new Game, initialized
   */
Status game_create(Game **game);

/**  
   * @brief It creates a new game from a file
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param filename a pointer to the name of the file
   * @return a new Game, initialized
   */
Status game_create_from_file(Game **game, char *filename);

/**  
   * @brief It destroys a game and frees its memory allocation
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game that must be destroyed
   * @return OK, if everything goes well or ERROR if there was some mistake
   */
Status game_destroy(Game **game);

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
Id game_get_object_location(Game *game, Id object_id);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Status game_set_object_location(Game *game, Id id, Id space_id);

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

Player *game_get_player(Game *game);

Status game_add_object(Game *game, Object *object);

Object *game_get_object(Game *game, Id id);

Bool game_has_object(Game *game, Id id);

Status game_add_character(Game *game, Character *character);

Status game_remove_character(Game *game, Id id);

Bool game_has_character(Game *game, Id id);

Object **game_get_objects(Game *game);

Character *game_get_character_at_location(Game *game, Id location);

int game_get_player_health(Game *game);

int game_get_character_health(Game *game, Character *character);

Status game_set_player_health(Game *game, int health);

Status game_set_character_health(Game *game, Character *character, int health);

char *game_get_description(Game *game);

Status game_set_description(Game *game, char *description);

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
