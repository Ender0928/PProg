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
  Player *player;                         /*!< Player of the game */
  Object *objects[MAX_OBJECTS];           /*!< Objects of the game */
  int n_objects;
  Character *characters[MAX_CHARACTERS];  /*!< Characters of the game */
  int n_characters;
  Space *spaces[MAX_SPACES];              /*!< Spaces of the game */
  int n_spaces;                           /*!< Number of spaces in the game */
  Command *last_cmd;                      /*!< Last command written */
  Bool finished;                          /*!< Finished status of the game */
  char *description;                      /*!< Auxiliar */
  Status command;                           /*!< Status for the last command */  
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
  Character *character = NULL;

  *game = (Game*)malloc(sizeof(Game));
  
  if (!(*game)) {
    return ERROR;
  }
  for (i = 0; i < MAX_SPACES; i++) {
    (*game)->spaces[i] = NULL;
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    (*game)->objects[i] = NULL;
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    (*game)->characters[i] = NULL;
  }

  (*game)->n_spaces = 0;
  (*game)->n_objects = 0;
  (*game)->n_characters = 0;
  (*game)->player = player_create(10);
  (*game)->last_cmd = command_create();
  character = character_create(7);
  game_add_character(*game, character);
  character_set_location(character, 11);
  character_set_friendly(character, TRUE);
  character_set_name(character, "Amigo");
  character_set_message(character, "Hola soy yo");
  (*game)->finished = FALSE;
  (*game)->description = "";
  (*game)->command = OK;

  return OK;
}

Status game_create_from_file(Game **game, char *filename) {
  if (game_create(game) == ERROR || !filename) {
    return ERROR;
  }

  /*Modificado*/
  if (game_reader_load_spaces(*game, filename) == ERROR) {
    game_destroy(game);
    return ERROR;
  }

  if (game_reader_load_objects(*game, filename) == ERROR) {
    game_destroy(game);
    return ERROR;
  }
  game_set_player_location(*game, game_get_space_id_at(*game, 0));

  return OK;
}

Status game_destroy(Game **game) {
  int i = 0;

  for (i = 0; i < (*game)->n_spaces; i++) {
    space_destroy((*game)->spaces[i]);
  }

  for (i = 0; i < (*game)->n_objects; i++) {
      object_destroy((*game)->objects[i]);
    
  }

  for (i = 0; i < (*game)->n_characters; i++) {
      character_destroy((*game)->characters[i]);
  }
  
  command_destroy((*game)->last_cmd);
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

Id game_get_object_location(Game *game, Id object_id) { 
  int i;

  if (!game || object_id == NO_ID) {
    return NO_ID;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (space_has_object(game->spaces[i], object_id)) {
      return space_get_id(game->spaces[i]);
    }
  }
  return NO_ID;
}

  
Status game_set_object_location(Game *game, Id object_id, Id space_id) {
  Space *space = game_get_space(game, space_id);
  if (!space) {
    return ERROR;
  }

  if (space_add_object(space, object_id) == ERROR) {
    return ERROR;
  }

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

  printf("=> Object locations:\n");
  for (i = 0; i < game->n_objects; i++) {
    if (game->objects[i]) {
      printf("   - Object %d is at space %d\n", (int)object_get_id(game->objects[i]), 
            (int)game_get_object_location(game, object_get_id(game->objects[i])));
    }
  }

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

Player *game_get_player(Game *game) {
  if (!game) {
    return NULL;
  }

  return game->player;
}

Status game_add_object(Game *game, Object *object) {
  int i = 0;

  if (!object) {
    return ERROR;
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    if (!game->objects[i]) {
      game->objects[i] = object;
      game->n_objects++;
      return OK;
    }
  }

  return ERROR;
}

Object *game_get_object(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    if (id == object_get_id(game->objects[i])) {
      return game->objects[i];
    }
  }

  return NULL;
}

Bool game_has_object(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID) {
    return FALSE;
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    if (id == object_get_id(game->objects[i])) {
      return TRUE;
    }
  }

  return FALSE;
}

Status game_add_character(Game *game, Character *character) {
  int i = 0;

  if (!character) {
    return ERROR;
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    if (!game->characters[i]) {
      game->characters[i] = character;
      game->n_characters++;
      return OK;
    }
  }

  return ERROR;
}

Status game_remove_character(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID) {
    return ERROR;
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    if (id == character_get_id(game->characters[i])) {
      character_destroy(game->characters[i]);
      game->characters[i] = NULL;
      game->n_characters--;
      return OK;
    }
  }

  return ERROR;
}

Bool game_has_character(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID) {
    return FALSE;
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    if (id == character_get_id(game->characters[i])) {
      return TRUE;
    }
  }

  return FALSE;
}

Object **game_get_objects(Game *game) { 
  return game->objects; 
}


Character *game_get_character_at_location(Game *game, Id location) {
  int i;

  for (i=0; i < game->n_characters; i++) {
    if (character_get_location(game->characters[i]) == location){
      return game->characters[i];
    }
  }

  return NULL;
}
int game_get_character_health(Game *game, Character *character) {
  return character_get_health(character);
}

int game_get_player_health(Game *game) {
  return player_get_health(game->player);
}

Status game_set_player_health(Game *game, int health) {
  if (!game) {
    return ERROR;
  } 

  if (health < 0) {
    return ERROR;
  }

  if (health == 0) {
    game_set_finished(game, TRUE);
    return OK;
  }

  player_set_health(game->player, health);
  return OK;
}
Status game_set_character_health(Game *game, Character *character, int health) {
  if (!game || character == NULL) {
    return ERROR;
  } 

  if (health < 0) {
    return ERROR;
  }

  if (health == 0) {
    game_remove_character(game, character_get_id(character));
    return OK;
  }

  character_set_health(character, health);
  return OK;
}

char *game_get_description(Game *game) {
  if (!game) {
    return NULL;
  }

  return game->description;
}

Status game_set_description(Game *game, char *description) {
  if (!game || !description) {
    return ERROR;
  }

  game->description = description;
  return OK;
}

Character **game_get_characters(Game *game) {
  return game->characters;
}

Status game_set_command_status(Game *game, Status status) {
  if (!game) {
    return ERROR;
  }

  game->command = status;
  return OK;
}

Status game_get_command_status(Game *game) {
  if (!game) {
    return ERROR;
  }

  return game->command;
}