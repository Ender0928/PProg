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

void game_actions_unknown(Game *game);

void game_actions_exit(Game *game);

void game_actions_next(Game *game);

void game_actions_back(Game *game);

void game_actions_take(Game *game);

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
    game_set_object_location(game, NO_ID);
    player_set_object(game->player, game_get_object_id(game));
    space_set_object(game_get_space(game, player_location), NO_ID);
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

  if (player_get_object(game->player) == NO_ID)
    return;

  printf("Player location: %ld\n", player_location);

  game_set_object_location(game, player_location);
  player_set_object(game->player, player_location);
  printf("Object droped\n");
  printf("Player object: %ld\n", player_get_object(game->player));

  return;
}
