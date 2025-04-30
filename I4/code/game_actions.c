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
#include "game_rules.h"

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

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
 * @brief Allows the player to use an Object
 * @author Profesores PPROG
 * 
 * If the player use the object, it will disappear, it can be used in other players too.
 * 
 * @param game Pointer to the game instance
 */
Status game_actions_use(Game *game);

 /**
  * @brief Allows the player to open a link with an Object
  * @author Profesores PPROG
  * 
  * 
  * 
  * @param game Pointer to the game instance
  */
Status game_actions_open(Game *game);


Status game_actions_recruit(Game *game);

Status game_actions_abandon(Game *game);

Status game_actions_load(Game *game);

Status game_actions_save(Game *game);

Status game_actions_fabricar(Game *game);

Status game_actions_battle(Game *game);

Status game_actions_quit_battle(Game *game);

Status game_actions_group(Game *game);

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

    case RECRUIT:
      return game_actions_recruit(game);

    case ABANDON:
      return game_actions_abandon(game);
    
    case SAVE:
      return game_actions_save(game);
    
    case LOAD:
      return game_actions_load(game);
    
    case FABRICAR:
      return game_actions_fabricar(game);

    case BATTLE:
      return game_actions_battle(game);
    
    case QUICK:
      return game_actions_quit_battle(game);
  
    case USE:
      return game_actions_use(game);

    case OPEN: 
      return game_actions_open(game);

    case GROUP:
      return game_actions_group(game);
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
  Id dependent_object = NO_ID;
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

  if (game_get_object_movable(game, selected_object) == FALSE) {
    game_set_description(game, "El objeto seleccionado no se puede mover");
    return ERROR;
  }

  
  dependent_object = game_get_object_dependency(game, selected_object);
  
  if (dependent_object != 0) {
    if (inventory_find_object(game_get_player_backpack(game), dependent_object) == TRUE) {
      game_add_object_to_player(game, selected_object);
      space_remove_object(game_get_space(game, player_location), selected_object);
      game_set_description(game, "");
      return OK;
    }
    else {
      game_set_description(game, "Necesitas tener en tu inventario el objeto");
      return ERROR;
    }
  }
  game_add_object_to_player(game, selected_object);
  space_remove_object(game_get_space(game, player_location), selected_object);
  return OK;
}

//preguntar que hacer con el group
Status game_actions_group(Game *game) {
  if(!game) {
    return ERROR;
  }

  if(game_get_group(game) == TRUE) {
    game_set_group(game, FALSE);
    game_set_description(game, "Has disuelto el grupo");
    return OK;
  } else {
    game_set_group(game, TRUE);
    game_set_description(game, "Has formado un grupo");
    return OK;
  }

    return ERROR;

} 


Status game_actions_drop(Game *game) {
  Id player_location = NO_ID;
  Id object_id = NO_ID;
  Id objeto_que_depende_del_elegido = NO_ID;
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

  objeto_que_depende_del_elegido = game_get_object_that_depent_from_a_given(game, object_id);
  
  if(player_has_object(game_get_player(game), object_id)){
    game_set_object_location(game, object_id, player_location);
    game_remove_object_from_player(game, object_id);
    if (objeto_que_depende_del_elegido != NO_ID && (inventory_find_object(player_get_backpack(game_get_player(game)), objeto_que_depende_del_elegido) == TRUE)) {
      game_set_object_location(game, objeto_que_depende_del_elegido, player_location);
      game_remove_object_from_player(game, objeto_que_depende_del_elegido);
    }
    return OK;
  }

  return ERROR;
}

