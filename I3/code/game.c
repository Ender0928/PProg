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

#define MAX_PLAYERS 5
/**
   Private functions
*/

typedef struct _PlayerNode {
  Player *player;
  
  struct _PlayerNode *next;

} PlayerNode;

struct _Game {
  Player *player;                         /*!< Player of the game */
  PlayerNode *all_players;                /*!< All players of the game */        
  int turn;                               /*!< Turn of the game */
  int n_players;                          /*!< Number of players in the game */
  Object *objects[MAX_OBJECTS];           /*!< Objects of the game */
  int n_objects;                          /*!< Number of objects in the game */
  Character *characters[MAX_CHARACTERS];  /*!< Characters of the game */
  int n_characters;                       /*!< Number of characters in the game */
  Space *spaces[MAX_SPACES];              /*!< Spaces of the game */
  int n_spaces;                           /*!< Number of spaces in the game */
  Link *links[MAX_LINKS];                 /*!< Links of the game */
  int n_links;                            /*!< Number of links in the game */
  Command *last_cmd;                      /*!< Last command written */
  Bool finished;                          /*!< Finished status of the game */
  char *description;                      /*!< Auxiliar */
  Status command;                         /*!< Status for the last command */  
}; 

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

  for (i = 0; i < MAX_OBJECTS; i++) {
    (*game)->objects[i] = NULL;
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    (*game)->characters[i] = NULL;
  }
  for (i = 0; i < MAX_LINKS; i++) {
    (*game)->links[i] = NULL;
  }

  
  (*game)->all_players = NULL;
  (*game)->player = NULL;
  (*game)->n_spaces = 0;
  (*game)->n_objects = 0;
  (*game)->n_characters = 0;
  (*game)->n_links = 0;
  (*game)->n_players = 0;
  (*game)->turn = 0;
  (*game)->last_cmd = command_create();
  (*game)->finished = FALSE;
  (*game)->description = NULL;
  (*game)->command = OK;

  return OK;
}

Status game_create_from_file(Game **game, char *filename) {
  if (game_create(game) == ERROR || !filename) {
    return ERROR;
  }

  if (game_reader_load_players(*game, filename) == ERROR) {
    game_destroy(game);
    return ERROR;
  }
  if (game_reader_load_spaces(*game, filename) == ERROR) {
    game_destroy(game);
    return ERROR;
  }

  if (game_reader_load_objects(*game, filename) == ERROR) {
    game_destroy(game);
    return ERROR;
  }

  if (game_reader_load_links(*game, filename) == ERROR) {
    game_destroy(game);
    return ERROR;
  }

  if(game_reader_load_character(*game, filename) == ERROR) {
    game_destroy(game);
    return ERROR;
  }

  return OK;
}

Status game_destroy(Game **game) {
  int i = 0;
  PlayerNode *current = NULL;
  PlayerNode *temp = NULL;

  for (i = 0; i < (*game)->n_spaces; i++) {
    space_destroy((*game)->spaces[i]);
  }

  for (i = 0; i < (*game)->n_objects; i++) {
      object_destroy((*game)->objects[i]);
    
  }

  for (i = 0; i < (*game)->n_characters; i++) {
      character_destroy((*game)->characters[i]);
  }

  for (i = 0; i < (*game)->n_links; i++) {
    link_destroy((*game)->links[i]);
  }

  current = (*game)->all_players;
    while (current) {
        temp = current;
        current = current->next;
        player_destroy(temp->player);
        free(temp);
    }
  
  command_destroy((*game)->last_cmd);
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

Id  game_get_player_location(Game *game) { 
  if (!game)
    return NO_ID;

  return player_get_location(game->player); }

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

  for (i = 0; i < MAX_CHARACTERS; i++) {
    if (!game->characters[i]) {
      game->characters[i] = character;
      game->n_characters++;
      return OK;
    }
  }

  return ERROR;
}

