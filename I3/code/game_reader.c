/**
 * @brief It defines the game reader
 * 
 * @file game_reader.c
 * @author Javier and Rubén
 * @version 1.0
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_reader.h"

Status game_reader_load_spaces(Game *game, char *filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID;
  Space* space = NULL;
  Status st = OK;
  int i;
  char (*gdesc)[GDESC_COLS];

  if (!filename || !game) {
    return ERROR;
  }
  
  gdesc = malloc(GDESC_ROWS * sizeof(char[GDESC_COLS]));
  if (!gdesc) {
      return ERROR;
  }



  file = fopen(filename, "r");
  if (file == NULL) {
    free(gdesc);
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);

      for (i = 0; i < GDESC_ROWS; i++) {
        toks = strtok(NULL, "|");
        if (toks) {
            strncpy(gdesc[i], toks, GDESC_COLS - 1);
            gdesc[i][GDESC_COLS - 1] = '\0';
        } else {
            strcpy(gdesc[i], "         ");
            gdesc[i][GDESC_COLS - 1] = '\0';
        }
      }
#ifdef DEBUG
      printf("Leido: %ld|%s|\n", id, name);
#endif
      space = space_create(id);
      if (space != NULL) {
        if (space_set_name(space, name) == ERROR ||
            space_set_gdesc(space, gdesc) == ERROR ||
            game_add_space(game, space) == ERROR) {
            
            space_destroy(space);
            st = ERROR;
        }
      } else {
          st = ERROR;
      }
      for (i=0; i < GDESC_ROWS; i++) {
        gdesc[i][0] = '\0';
      }
    }
  }

  if (ferror(file))
    st = ERROR;

  free(gdesc);
  fclose(file);
  return st;
}

Status game_reader_load_objects(Game *game, char *filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char description[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID;
  Id location = NO_ID;
  Object* object = NULL;
  Status Status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(description, toks);
      toks = strtok(NULL, "|");
      
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%s\n", id, name, location, description);
#endif
      object = object_create(id);
      if (object != NULL) {
	       object_set_name(object, name);
	       space_add_object(game_get_space(game, location), id);
         game_add_object(game, object);
         object_set_description(object, description);
      }
    }
  }

  if (ferror(file))
    Status = ERROR;

  fclose(file);
  return Status;
}

Status game_reader_load_links(Game *game, char *filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID, origin = NO_ID, destination = NO_ID;
  int direction, open;
  Link* link = NULL;

  if (!filename || !game) {
      return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
      return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
      if (strncmp("#l:", line, 3) == 0) {
          toks = strtok(line + 3, "|");
          id = atol(toks);
          toks = strtok(NULL, "|");
          strcpy(name, toks);
          toks = strtok(NULL, "|");
          origin = atol(toks);
          toks = strtok(NULL, "|");
          destination = atol(toks);
          toks = strtok(NULL, "|");
          direction = atoi(toks);
          toks = strtok(NULL, "|");
          open = atoi(toks);

          #ifdef DEBUG
          printf("Leido Link: %ld|%s|%ld|%ld|%d|%d\n", id, name, origin, destination, direction, open);
          #endif

          link = link_create(id);
          if (link) {
              link_set_name(link, name);
              link_set_origin(link, origin);
              link_set_destination(link, destination);
              link_set_direction(link, direction);
              link_set_open(link, open);
              game_add_link(game, link);
          } else {
              fclose(file);
              return ERROR;
          }
          link_print(link);
      }
  }

  if (ferror(file)) {
      fclose(file);
      return ERROR;
  }

  fclose(file);
  return OK;
}

Status game_reader_load_character(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, location = NO_ID;
  char name[WORD_SIZE] = "";
  char gdesc[7] = "";
  int health = 0;
  int friendly = 0;
  char message[WORD_SIZE] = "";
  Character *character = NULL;

  if (!filename || !game) {
      return ERROR;
  }

  file = fopen(filename, "r");
  if (!file) {
      return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
      if (strncmp("#c:", line, 3) == 0) {
          toks = strtok(line + 3, "|");
          id = atol(toks);

          toks = strtok(NULL, "|");
          strcpy(name, toks);

          toks = strtok(NULL, "|");
          strcpy(gdesc, toks);

          toks = strtok(NULL, "|");
          location = atol(toks);

          toks = strtok(NULL, "|");
          health = atoi(toks);

          toks = strtok(NULL, "|");
          friendly = atoi(toks);

          toks = strtok(NULL, "|");
          if (toks) {
              strcpy(message, toks);
              message[strcspn(message, "\n")] = '\0';
          }

#ifdef DEBUG
          printf("Leído Personaje: %ld|%s|%s|%ld|%d|%d|%s\n", id, name, gdesc, location, health, friendly, message);
#endif

          character = character_create(id);
          if (!character) {
              fclose(file);
              return ERROR;
          }

          character_set_name(character, name);
          character_set_gdesc(character, gdesc);
          character_set_location(character, location);
          character_set_health(character, health);
          character_set_friendly(character, friendly ? TRUE : FALSE);
          character_set_message(character, message);

          game_add_character(game, character);
      }
  }

  if (ferror(file)) {
      fclose(file);
      return ERROR;
  }

  fclose(file);
  return OK;
}

/*
Status game_reader_load_players(Game *game, char *filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID, position = NO_ID;
  int health = 0, max_objects = 0;
  char gdesc[GDESC_COLS] = "";
  Player* player = NULL;
  Status st = OK;

  if (!filename || !game) {
      return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
      return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
      if (strncmp("#p:", line, 3) == 0) {
          toks = strtok(line + 3, "|");
          id = atol(toks);

          toks = strtok(NULL, "|");
          strcpy(name, toks);

          toks = strtok(NULL, "|");
          strncpy(gdesc, toks, GDESC_COLS - 1);
          gdesc[GDESC_COLS - 1] = '\0';

          toks = strtok(NULL, "|");
          position = atol(toks);

          toks = strtok(NULL, "|");
          health = atoi(toks);

          toks = strtok(NULL, "|");
          max_objects = atoi(toks);

#ifdef DEBUG
          printf("Leído Jugador: %ld|%s|%s|%ld|%d|%d\n", id, name, gdesc, position, health, max_objects);
#endif

          player = player_create(id);
          if (player != NULL) {
              if (player_set_name(player, name) == ERROR ||
                  player_set_graphic_desc(player, gdesc) == ERROR ||
                  player_set_location(player, position) == ERROR ||
                  player_set_health(player, health) == ERROR ||
                  player_set_max_objects(player, max_objects) == ERROR ||
                  game_add_player(game, player) == ERROR) {
                  
                  player_destroy(player);
                  st = ERROR;
              }
          } else {
              st = ERROR;
          }
      }
  }

  if (ferror(file)) {
      st = ERROR;
  }

  fclose(file);
  return st;
}
*/
