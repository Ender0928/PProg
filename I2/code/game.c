/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game.h"
#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

struct _Game {
  Player *player;             /*!< Player of the game */
  Object *object;             /*!< Object of the game */
  Space *spaces[MAX_SPACES];  /*!< Spaces of the game */
  int n_spaces;               /*!< Number of spaces in the game */
  Command *last_cmd;          /*!< Last command written */
  Bool finished;              /*!< Finished status of the game */
}; 

/*Status game_add_space(Game *game, Space *space);*/

/**
  * @brief It returns the id of a space in a game
  * @author Profesores
  * @param game a pointer to the game
  * @param position an integer with the position of the space
  * @return the id of the space located at the position given
  */
Id game_get_space_id_at(Game *game, int position);

/**
   Game interface implementation
*/

Status game_create(Game **game) {
  int i;

  *game = (Game*)malloc(sizeof(Game));
  if (!(*game)) {
    return ERROR;
  }
  for (i = 0; i < MAX_SPACES; i++) {
    (*game)->spaces[i] = NULL;
  }

  (*game)->n_spaces = 0;
  (*game)->player = player_create(10);
  (*game)->object = object_create(4);
  (*game)->last_cmd = command_create();
  (*game)->finished = FALSE;

  return OK;
}

Status game_create_from_file(Game **game, char *filename) {
  if (game_create(game) == ERROR) {
    return ERROR;
  }

  /*Modificado*/
  if (game_reader_load_spaces(*game, filename) == ERROR) {
    return ERROR;
  }

  /* The player and the object are located in the first space */
  game_set_player_location(*game, game_get_space_id_at(*game, 0));
  game_set_object_location(*game, game_get_space_id_at(*game, 0));

  return OK;
}

Status game_destroy(Game **game) {
  int i = 0;

  for (i = 0; i < (*game)->n_spaces; i++) {
    space_destroy((*game)->spaces[i]);
  }

  command_destroy((*game)->last_cmd);
  object_destroy((*game)->object);
  player_destroy((*game)->player);
  free(*game);
  return OK;
}

Space *game_get_space(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}

Id game_get_player_location(Game *game) { return player_get_location(game->player); }

Status game_set_player_location(Game *game, Id id) {
  if (id == NO_ID) {
    return ERROR;
  }

  player_set_location(game->player, id);

  return OK;
}

Id game_get_object_location(Game *game) { 
  int i;

  if (!game) {
    return NO_ID;
  }

  for (i = 0; i < MAX_SPACES; i++) {
    if (space_has_object(game->spaces[i], game_get_object_id(game))) {
      return space_get_id(game->spaces[i]);
    }
  }
  
  return NO_ID;
}
  
Status game_set_object_location(Game *game, Id id) {
  Space *space = game_get_space(game, id);
  if (!space) {
    return ERROR;
  }

  space_add_object(space, game_get_object_id(game));

  return OK;
}

Command* game_get_last_command(Game *game) { return game->last_cmd; }

Status game_set_last_command(Game *game, Command *command) {
  game->last_cmd = command;

  return OK;
}

Bool game_get_finished(Game *game) { return game->finished; }

Status game_set_finished(Game *game, Bool finished) {
  game->finished = finished;

  return OK;
}

void game_print(Game *game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: %d\n", (int)game_get_object_location(game));
  printf("=> Player location: %d\n", (int)game_get_player_location(game));
}

Status game_add_space(Game *game, Space *space) {
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

Id game_get_space_id_at(Game *game, int position) {
  if (position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

Id game_get_object_id(Game *game) {
  if (!game) {
    return NO_ID;
  }

  return object_get_id(game->object);
}

Player *game_get_player(Game *game) {
  if (!game) {
    return NULL;
  }

  return game->player;
}

Object *game_get_object(Game *game) {
  if (!game) {
    return NULL;
  }

  return game->object;
}