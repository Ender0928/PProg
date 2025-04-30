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
#include "game_management.h"
#include "game_rules.h" 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

typedef struct _PlayerNode {
  Player *player;
  
  struct _PlayerNode *next;

} PlayerNode;

struct _Game {
  GameRules *rules;                       /*!< Rules of the game*/
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
  GameState state;                        /*!< State of the game */ 
  Battle *battle;                         /*!< Battle of the game */
  Id revival_space;                       /*!< Space where the player revives */
  Bool group;                             /*!< Group of the game */
}; 

void game_rules_init(Game *game);

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
  (*game)->finished = FALSE;
  (*game)->description = NULL;
  (*game)->command = OK;
  (*game)->group = FALSE;
  (*game)->last_cmd = command_create();
  (*game)->rules = gamerules_create();
  if (!(*game)->rules) {
      game_destroy(game);
      return ERROR;
  }
  game_rules_init(*game);
  (*game)->state = GAME_STATE_NORMAL  ;
  (*game)->battle = battle_create();
  if (!(*game)->battle) {
      game_destroy(game);
      return ERROR;
  }
  (*game)->revival_space = DEFAULT_REVIVAL_SPACE_ID;
  return OK;
}

Status game_create_from_file(Game **game, char *filename) {
  if (game_create(game) == ERROR || !filename) {
    return ERROR;
  }
  if (game_management_load(*game, filename) == ERROR) {
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

  gamerules_destroy((*game)->rules);
  
  battle_destroy((*game)->battle);

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

int game_get_n_characters(Game *game) {
  if (!game) {
    return -1;
  }

  return game->n_characters;
}


Character *game_get_character_by_name_at_location(Game *game, char *name, Id location) {
  int i = 0;

  if (!game || !name || location == NO_ID) {

    return NULL;
  }

  for (i = 0; i < game->n_characters; i++) {
    if (character_get_id(game->characters[i]) != NO_ID &&  
            strcmp(character_get_name(game->characters[i]), name) == 0) {
        
      return game->characters[i];
    }
  }


  return NULL;
}

Status game_set_character_follow(Game *game, Id character_id, Id player_id) {
  int i = 0;

  if (!game || character_id == NO_ID || player_id == NO_ID) {
    return ERROR;
  }

  for (i = 0; i < game->n_characters; i++) {
    if (character_get_id(game->characters[i]) == character_id) {
      character_set_follow(game->characters[i], player_id);
      return OK;
    }
  }

  return ERROR;
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

Bool  game_get_object_movable(Game *game, Id object_id) { 
  int i=0;
  if (!game || object_id == NO_ID){
    return NO_ID;
  }
    for (i = 0; i < game->n_objects ; i++) {
      if (object_get_id(game->objects[i]) == object_id) {
        return object_get_movable(game->objects[i]);
      }
    }
  return FALSE; 
}

Id game_get_object_dependency(Game *game, Id object_id) { 
  int i=0;
  if (!game || object_id == NO_ID){
    return NO_ID;
  }
    for (i = 0; i < game->n_objects ; i++) {
      if (object_get_id(game->objects[i]) == object_id) {
        return object_get_dependency(game->objects[i]);
      }
    }
  return FALSE; 
}

Id game_get_object_that_depent_from_a_given(Game *game, Id object_id) {
  int i;
  if (!game || object_id==NO_ID) {
    return NO_ID;
  }
  for (i=0; i<game->n_objects; i++) {
    if (object_get_dependency(game->objects[i]) == object_id){
      return object_get_id(game->objects[i]);
    }
  }
  return NO_ID;
}

Link *game_get_link_by_id(Game *game, Id link_id) {
  int i;
  if (!game || link_id == NO_ID) {
    return NULL;
  }
  for (i = 0; i<game->n_links; i++) {
    if (link_get_id(game->links[i]) == link_id) {
      return game->links[i];
    }
  }
  return NULL;
}

Id game_get_link_id_by_name(Game *game, char *link_name) {
  int i;
  if (!game || !link_name) {
    return NO_ID;
  }
  for (i = 0; i <game->n_links; i++) {
    if ((strcmp(link_name, link_get_name(game->links[i]))) == 0){
      return link_get_id(game->links[i]);
    }
  }
  return NO_ID;
}

Id game_get_character_id_by_name(Game *game, char *character_name) {
  int i;
  if (!game || !character_name) {
    return NO_ID;
  }
  for (i = 0; i <game->n_characters; i++) {
    if ((strcmp(character_name, character_get_name(game->characters[i]))) == 0){
      return character_get_id(game->characters[i]);
    }
  }
  return NO_ID;
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

Player *game_get_player(Game *game) {
  if (!game) {
    return NULL;
  }

  return game->player;
}


Status game_set_character_location(Game *game, Character *c, Id location_id) {
 if(!game || !c || location_id == NO_ID) {
    return ERROR;
  }

  if (character_set_location(c, location_id) == ERROR) {
    return ERROR;
  }

  return OK;
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
    if (gamerules_check_revival_object(game, game_get_rules(game))) {
      game_set_state(game, GAME_STATE_REVIVAL);
      return OK;
    } 

    game_set_state(game, GAME_STATE_RESPAUWN);
    game_drop_all_objects(game);
    game_set_player_location(game, game_get_revival_space(game));
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
    character_mark_dead(character);
    character_set_health(character, 0);
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

Character *game_get_character_by_index(Game *g, int i){
  if (!g || i < 0 || i >= g->n_characters) {
    return NULL;
  }

  return g->characters[i];
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
  if (command_get_code(game->last_cmd) == BATTLE || command_get_code(game->last_cmd) == ATTACK) {
      return OK;
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

int game_get_n_spaces(Game *game) {
  if (!game) {
    return -1;
  }

  return game->n_spaces;
}

Space *game_get_space_by_index(Game *game, Id index) {
  if (!game || index < 0) {
    return NULL;
  }

  return game->spaces[index];
}

int game_get_n_links(Game *game) {
  if (!game) {
    return -1;
  }

  return game->n_links;
}

Link *game_get_link_by_index(Game *game, Id index) {
  if (!game || index < 0) {
    return NULL;
  }

  return game->links[index];
}

int game_get_n_players(Game *game) {
  if (!game) {
    return -1;
  }

  return game->n_players;
}

Player *game_get_player_by_index(Game *game, Id id) {
  int i = 0;
  PlayerNode *current = NULL;

  if (!game || id == NO_ID) {
    return NULL;
  }

  current = game->all_players;
  while (current && i < game->n_players) {
    if (i == id) {
      return current->player;
    }
    current = current->next;
    i++;
  }
  return NULL;
}

int game_get_n_objects(Game *game) {
  if (!game) {
    return -1;
  }

  return game->n_objects;
}

Object *game_get_object_by_index(Game *game, Id index) {
  if (!game || index < 0) {
    return NULL;
  }

  return game->objects[index];
}

void game_clean(Game *game) {
  PlayerNode *current = NULL;
  PlayerNode *temp = NULL;
  int i = 0;

  for (i = 0; i < game->n_spaces; i++) {
    if(game->spaces[i]) {
      space_destroy(game->spaces[i]);
      game->spaces[i] = NULL;
    }
  }

  for (i = 0; i < game->n_objects; i++) {
    if(game->objects[i]) {
      object_destroy(game->objects[i]);
      game->objects[i] = NULL;
    }
  }
  for (i = 0; i < game->n_characters; i++) {
    if(game->characters[i]) {
      character_destroy(game->characters[i]);
      game->characters[i] = NULL;
    }
  }
  for (i = 0; i < game->n_links; i++) {
    if(game->links[i]) {
      link_destroy(game->links[i]);
      game->links[i] = NULL;
    }
  }

  current = game->all_players;
  temp = NULL;
  while (current) {
    temp = current;
    current = current->next;
    player_destroy(temp->player);
    free(temp);
  }
  game->all_players = NULL;
  game->player = NULL;
  game->n_spaces = 0;
  game->n_objects = 0;
  game->n_characters = 0;
  game->n_links = 0;
  game->n_players = 0;
  game->turn = 0;
}

Status game_set_group(Game *game, Bool group) {
  if (!game) {
    return ERROR;
  }

  game->group = group;
  return OK;
}

Bool game_get_group(Game *game) {
  if (!game) {
    return FALSE;
  }

  return game->group;
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
  fprintf(stdout, "Down: %d\n", (int)game_get_connection(game, space_get_id(space), D));
  fprintf(stdout, "Up: %d\n", (int)game_get_connection(game, space_get_id(space), UP));

  return OK;
}

int game_get_characters_at_location(Game *game, Id location, Character **result) {
  int count = 0;
  int i = 0;
  if (!game || location == NO_ID || !result) {
      return 0;
  }

  for (i = 0; i < game->n_characters && count < MAX_CHARACTERS; i++) {
      Character *c = game->characters[i];
      if (c && character_get_location(c) == location) {
          result[count++] = c;
      }
  }

  return count;
}

Character *game_get_character(Game *game, Id id) {
  int i;

  if (!game || id == NO_ID) return NULL;

  for (i = 0; i < game->n_characters; i++) {
      if (character_get_id(game->characters[i]) == id) {
          return game->characters[i];
      }
  }

  return NULL;
}

GameRules *game_get_rules(Game *game) {
  if (!game) return NULL;
  return game->rules;
}

void game_rules_init(Game *game) {
  GameRules *rules = game_get_rules(game);
  if (!rules) return;

  /*Rules of drop objects on dead*/
  gamerules_add_drop_rule(rules, 3, 12);
  gamerules_add_drop_rule(rules, 5, 14);
  gamerules_add_drop_rule(rules, 6, 15);

  /*Rules of open links */
  gamerules_add_open_link_on_death_rule(rules, 3, 12);

  /*Rules of heath objects*/
  gamerules_add_heal_on_pickup(rules, 15, 3);
  gamerules_add_heal_on_pickup(rules, 16, 2);

  /*Rules of crafts*/
  gamerules_add_craft_rule(rules, 12, 14, 17);

  /*Rules of extra damege objects*/
  gamerules_add_object_damage_rule(rules, 17, 1);

  /*Rules of extra damage characters*/
  gamerules_add_enemy_damage_rule(game_get_rules(game), 3, 1);

  /*Objetos inmortales*/
  gamerules_add_revival_object(rules, 18);
}

Link *game_get_link(Game *game, Id link_id) {
  int i;
  if (!game || link_id == NO_ID) return NULL;

  for (i = 0; i < MAX_LINKS; i++) {
      if (game->links[i] && link_get_id(game->links[i]) == link_id) {
          return game->links[i];
      }
  }

  return NULL;
}

void game_set_state(Game *game, GameState state) {
  if (game) game->state = state;
}

GameState game_get_state(Game *game) {
  return game ? game->state : GAME_STATE_NORMAL;
}

Battle *game_get_battle(Game *game) {
  if (!game) return NULL;

  return game->battle;
}

void game_set_revival_space(Game *game, Id space_id) {
  if (game) game->revival_space = space_id;
}

Id game_get_revival_space(Game *game) {
  return game ? game->revival_space : NO_ID;
}

Status game_drop_all_objects(Game *game) {
  Player *player = NULL;
  Space *space = NULL;
  Id location = NO_ID;
  Id *objects = NULL;
  int total = 0;
  Id obj_id;

  if (!game) return ERROR;

  player = game_get_player(game);
  if (!player) return ERROR;

  location = player_get_location(player);
  if (location == NO_ID) return ERROR;

  space = game_get_space(game, location);
  if (!space) return ERROR;

  total = player_get_num_objects(player);
  while (total > 0) {
      objects = player_get_objects(player);
      obj_id = objects[0]; // siempre coger el primero

      if (player_remove_object(player, obj_id) == OK) {
          space_add_object(space, obj_id);
      }

      total--; // ya hemos eliminado uno, siguiente vuelta
  }

  return OK;
}



