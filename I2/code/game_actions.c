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
void game_actions_unknown(Game *game);

/**
 * @brief Handles the exit command
 * @author Profesores PPROG
 *
 * This function processes the exit command, allowing the game to terminate properly.
 *
 * @param game Pointer to the game instance
 */
void game_actions_exit(Game *game);

/**
 * @brief Moves the player to the next space (south)
 * @author Profesores PPROG
 *
 * If there is a valid space to the south, the player is moved to it.
 *
 * @param game Pointer to the game instance
 */
void game_actions_next(Game *game);

/**
 * @brief Moves the player to the previous space (north)
 * @author Profesores PPROG
 *
 * If there is a valid space to the north, the player is moved to it.
 *
 * @param game Pointer to the game instance
 */
void game_actions_back(Game *game);

/**
 * @brief Allows the player to the left of the current location
 * @author Profesores PPROG
 *
 * If there is a valid space to the left, the player is moved to it.
 *
 * @param game Pointer to the game instance
 */
void game_actions_left(Game *game);

/**
 * @brief Allows the player to the right of the current location
 * @author Profesores PPROG
 *
 * If there is a valid space to the right, the player is moved to it.
 *
 * @param game Pointer to the game instance
 */
void game_actions_right(Game *game);
/**
 * @brief Allows the player to take an object
 * @author Profesores PPROG
 *
 * If the player is at the same location as an object, they pick it up.
 *
 * @param game Pointer to the game instance
 */
void game_actions_take(Game *game);

/**
 * @brief Allows the player to drop an object
 * @author Profesores PPROG
 *
 * If the player is carrying an object, they drop it at their current location.
 *
 * @param game Pointer to the game instance
 */
void game_actions_drop(Game *game);

/**
 * @brief Allows the player to attack a Character
 * @author Profesores PPROG
 * 
 * If the player is at the same location as a Character, they attack it.
 * 
 * @param game Pointer to the game instance
 */
void game_actions_attack(Game *game);

void game_actions_chat(Game *game);

/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN:
      game_actions_unknown(game);
      break;

    case EXIT:
      game_actions_exit(game);
      break;

    case NEXT:
      game_actions_next(game);
      break;

    case BACK:
      game_actions_back(game);
      break;

    case LEFT:
      game_actions_left(game);
      break;

    case RIGHT:
      game_actions_right(game);
      break;
      
    case TAKE:
      game_actions_take(game);
      break;

    case DROP:
      game_actions_drop(game);
      break;

    case ATTACK:
      game_actions_attack(game);
      break;
    
    case CHAT:
      game_actions_chat(game);
      break;

    default:
      break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) {}

void game_actions_exit(Game *game) {}

void game_actions_next(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_back(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }
}

void game_actions_left(Game *game){
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_west(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_right(Game *game){
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_east(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_take(Game *game) {
  Id player_location = NO_ID;
  Id selected_object = NO_ID;
  
  if (player_get_object(game_get_player(game)) != NO_ID) {
      printf("Ya llevas un objeto.\n");
      return;
  }

  player_location = game_get_player_location(game);
  if (player_location == NO_ID)
    return;

  selected_object = select_object_in_current_location(game);
  if (selected_object == NO_ID)
    return;

  player_set_object(game_get_player(game), selected_object);
  space_remove_object(game_get_space(game, player_location), selected_object);
  printf("Has recogido el objeto.\n");
  return;
}

void game_actions_drop(Game *game) {
  Id player_location = NO_ID;
  Id object_id = NO_ID;

  player_location = game_get_player_location(game);
  object_id = player_get_object(game_get_player(game));

  if (object_id == NO_ID) {
      printf("No llevas ningún objeto.\n");
      return;
  }

  if (player_location == NO_ID)
    return;

  game_set_object_location(game, object_id, player_location);
  player_set_object(game_get_player(game), NO_ID);
  printf("Has soltado el objeto.\n");

  return;
}

void game_actions_attack(Game *game){
  Character *character = NULL;
  Id player_location = NO_ID;
  int num = 0, player_health = 0, character_health = 0;

  player_location = game_get_player_location(game);
  if (player_location == NO_ID)
    return;
  
  character = game_get_character_at_location(game, player_location);
  if (!character)
    return;

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
  return;
}

Id select_object_in_current_location(Game *game) {
  Id player_location = NO_ID;
  int count = 0;
  int i = 0;
  int choice = 0;
  Object **objects = NULL;
  char description[WORD_SIZE] = "";
  char str[WORD_SIZE];
  
  player_location = game_get_player_location(game);
  objects = game_get_objects(game);

  if (player_location == NO_ID) 
    return NO_ID;

  printf("Objetos disponibles en esta ubicación:\n");
  for(i = 0; i < MAX_OBJECTS; i++) {
      Object *obj = objects[i];
      if (obj != NULL && game_get_object_location(game, object_get_id(obj)) == player_location) {
        sprintf(str, "[%d] %s (ID: %ld)\n", count + 1, object_get_name(obj), object_get_id(obj));
        count++;
        strcat(description, str);
      }
    }
  game_set_description(game, description);
  if (count == 0) {
      printf("No hay objetos en esta ubicación.\n");
      return NO_ID;
  }

  printf("Selecciona un objeto (número): ");
  if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
      printf("Selección inválida.\n");
      return NO_ID;
  }

  count = 0;
  for (i = 0; i < MAX_OBJECTS; i++) {
      Object *obj = objects[i];
      if (obj != NULL && game_get_object_location(game, object_get_id(obj)) == player_location) {
          count++;
          if (count == choice) {
              return object_get_id(obj);
          }
      }
  }

  return NO_ID;
}

void game_actions_chat(Game *game) {
  Character *character = NULL;

  if (!game) { return; }

  character = game_get_character_at_location(game, game_get_player_location(game));
  if (!character ||character_is_friendly(character) == FALSE) { return; }

  game_set_description(game, character_get_message(character));

  return;
}