Status game_actions_attack(Game *game) {
  Character *character = NULL;
  Character *follower = NULL;
  Id player_location = NO_ID;
  int num = 0, player_health = 0, character_health = 0;
  int followers_count = 0, random_target = 0, i;
  int extra_damage;

  if (!game || game_get_state(game) != GAME_STATE_COMBAT) {
    return ERROR;
  }

  player_location = game_get_player_location(game);
  if (player_location == NO_ID) {
    return ERROR;
  }


  character = game_get_character_at_location(game, player_location);
  if (!character || character_is_friendly(character) == TRUE || character_is_dead(character)) {
    return ERROR;
  }

  player_health = game_get_player_health(game);
  character_health = character_get_health(character);


  for (i = 0; i < game_get_n_characters(game); i++) {
    follower = game_get_character_by_index(game, i);
    if (follower && character_get_follow(follower) == player_get_id(game_get_player(game))) {
      followers_count++;
    }
  }


  num = rand() % 10;
  if (num < 5) {
    
    random_target = rand() % (followers_count + 1);
    if (random_target == 0) {
      extra_damage = gamerules_get_extra_damage_from_enemy(game, character_get_id(character));
      player_health -= (1 + extra_damage);
      if (player_health < 0)  player_health = 0;
      game_set_player_health(game, player_health);
    } else {
        for (i = 0; i < game_get_n_characters(game); i++) {
            follower = game_get_character_by_index(game, i);
            if (follower && character_get_follow(follower) == player_get_id(game_get_player(game))) {
                random_target--;
                if (random_target == 0) {
                    int follower_health = character_get_health(follower);
                    extra_damage = gamerules_get_extra_damage_from_enemy(game, character_get_id(character));
                    follower_health -= (1 + extra_damage);
                    if (follower_health < 0)  follower_health = 0;
                    game_set_character_health(game, follower, follower_health);
                    break;
                }
            }
        }
    }       

  } else {
    extra_damage = gamerules_get_extra_damage_from_objects(game);
    printf("Extra damage: %d\n", extra_damage);
    character_health -= (1 + followers_count + extra_damage); 
    if (character_health < 0)  character_health = 0;

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

Status game_actions_recruit(Game *game) {
  Character *character = NULL;
  Id player_location = NO_ID;
  Id character_id = NO_ID;
  char *character_name = NULL;

  if (!game) {
    printf("Error 1\n");
    return ERROR;
  }

 
  character_name = command_get_argument(game_get_last_command(game));
 
  if (!character_name) {
   
    return ERROR;
  }

  player_location = game_get_player_location(game);
  if (player_location == NO_ID) {
    
    return ERROR;
  }

  
  character = game_get_character_by_name_at_location(game, character_name, player_location);
  if (!character) {
 
    return ERROR;
  }

  if (character_is_friendly(character) == FALSE) {
   
    return ERROR;
  }

  character_id = character_get_id(character);
  if (character_id == NO_ID) {
   
    return ERROR;
  }

  
 game_set_character_follow(game, character_id, player_get_id(game_get_player(game)));

  return OK;
}

Status game_actions_abandon(Game *game) {
  Character *character = NULL;
  Id player_location = NO_ID;
  Id character_id = NO_ID;
  char *character_name = NULL;

  if (!game) {
    return ERROR;
  }

  
  character_name = command_get_argument(game_get_last_command(game));
  if (!character_name) {
    return ERROR;
  }

  player_location = game_get_player_location(game);
  if (player_location == NO_ID) {
    return ERROR;
  }

  
  character = game_get_character_by_name_at_location(game, character_name, player_location);
  if (!character) {
    return ERROR;
  }

  character_id = character_get_id(character);
  if (character_id == NO_ID) {
    return ERROR;
  }

  if (player_get_id(game_get_player(game)) != character_get_follow(character)) {
    return ERROR;
  }

  game_set_character_follow(game, character_id, NO_ID);

  return OK;
}

Status game_actions_move(Game *game) {
  Id space_id = NO_ID; 
  int i;
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

    
  for( i = 0; i < game_get_n_characters(game); i++){
    if(character_get_follow(game_get_character_by_index(game,i)) == player_get_id(game_get_player(game))){
      game_set_character_location(game,game_get_character_by_index(game,i), new_location);
    }
  }
   
    space_set_discovered(game_get_space(game, new_location), TRUE);

    return OK;
  }  

  return ERROR;
}

Status game_actions_load(Game *game) {
  char *filename;
  FILE *file = NULL;

  if (!game) {
    return ERROR;
  }

  filename = command_get_argument(game_get_last_command(game));
  if (!filename || strlen(filename) == 0) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (!file) {
    return ERROR;
  }
  fclose(file);

  game_clean(game);
  
  game_management_load(game, filename);
  return OK;
}

Status game_actions_save(Game *game) {
  char *filename;

  if (!game) {
    return ERROR;
  }

  filename = command_get_argument(game_get_last_command(game));
  if (!filename || strlen(filename) == 0) {
    return ERROR;
  }

  if (game_management_save(game, filename) == ERROR) {
    return ERROR;
  }

  return OK;
}

Status game_actions_fabricar(Game *game) {
  char *argument = command_get_argument(game_get_last_command(game));
  GameRules *rules = game_get_rules(game);
  CraftRule *found_rules[MAX_CRAFTS_RULES];
  int i, num_found;

  if (!argument || !rules) return ERROR;

  num_found = gamerules_get_craft_rules_by_name(game, rules, argument, found_rules);

  if (num_found == 0) {
      return ERROR;
  }

  for (i = 0; i < num_found; i++) {
      gamerules_set_requested(found_rules[i], TRUE);
  }

  return OK;
}

Status game_actions_battle(Game *game) {
  char *argument = command_get_argument(game_get_last_command(game));
  Character *enemy = NULL;
  int i;

  if (!game || !argument) return ERROR;

  for (i = 0; i < game_get_n_characters(game); i++) {
      Character *character = game_get_character_by_index(game, i);
      if (character && character_get_health(character) > 0 &&
          !character_is_friendly(character) &&
          game_get_player_location(game) == character_get_location(character) &&
          strcasecmp(character_get_name(character), argument) == 0) {

          enemy = character;
          break;
      }
  }

  if (!enemy) return ERROR;

  game_set_state(game, GAME_STATE_COMBAT);
  battle_set_enemy_id(game_get_battle(game), character_get_id(enemy));
  battle_set_initial_healths(game_get_battle(game), game_get_player_health(game), character_get_health(game_get_character(game, battle_get_enemy_id(game_get_battle(game)))));

  return OK;
}

Status game_actions_quit_battle(Game *game) {
  if (!game) return ERROR;

  if (game_get_state(game) != GAME_STATE_COMBAT)
      return ERROR;

  game_set_state(game, GAME_STATE_NORMAL);
  return OK;
}

Status game_actions_use(Game *game) {
  char object_name[WORD_SIZE] = "";
  char character_name[WORD_SIZE] = "";
  char *input = "";
  Id object_id = NO_ID;
  Id character_id = NO_ID;
  int health=0;
  if (!game) {
    return ERROR;
  }

  input = command_get_argument(game_get_last_command(game));

  if (!input) {
    return ERROR;
  }
  if (strstr(input, " over ") != NULL) {
    sscanf(input, "%s over %s", object_name, character_name);
  }
  else {
    sscanf(input, "%s", object_name);
  }

  object_id = game_get_object_id_by_name(game, object_name);
  if (object_id == NO_ID) {
    return ERROR;
  }
  health = object_get_health(game_get_object(game, object_id));
  character_id = game_get_character_id_by_name(game, character_name);
  
  if (health == 0) {
    game_set_description(game, "El objeto seleccionado no se puede utilizar");
    return ERROR;
  }
  if (strlen(character_name)>0) {
    character_set_health (game_get_character(game, character_id), (health + character_get_health(game_get_character(game, character_id))));
    game_set_description(game, "");
  }
  else {
    game_set_player_health(game, (health + game_get_player_health(game)));
    game_set_description(game, "");
  }
  game_remove_object_from_player(game, object_id);
  game_set_object_location(game, object_id, NO_ID);
  return OK;
}

Status game_actions_open(Game *game) {
  char object_name[WORD_SIZE] = "";
  char link_name[WORD_SIZE] = "";
  char *input = "";
  Id object_id = NO_ID, id_link_to_open=NO_ID;
  Link *link_to_be_opened = NULL;
  
  if (!game) {
    return ERROR;
  }

  input = command_get_argument(game_get_last_command(game));
  
  if (!input) {
    return ERROR;
  }
  printf("DEBUG input recibido: '%s'\n", input);

  if (sscanf(input, "%s with %s", link_name, object_name) != 2){
    printf("DEBUG sscanf falló. link_name='%s', object_name='%s'\n", link_name, object_name);
    game_set_description(game, "La estructura que debes utilizar para abrir el espacio es open \"nombre del enlace\" with \"objeto\"");
    return ERROR;
  }
  printf("DEBUG link_name: '%s'\n", link_name);
  printf("DEBUG object_name: '%s'\n", object_name);

  object_id = game_get_object_id_by_name(game, object_name);
  link_to_be_opened = game_get_link_by_id(game, game_get_link_id_by_name(game, link_name));
  printf("DEBUG object_id: %ld\n", object_id);
  printf("DEBUG link_id: %ld\n", game_get_link_id_by_name(game, link_name));
  if (!link_to_be_opened) {
    printf("DEBUG: No se encontró el enlace con nombre '%s'\n", link_name);
  }
  if (object_id == NO_ID) {
    printf("DEBUG: No se encontró el objeto con nombre '%s'\n", object_name);
  }


  if (!link_to_be_opened && object_id == NO_ID){
    game_set_description(game, "El enlace seleccionado y el objeto utilizado no existen.");
    return ERROR;
  } else if (!link_to_be_opened) {
    game_set_description(game, "El enlace seleccionado no existe.");
    return ERROR;
  } else if (object_id == NO_ID){
    game_set_description(game, "El objeto seleccionado no existe.");
    return ERROR;
  }

  if  (link_is_open(link_to_be_opened)==TRUE){
    game_set_description(game, "El enlace que intentas abrir ya esta abierto.");
    return ERROR;
  }

  id_link_to_open = object_get_open(game_get_object(game, object_id));
  if (id_link_to_open == 0 || id_link_to_open == NO_ID){
    game_set_description(game, "El objeto no puede abrir nada.");
    return ERROR;
  }
  
  if (id_link_to_open != link_get_id(link_to_be_opened)) {
    game_set_description(game, "El objeto abre algun enlace, pero no el seleccionado.");
    return ERROR;
  }
  
  if (id_link_to_open == link_get_id(link_to_be_opened)) {
    link_set_open(link_to_be_opened, TRUE);
    game_set_description(game, "Enlace abierto!");
    return OK;
  }
  return ERROR;
}
