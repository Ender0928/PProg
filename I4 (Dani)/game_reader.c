#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_reader.h"


STATUS game_reader_load_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  int i;
  Id id = NO_ID;
  Space *space = NULL;
  STATUS status = OK;
  char description[MAX_DESCR] = "";

  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#s:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      strcpy(description, toks);

#ifdef DEBUG
      printf("Leido: %ld|%s\n", id, name);
#endif
      space = space_create(id);
      if (space != NULL)
      {
        space_set_name(space, name);
        space_set_description(space, description);

        for (i=0; i<NROWS; i++) {
          toks = strtok(NULL, "|");
          space_set(space, toks, i);
        }

        game_add_space(game, space);
      }
    }
  }

  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

STATUS game_reader_load_objects(Game* game,char* filename){
  FILE* file =NULL;
  Id id_obj = NO_ID;
  Id id_space = NO_ID;
  Object* object = NULL;
  char description[MAX_DESCR] = "";

  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;

  if(!game||!filename) return ERROR;

  file = fopen(filename, "r");
  if(!file) return ERROR;

  while(fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0 ) {
      toks = strtok(line + 3, "|");
      id_obj = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      id_space = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(description, toks);

  #ifdef DEBUG
    printf("Leido: %ld|%s|%ld\n",id_obj,name,id_space);
  #endif

    object = object_create(id_obj);
    if(!object){
      fclose(file);
      return ERROR;
    }

      if(object){
        object_set_name(object,name);
        game_set_object_location(game,id_space,id_obj);
        object_set_description(object,description);
        game_add_object(game, object);
        

      }
    }
  }

  fclose(file);

  return OK;

}

STATUS game_reader_load_player(Game* game,char* filename){
  FILE *file = NULL;
  Id id_player = NO_ID;
  Id id_location = NO_ID;
  int health;
  int max_inv;
  Player* player = NULL;

  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;

  if(!game||!filename) return ERROR;

  file = fopen(filename, "r");
  if(!file) return ERROR;

  while(fgets(line, WORD_SIZE, file)){
    if (strncmp("#p:", line, 3) == 0 ){
      toks = strtok(line + 3, "|");
      id_player = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      id_location = atol(toks);
      toks = strtok(NULL, "|");
      health = atol(toks);
      toks = strtok(NULL, "|");
      max_inv = atol(toks);


  #ifdef DEBUG
    printf("Leido: %ld|%s|%ld|%ld|%ld\n",id_player,name,id_location,health,max_inv);
  #endif

    player = player_create(id_player);
    if(!player){
      fclose(file);
      return ERROR;
    }

      if(player){
        player_set_name(player,name);
        player_set_location(player,id_location);
        player_set_health(player,health);
        player_set_MaxInv(player,max_inv);
        game_add_player(game, player);
      }
    }
  }

  fclose(file);
  return OK;
}

STATUS game_reader_load_enemy(Game* game,char* filename){
  FILE *file = NULL;
  Id id_enemy = NO_ID;
  Id id_location = NO_ID;
  int health;
  Enemy* enemy = NULL;

  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;

  if(!game||!filename) return ERROR;

  file = fopen(filename, "r");
  if(!file) return ERROR;

  while(fgets(line, WORD_SIZE, file)){
    if (strncmp("#e:", line, 3) == 0 ){
      toks = strtok(line + 3, "|");
      id_enemy = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      id_location = atol(toks);
      toks = strtok(NULL, "|");
      health = atol(toks);


  #ifdef DEBUG
    printf("Leido: %ld|%s|%ld|%ld\n",id_enemy,name,id_location,health);
  #endif

    enemy = enemy_create(id_enemy);
    if(!enemy){
      fclose(file);
      return ERROR;
    }

      if(enemy){
        enemy_set_name(enemy,name);
        enemy_set_location(enemy,id_location);
        enemy_set_health(enemy,health);
        game_add_enemy(game, enemy);


      }
    }
  }

  fclose(file);
  return OK;
}

STATUS game_reader_load_links(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID;
  Id origin = NO_ID;
  Id destination = NO_ID;
  DIRECTION direction = NO_DIRECTION;
  STATUS status = OK;
  
  Link *link = NULL;

  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#l:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      origin = atol(toks);
      toks = strtok(NULL, "|");
      destination = atol(toks);
      toks = strtok(NULL, "|");
      direction = atol(toks);
      toks = strtok(NULL, "|");
      status = atol(toks);
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      link = link_create(id);
      if (link != NULL)
      {
        link_set_name(link, name);
        link_set_origin(link, origin);
        link_set_destination(link, destination);
        link_set_direction(link, direction);
        link_set_status(link, status);

        /*
        link_print(link);
        */
        game_add_link(game, link);
      }
    }
  }


  fclose(file);

  return OK;
}