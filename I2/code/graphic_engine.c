/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "graphic_engine.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"

#define WIDTH_MAP 80
#define WIDTH_DES 29
#define WIDTH_BAN 23
#define HEIGHT_MAP 30
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3

struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback;
};

void print_spaces(Graphic_engine *ge, Game *game, Space *space, int act) {
  
  Space *aux_right = NULL;
  int i;
  char str[WORD_SIZE] = "";
  char str_aux[WORD_SIZE] = "";
  char str_objects[WORD_SIZE] = "";
  char (*gdesc)[GDESC_COLS];
  char (*gdesc_right)[GDESC_COLS];
  Id *ids_objects;
  Id id;
  Id id_right;
  int cont = 0;

  if (!ge || !space) return;

  gdesc = space_get_gdesc(space);
  id = space_get_id(space);
  id_right = space_get_east(space);
  
  
  if (id_right != NO_ID) {

    aux_right = game_get_space(game, id_right);
    sprintf(str, "  +-----------+");
    while(cont < 4) {
      if (space_get_id(aux_right) != NO_ID) {
        strcat(str, "  +-----------+");
        aux_right = game_get_space(game, space_get_east(aux_right));
      } else  {
        break;
      }
      cont ++;
    }
    screen_area_puts(ge->map, str);

    cont = 0;
    /*Imprime id y character*/
    aux_right = game_get_space(game, id_right);
    if (act == 0) {
      if (id > 99) {
        sprintf(str, "  |        %2d|", (int)id);
      }else  {
        sprintf(str, "  |         %2d|", (int)id);
      }
    } else  {
      if (id > 99) {
        sprintf(str, "  | m^0    %2d|", (int)id);
      }else  {
        sprintf(str, "  | m^0     %2d|", (int)id);
      }
      act = 0;
    }
    while(cont < 4) {
      if (space_get_id(aux_right) != NO_ID) {
        if (act == 0) {
          if ((int)space_get_id(aux_right) > 99) {
            sprintf(str_aux, "  |        %2d|", (int)space_get_id(aux_right));
          }else  {
            sprintf(str_aux, "  |         %2d|", (int)space_get_id(aux_right));
          }
        } else  {
          if ((int)space_get_id(aux_right) > 99) {
            sprintf(str_aux, "  | m^0    %2d|", (int)space_get_id(aux_right));
          }else  {
            sprintf(str_aux, "  | m^0     %2d|", (int)space_get_id(aux_right));
          }
        }
        strcat(str, str_aux);
        aux_right = game_get_space(game, space_get_east(aux_right));
      } else  {
        break;
      }
      cont++;
    }
    screen_area_puts(ge->map, str);

    cont = 0;
    /*Imprime descripcion espacio*/
    for(i=0; i < GDESC_ROWS; i++) {
      aux_right = game_get_space(game, id_right);
      gdesc = space_get_gdesc(space);
      sprintf(str, "  |%s  |", gdesc[i]);
      while(cont < 4) {
        if (space_get_id(aux_right) != NO_ID) {
          gdesc_right = space_get_gdesc(aux_right);
          sprintf(str_aux, "  |%s  |", gdesc_right[i]);
          strcat(str, str_aux);
          aux_right = game_get_space(game, space_get_east(aux_right));
        } else  {
          break;
        }
        cont ++;
      }
      cont = 0;
      screen_area_puts(ge->map, str);
    }
    
    cont = 0;
    /*Imprime objects*/
    aux_right = game_get_space(game, id_right);
    if (space_get_num_objects(space) > 0) {
      ids_objects = space_get_objects(space);

      for (i = 0; i < space_get_num_objects(space); i++) {
        sprintf(str_aux, "%s ", object_get_name(game_get_object(game, ids_objects[i])));
        strcat(str_objects, str_aux);
      }
      sprintf(str, "  |%-11.11s|", str_objects);
    } else {
      sprintf(str, "  |           |");
    } 
    while(cont < 4) {
      if (space_get_id(aux_right) != NO_ID) {
        if (space_get_num_objects(aux_right) > 0) {
          ids_objects = space_get_objects(space);

          /*devuelve un array con el nombre de los objetos de espacio*/
          for (i = 0; i < space_get_num_objects(space); i++) {
            sprintf(str_aux, "%s ", object_get_name(game_get_object(game, ids_objects[i])));
            strcat(str_objects, str_aux);
          }
          sprintf(str_aux, "  |%-11.11s|", str_objects);
          strcat(str, str_aux);
        } else {
          sprintf(str_aux, "  |           |");
          strcat(str, str_aux);
        }
        aux_right = game_get_space(game, space_get_east(aux_right));
      } else  {
        break;
      }
      cont ++;
    }
    screen_area_puts(ge->map, str);

    cont = 0;
    aux_right = game_get_space(game, id_right);
    sprintf(str, "  +-----------+");
    while(cont < 4) {
      if (space_get_id(aux_right) != NO_ID) {
        strcat(str, "  +-----------+");
        aux_right = game_get_space(game, space_get_east(aux_right));
      } else  {
        break;
      }
      cont ++;
    }
    screen_area_puts(ge->map, str);

  } else {
    if (id != NO_ID) {
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      if (act == 0) {
        if (id > 99) {
          sprintf(str, "  |        %2d|", (int)id);
        }else  {
          sprintf(str, "  |         %2d|", (int)id);
        }
      } else  {
        if (id > 99) {
          sprintf(str, "  | m^0    %2d|", (int)id);
        }else  {
          sprintf(str, "  | m^0     %2d|", (int)id);
        }
      }
      screen_area_puts(ge->map, str);

      for (i = 0; i < GDESC_ROWS; i++) {
        sprintf(str, "  |%s  |", gdesc[i]);
        screen_area_puts(ge->map, str);
      }

      if (space_get_num_objects(space) > 0) {
          ids_objects = space_get_objects(space);

          for (i = 0; i < space_get_num_objects(space); i++) {
            sprintf(str_aux, "%s ", object_get_name(game_get_object(game, ids_objects[i])));
            strcat(str_objects, str_aux);
          }
          sprintf(str, "  |%-11.11s|", str_objects);
          screen_area_puts(ge->map, str);
      } else {
        sprintf(str, "  |           |");
        screen_area_puts(ge->map, str);
      }

      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }
  }
}

