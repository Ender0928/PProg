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
  int i, j;
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
                toks[strcspn(toks, "\r\n")] = '\0';
        
                j = 0;
                for (; j < GDESC_COLS - 1 && toks[j] != '\0'; j++) {
                    gdesc[i][j] = toks[j];
                }
                for (; j < GDESC_COLS - 1; j++) {
                    gdesc[i][j] = ' ';
                }
                gdesc[i][GDESC_COLS - 1] = '\0';
            } else {
                memset(gdesc[i], ' ', GDESC_COLS - 1);
                gdesc[i][GDESC_COLS - 1] = '\0';
            }
        }
        

#ifdef DEBUG
          printf("Leido: %ld|%s|\n", id, name);
#endif
          space = space_create(id);
          if (space != NULL) {
              if (space_get_id(space) == game_get_player_location(game)) {
                  space_set_discovered(space, TRUE);
              } else {
                  space_set_discovered(space, FALSE);
              }

              if (space_set_name(space, name) == ERROR ||
                  space_set_gdesc(space, gdesc) == ERROR ||
                  game_add_space(game, space) == ERROR) {
                  
                  space_destroy(space);
                  st = ERROR;
              }
          } else {
              st = ERROR;
          }

          for (i = 0; i < GDESC_ROWS; i++) {
              gdesc[i][0] = '\0';
          }
      }
  }

  if (ferror(file)) {
      st = ERROR;
  }

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
  Id dependency = NO_ID;
  Id open = NO_ID;
  int health;
  int movable;
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
      health = atoi(toks);
      toks = strtok(NULL, "|");
      movable = atoi(toks); 
      toks = strtok(NULL, "|");
      dependency = atol(toks);
      toks = strtok(NULL, "|");
      open = atol(toks);

      
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%s\n", id, name, location, description);
#endif
        object = object_create(id);
        if (object != NULL) {
            object_set_name(object, name);
            space_add_object(game_get_space(game, location), id);
            game_add_object(game, object);
            object_set_description(object, description);
            object_set_health(object, health);
            object_set_movable(object, movable);
            object_set_dependency(object, dependency);
            object_set_open(object, open);
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

    char gdesc_battle[GDESC_BATTLE_ROWS][GDESC_BATTLE_COLS];
    int i, j;

    if (!filename || !game) return ERROR;

    file = fopen(filename, "r");
    if (!file) return ERROR;

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

            for (i = 0; i < GDESC_BATTLE_ROWS; i++) {
                toks = strtok(NULL, "|");
                if (toks) {
                    toks[strcspn(toks, "\r\n")] = '\0';

                    j = 0;
                    for (; j < GDESC_BATTLE_COLS - 1 && toks[j] != '\0'; j++) {
                        gdesc_battle[i][j] = toks[j];
                    }
                    for (; j < GDESC_BATTLE_COLS - 1; j++) {
                        gdesc_battle[i][j] = ' ';
                    }
                    gdesc_battle[i][GDESC_BATTLE_COLS - 1] = '\0';
                } else {
                    memset(gdesc_battle[i], ' ', GDESC_BATTLE_COLS - 1);
                    gdesc_battle[i][GDESC_BATTLE_COLS - 1] = '\0';
                }
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

            character_set_gdesc_battle(character, gdesc_battle);

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

Status game_reader_load_players(Game *game, char *filename) {
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char *toks = NULL;
    Id id = NO_ID, position = NO_ID;
    char name[WORD_SIZE] = "";
    char gdesc[7] = "";
    int health = 0, max_objects = 0, count = 0;
    Player *player = NULL;

    char gdesc_battle[GDESC_BATTLE_ROWS][GDESC_BATTLE_COLS];
    char (*gdesc_battle_ptr)[GDESC_BATTLE_COLS];

    int i, j;

    if (!filename || !game) return ERROR;

    file = fopen(filename, "r");
    if (!file) return ERROR;

    while (fgets(line, WORD_SIZE, file)) {
        if (strncmp("#p:", line, 3) == 0) {
            toks = strtok(line + 3, "|");
            id = atol(toks);

            toks = strtok(NULL, "|");
            strcpy(name, toks);

            toks = strtok(NULL, "|");
            strcpy(gdesc, toks);

            toks = strtok(NULL, "|");
            position = atol(toks);

            toks = strtok(NULL, "|");
            health = atoi(toks);

            toks = strtok(NULL, "|");
            max_objects = atoi(toks);

            for (i = 0; i < GDESC_BATTLE_ROWS; i++) {
                toks = strtok(NULL, "|");
                if (toks) {
                    toks[strcspn(toks, "\r\n")] = '\0';

                    j = 0;
                    for (; j < GDESC_BATTLE_COLS - 1 && toks[j] != '\0'; j++) {
                        gdesc_battle[i][j] = toks[j];
                    }
                    for (; j < GDESC_BATTLE_COLS - 1; j++) {
                        gdesc_battle[i][j] = ' ';
                    }
                    gdesc_battle[i][GDESC_BATTLE_COLS - 1] = '\0';
                } else {
                    memset(gdesc_battle[i], ' ', GDESC_BATTLE_COLS - 1);
                    gdesc_battle[i][GDESC_BATTLE_COLS - 1] = '\0';
                }
            }

#ifdef DEBUG
            printf("Leído Jugador: %ld|%s|%s|%ld|%d|%d\n", id, name, gdesc, position, health, max_objects);
#endif

            player = player_create(id);
            if (!player) {
                fclose(file);
                return ERROR;
            }

            player_set_name(player, name);
            player_set_graphic_desc(player, gdesc);
            player_set_location(player, position);
            player_set_health(player, health);
            player_set_max_objects(player, max_objects);
            if (count == 0) {
                player_set_turn(player, TRUE);
                count++;
            }

            player_set_gdesc_battle(player, gdesc_battle);

            game_add_player(game, player);

            gdesc_battle_ptr = player_get_gdesc_battle(player);
            if (gdesc_battle_ptr) {
                printf("Descripción de combate del jugador %s:\n", player_get_name(player));
                for (i = 0; i < GDESC_BATTLE_ROWS; i++) {
                    printf("%s\n", gdesc_battle_ptr[i]);
                }
            }
        }
    }

    if (ferror(file)) {
        fclose(file);
        return ERROR;
    }

    fclose(file);
    return OK;
}

  

