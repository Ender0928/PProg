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
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
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
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);

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
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      space = space_create(id);
      if (space != NULL) {
        if (space_set_name(space, name) == ERROR ||
            space_set_north(space, north) == ERROR ||
            space_set_east(space, east) == ERROR ||
            space_set_south(space, south) == ERROR ||
            space_set_west(space, west) == ERROR ||
            space_set_gdesc(space, gdesc) == ERROR ||
            game_add_space(game, space) == ERROR) {
            
            space_destroy(space);
            st = ERROR;
        }
        /*space_print(space);*/
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
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld\n", id, name, location);
#endif
      object = object_create(id);
      if (object != NULL) {
	       object_set_name(object, name);
	       space_add_object(game_get_space(game, location), id);
         game_add_object(game, object);
      }
    }
  }

  if (ferror(file))
    Status = ERROR;

  fclose(file);
  return Status;
}
