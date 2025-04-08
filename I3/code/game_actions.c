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
 * @brief Moves the player to the selected space
 * @author Profesores PPROG
 *
 * If there is a valid link to the specified space, the player is moved to it.
 *
 * @param game Pointer to the game instance
 */
Status game_actions_move(Game *game);

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

/**
 * @brief Allows the player to get the message from a Character
 * @author Profesores PPROG
 * 
 * If the player is at the same location as a Character, they'll be able to chat with it.
 * 
 * @param game Pointer to the game instance
 */
Status game_actions_chat(Game *game);

/**
 * @brief Allows the player to inspect an Object
 * @author Profesores PPROG
 * 
 * If the player is at the same location as a the object or have it in the inventory, they can inspect it.
 * 
 * @param game Pointer to the game instance
 */
Status game_actions_inspect(Game *game);

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

    case MOVE:
      return game_actions_move(game);

    case TAKE:
      return game_actions_take(game);

    case DROP:
      return game_actions_drop(game);

    case ATTACK:
      return game_actions_attack(game);
    
    case CHAT:
      return game_actions_chat(game);

    case INSPECT:
      return game_actions_inspect(game);

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

Status game_actions_take(Game *game) {
  Id player_location = NO_ID;
  Id selected_object = NO_ID;
  char *object_name = "";
  
  object_name = command_get_argument(game_get_last_command(game));
  
  if (!object_name) {
      return ERROR;
  }

  if (player_inventory_is_full(game_get_player(game))) {
    return ERROR;
  }

  player_location = game_get_player_location(game);
  if (player_location == NO_ID)
    return ERROR;

  selected_object = select_object_in_current_location_by_name(game, object_name, player_location, game_get_objects(game));
  if (selected_object == NO_ID) {
    return ERROR;
  }

  game_add_object_to_player(game, selected_object);
  space_remove_object(game_get_space(game, player_location), selected_object);
  return OK;
}

Status game_actions_drop(Game *game) {
  Id player_location = NO_ID;
  Id object_id = NO_ID;
  char *object_name;

  if(!game)
  return ERROR;
  
  if(player_inventory_is_empty(game_get_player(game)))
  return ERROR;
  
  object_name = command_get_argument(game_get_last_command(game));
  if(!object_name)
    return ERROR;
  
  player_location = game_get_player_location(game);
  if (player_location == NO_ID)
    return ERROR;
  
  object_id = game_get_object_id_by_name(game, object_name);
  if (object_id == NO_ID)
    return ERROR;

  if(player_has_object(game_get_player(game), object_id) == OK){
    game_set_object_location(game, object_id, player_location);
    game_remove_object_from_player(game, object_id);
    return OK;
  }

  return ERROR;
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

  if (player_location != character_get_location(character))
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
      if (strcmp(object_get_name(obj), name) == 0) {
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
  if (!character || character_is_friendly(character) == FALSE) { return ERROR; }

  game_set_description(game, character_get_message(character));

  return OK;
}

Status game_actions_inspect(Game *game) {
  char *object_name = "";
  Id player_location = NO_ID;
  Id selected_object = NO_ID;

  if (!game) {
    return ERROR;
  }

  object_name = command_get_argument(game_get_last_command(game));
  if (!object_name) {
    return ERROR;
  }
  player_location = game_get_player_location(game);
  if (player_location == NO_ID) {
    return ERROR;
  }
  
  selected_object = game_get_object_id_by_name(game, object_name);
  if (selected_object == NO_ID) {
    game_set_description(game, "El objeto seleccionado no existe");
    return ERROR;
  }
  if ((inventory_find_object(game_get_player_backpack(game), selected_object)==TRUE) || (player_location == game_get_object_location(game, selected_object))){
    game_set_description(game,object_get_description(game_get_object(game, selected_object)));
    return OK;
  }
  return ERROR;
}


Status game_actions_move(Game *game) {
  Id space_id = NO_ID; 
  Id new_location = NO_ID;
  Direction direction = U;
  game_set_description(game, "");
  direction = command_get_direction(game_get_last_command(game));

  if (direction != N && direction != S && direction != E && direction != W && direction == U) {
    game_set_description(game, "Selecciona una direccion valida (N, S, E, W)");
    return ERROR;
  }

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return ERROR;
  }
  
  if (game_connection_is_open(game, space_id, direction)==FALSE) {
    game_set_description(game, """La puerta para acceder a la sala en esta direccion esta cerrada""");
    return ERROR;
  }

  new_location = game_get_connection(game, space_id, direction);
  if (new_location != NO_ID) {
    game_set_player_location(game, new_location);
   
    space_set_discovered(game_get_space(game, new_location), TRUE);
    return OK;
  }  

  return ERROR;
}