Status game_remove_character(Game *game, Id id) {
  int i = 0, j = 0;
  if (id == NO_ID) {
    return ERROR;
  }
  for (i = 0; i < game->n_characters; i++) {
    if (id == character_get_id(game->characters[i])) {
      character_destroy(game->characters[i]);
      game->characters[i] = NULL;
      game->n_characters--;
      for (j = i; j < game->n_characters; j++) {
        game->characters[j] = game->characters[j + 1];
        game->characters[j + 1] = NULL;
      }
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

  for (i = 0; i < game->n_characters; i++) {
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

  for (i = 0; i < game->n_characters; i++) {
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

Status game_add_object_to_player(Game *game, Id object_id) {
  if (!game || object_id == NO_ID) {
    return ERROR;
  }

  player_add_object(game->player, object_id);
  return OK;
}

Status game_remove_object_from_player(Game *game, Id object_id) {
  if (!game || object_id == NO_ID) {
    return ERROR;
  }

  player_remove_object(game->player, object_id);
  return OK;
}

Id game_get_object_id_by_name(Game *game, char *name) {
  int i;
  Object *obj = NULL;

  if (!game || !name) {
      return NO_ID;
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
      obj = game->objects[i];
      if (obj && object_get_name(obj)) {
          if (strcmp(object_get_name(obj), name) == 0) {
              return object_get_id(obj);
          }
      }
  }

  return NO_ID;
}


char* game_get_object_description(Game *game, Id id_object) {
  if (!game || id_object != NO_ID) {
    return NULL;
  }
  return object_get_description(game_get_object(game, id_object));
}

Status game_set_object_description(Game *game, char *description, Id id_object) {
  if (!game || !description) {
    return ERROR;
  }
  return object_set_description(game_get_object(game, id_object), description);
}

Inventory *game_get_player_backpack(Game *game) {
  if (!game) {
    return ERROR;
  }
  return player_get_backpack(game->player);
}

Id game_get_connection(Game *game, Id space_id, Direction dir) {
  int i;
  if (!game || space_id == NO_ID) {
      return NO_ID;
  }
  
  for (i = 0; i < game->n_links; i++) {
      if (link_get_origin(game->links[i]) == space_id && link_get_direction(game->links[i]) == dir) {
          return link_get_destination(game->links[i]);
      }
  } 
  return NO_ID;
}

Bool game_connection_is_open(Game *game, Id space_id, Direction dir) {
  int i;
  if (!game || space_id == NO_ID) {
      return FALSE;
  }

  for (i = 0; i < game->n_links; i++) {
      if (link_get_origin(game->links[i]) == space_id && link_get_direction(game->links[i]) == dir) {
          return link_is_open(game->links[i]);
      }
  }
  return FALSE;
}

Status game_add_link(Game *game, Link *link) {
    if (!game || !link || game->n_links >= MAX_LINKS) {
        return ERROR;
    }

    game->links[game->n_links] = link;
    game->n_links++;
    return OK;
}

Bool game_get_discovered(Game *game, Id space_id) {
  Space *space = NULL;
  if (!game || space_id == NO_ID) {
      return FALSE;
  }

  space = game_get_space(game, space_id);
  if (!space) {
      return FALSE;
  }

  return space_get_discovered(space);
}

Status game_set_discovered(Game *game, Id space_id, Bool discovered) {
  Space *space = NULL;
  if (!game || space_id == NO_ID) {
      return ERROR;
  }

  space = game_get_space(game, space_id);
  if (!space) {
      return ERROR;
  }

  return space_set_discovered(space, discovered);
}

Status game_add_player(Game *game, Player *player) {
  PlayerNode *new_node = NULL;
  if (!game || !player) {
      return ERROR;
  }

  new_node = (PlayerNode *)malloc(sizeof(PlayerNode));
  if (!new_node) {
      return ERROR;
  }
  new_node->player = player;
  new_node->next = NULL;

  if (!game->all_players) {
      game->all_players = new_node;
  } else {
      PlayerNode *current = game->all_players;
      while (current->next) {
          current = current->next;
      }
      current->next = new_node;
  }

  if (!game->player) {
      game->player = player;
  }
  game->n_players++;
  return OK;
}

Status set_actual_player(Game *game) {
  int i = 0;
  
  PlayerNode *current = NULL;
  if (!game || !game->all_players) {
      return ERROR;
  }

  current = game->all_players;
  while (current) {
      if (i == game->turn) {
          game->player = current->player;
          return OK;
      }
      current = current->next;
      i++;
  }

  return ERROR;
}

Status game_next_turn(Game *game) {
  if (!game || !game->all_players) {
      return ERROR;
  }

  game->turn++;
  if (game->turn >= game->n_players) {
      game->turn = 0;
  }

  return set_actual_player(game);
}

char *game_get_str_command(Game *game) {
  if (!game) {
    return NULL;
  }

  return command_get_name(game->last_cmd);
}

Status game_space_print(Game *game, Space *space) {
  if(!space || !game) {
    return ERROR;
  }
  space_print(space);
  fprintf(stdout, "Norte: %d\n", (int)game_get_connection(game, space_get_id(space), N));
  fprintf(stdout, "Sur: %d\n", (int)game_get_connection(game, space_get_id(space), S));
  fprintf(stdout, "West: %d\n", (int)game_get_connection(game, space_get_id(space), W));
  fprintf(stdout, "East: %d\n", (int)game_get_connection(game, space_get_id(space), E));

  return OK;
}