/**
 * @brief It implements the game update through user actions
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

/**
 * @brief Handles an unknown command
 * @author Profesores PPROG
 *
 * This function is called when the user enters an unknown command.
 * It does nothing but ensures the game continues running.
 *
 * @param game Pointer to the game instance
 */
Status game_actions_unknown(Game *game);

/**
 * @brief Handles the exit command
 * @author Profesores PPROG
 *
 * This function processes the exit command, allowing the game to terminate properly.
 *
 * @param game Pointer to the game instance
 */
Status game_actions_exit(Game *game);

/**
 * @brief Moves the player to the next space (south)
 * @author Profesores PPROG
 *
 * If there is a valid space to the south, the player is moved to it.
 *
 * @param game Pointer to the game instance
 */
Status game_actions_next(Game *game);

/**
 * @brief Moves the player to the previous space (north)
 * @author Profesores PPROG
 *
 * If there is a valid space to the north, the player is moved to it.
 *
 * @param game Pointer to the game instance
 */
Status game_actions_back(Game *game);

/**
 * @brief Allows the player to the left of the current location
 * @author Profesores PPROG
 *
 * If there is a valid space to the left, the player is moved to it.
 *
 * @param game Pointer to the game instance
 */
Status game_actions_left(Game *game);

/**
 * @brief Allows the player to the right of the current location
 * @author Profesores PPROG
 *
 * If there is a valid space to the right, the player is moved to it.
 *
 * @param game Pointer to the game instance
 */
Status game_actions_right(Game *game);
/**
 * @brief Allows the player to take an object
 * @author Profesores PPROG
 *
 * If the player is at the same location as an object, they pick it up.
 *
 * @param game Pointer to the game instance
 */
Status game_actions_take(Game *game);

/**
 * @brief Allows the player to drop an object
 * @author Profesores PPROG
 *
 * If the player is carrying an object, they drop it at their current location.
 *
 * @param game Pointer to the game instance
 */
Status game_actions_drop(Game *game);

/**
 * @brief Allows the player to attack a Character
 * @author Profesores PPROG
 * 
 * If the player is at the same location as a Character, they attack it.
 * 
 * @param game Pointer to the game instance
 */
Status game_actions_attack(Game *game);

Status game_actions_chat(Game *game);

/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN:
      return game_actions_unknown(game);

    case EXIT:
      return game_actions_exit(game);

    case NEXT:
      return game_actions_next(game);

    case BACK:
      return game_actions_back(game);

    case LEFT:
      return game_actions_left(game);

    case RIGHT:
      return game_actions_right(game);
      
    case TAKE:
      return game_actions_take(game);

    case DROP:
      return game_actions_drop(game);

    case ATTACK:
      return game_actions_attack(game);
    
    case CHAT:
      return game_actions_chat(game);

    default:
      return ERROR;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

Status game_actions_unknown(Game *game) {
  return ERROR;
}

Status game_actions_exit(Game *game) {
  return OK;
}

Status game_actions_next(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return ERROR;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return OK;
}

Status game_actions_back(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    return ERROR;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }
  return OK;
}

Status game_actions_left(Game *game){
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return ERROR;
  }

  current_id = space_get_west(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return OK;
}

Status game_actions_right(Game *game){
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return ERROR;
  }

  current_id = space_get_east(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return OK;
}

Status game_actions_take(Game *game) {
  Id player_location = NO_ID;
  Id selected_object = NO_ID;
  char *object_name = "";
  
  object_name = command_get_argument(game_get_last_command(game));
  
  if (player_get_object(game_get_player(game)) != NO_ID) {
      return ERROR;
  }

  player_location = game_get_player_location(game);
  if (player_location == NO_ID)
    return ERROR;

  selected_object = select_object_in_current_location_by_name(game, object_name, player_location, game_get_objects(game));
  if (selected_object == NO_ID) {
    return ERROR;
  }

  player_set_object(game_get_player(game), selected_object);
  space_remove_object(game_get_space(game, player_location), selected_object);
  return OK;
}

Status game_actions_drop(Game *game) {
  Id player_location = NO_ID;
  Id object_id = NO_ID;

  player_location = game_get_player_location(game);
  object_id = player_get_object(game_get_player(game));

  if (object_id == NO_ID) {
      return ERROR;
  }

  if (player_location == NO_ID)
    return ERROR;

  game_set_object_location(game, object_id, player_location);
  player_set_object(game_get_player(game), NO_ID);

  return OK;
}

Status game_actions_attack(Game *game){
  Character *character = NULL;
  Id player_location = NO_ID;
  int num = 0, player_health = 0, character_health = 0;

  player_location = game_get_player_location(game);
  if (player_location == NO_ID)
    return ERROR;
  
  character = game_get_character_at_location(game, player_location);
  if (!character)
    return ERROR;

  player_health = game_get_player_health(game);
  character_health = game_get_character_health(game, character);

  num = rand() % 10;
  if(num < 5){
    player_health--;
    game_set_player_health(game, player_health);
      
  }
  else{
    character_health--;
    game_set_character_health(game, character, character_health);
  }
  return OK;
}

Id select_object_in_current_location_by_name(Game *game, char *name, Id location, Object **objects) {
  int i = 0;
  Object *obj = NULL;

  if (!game || !name) {
    return NO_ID;
  }
  for (i=0; i<MAX_OBJECTS; i++) {
    obj = objects[i];
    if (obj != NULL && game_get_object_location(game, object_get_id(obj)) == location) {
      if (strcasecmp(object_get_name(obj), name) == 0) {
        return object_get_id(obj);
      }
    }
  }
  return NO_ID;
}

Status game_actions_chat(Game *game) {
  Character *character = NULL;

  if (!game) { return ERROR; }

  character = game_get_character_at_location(game, game_get_player_location(game));
  if (!character ||character_is_friendly(character) == FALSE) { return ERROR; }

  game_set_description(game, character_get_message(character));

  return OK;
}