Graphic_engine *graphic_engine_create() {
  static Graphic_engine *ge = NULL;

  if (ge) {
    return ge;
  }

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL) {
    return NULL;
  }

  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge) {
  if (!ge) return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID;
  Space *space_act = NULL;
  Space *space_back = NULL;
  Space *space_next = NULL;
  Character **characters = NULL;
  Object **objects;
  char str[WORD_SIZE]="";
  int i, act = 0;
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];

  if (!ge || !game) {
    return;
  }

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    space_back = game_get_space(game, id_back);
    space_next = game_get_space(game, id_next);
    objects = game_get_objects(game);

    if (id_back != NO_ID) {
      print_spaces(ge, game, space_back, act);
    }

    if (id_act != NO_ID) {
      print_spaces(ge, game, space_act, ++act);
      act = 0;
    }

    if (id_next != NO_ID) {
      print_spaces(ge, game, space_next, act);
    }
  }

  /* Paint in the description area */
  screen_area_clear(ge->descript);
  for (i = 0; i < MAX_SPACES && game_get_space(game, i) != NULL; i++) {
    if (game_get_space(game, i) != NULL) {
      sprintf(str, " %d:", (int)space_get_id(game_get_space(game, i)));
      screen_area_puts(ge->descript, str);
    }
  }

  /* Print all the objects and their location */
  if (id_act != NO_ID) {
    screen_area_puts(ge->descript, "Objects: ");
    for (i = 0; i < MAX_OBJECTS && objects[i] != NULL; i++) {
      obj_loc = game_get_object_location(game, object_get_id(objects[i]));
      if (obj_loc != NO_ID) {
        sprintf(str, " %s:%d", object_get_name(objects[i]), (int)obj_loc);
        screen_area_puts(ge->descript, str);
      }
    }
  }
  /* Print the player object */
  if (id_act != NO_ID) {
    screen_area_puts(ge->descript, "Player objects: ");
    for (i = 0; i < MAX_OBJECTS && objects[i] != NULL; i++) {
      if (game_get_object_location(game, object_get_id(objects[i])) == NO_ID) {
        sprintf(str, " %s", object_get_name(objects[i]));
        screen_area_puts(ge->descript, str);
      }
    }
  }

  /* Print the characters location */
  screen_area_puts(ge->descript, "Characters: ");
  characters = game_get_characters(game);
  for (i = 0; i < MAX_CHARACTERS && characters[i] != NULL; i++) {
    sprintf(str, " %s:%d", character_get_name(characters[i]), (int)character_get_location(characters[i]));
    screen_area_puts(ge->descript, str);
  }

  /* Print the player location and health */
  sprintf(str, "Player location: %d", (int)game_get_player_location(game));
  screen_area_puts(ge->descript, str);
  sprintf(str, "Player health: %d", game_get_player_health(game));
  screen_area_puts(ge->descript, str);
  
  if (command_get_code(game_get_last_command(game)) == CHAT) {
    sprintf(str, " %s", game_get_description(game));
    screen_area_puts(ge->descript, str);
  }
  
  /* Paint in the banner area */
  screen_area_puts(ge->banner, "    The anthill game ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     next or n, back or b, exit or e, take or t, drop or d, attack or a, chat or c");
  screen_area_puts(ge->help, str);
  

  /* Paint in the feedback area */
  last_cmd = command_get_code(game_get_last_command(game));
  sprintf(str, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS],game_get_command_status(game) == OK ? "OK" : "ERROR");
  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
  game_set_description(game, "");
}