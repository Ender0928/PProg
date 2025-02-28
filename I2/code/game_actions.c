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

    case TAKE:
      game_actions_take(game);
      break;

    case DROP:
      game_actions_drop(game);
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

  printf("Player location: %ld\n", current_id);

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

void game_actions_take(Game *game) {
  Id player_location = NO_ID;
  Id object_location = NO_ID;

  if (player_get_object(game->player) != NO_ID) {
    return;
  }

  player_location = game_get_player_location(game);
  if (player_location == NO_ID) 
      return;

  object_location = game_get_object_location(game);
  if (object_location == NO_ID)
    return;

  printf("Player location: %ld\n", player_location);
  printf("Object location: %ld\n", object_location);

  if (object_location == player_location){
    player_set_object(game->player, game_get_object_id(game));
    space_remove_object(game_get_space(game, player_location), game_get_object_id(game));
  }
  return;
  
}

void game_actions_drop(Game *game){
  Id player_location = NO_ID;

  if (player_get_object(game->player) == NO_ID) {
    return;
  }

  player_location = game_get_player_location(game);
  if (player_location == NO_ID) 
      return;

  game_set_object_location(game, player_location);
  player_set_object(game->player, NO_ID);

  return;
}
