/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Profesores PPROG
 * @version 0
 * @date 31-01-2025
 * @copyright GNU Public License
 */

#include "graphic_engine.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"

#define WIDTH_MAP 135
#define WIDTH_DES 29
#define WIDTH_BAN 23
#define HEIGHT_MAP 52 
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3

struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback;
};

void print_limits_no_west_east(Graphic_engine *ge) {
  char str[WORD_SIZE] = "";
  char str_aux[WORD_SIZE] = "";

  sprintf(str, "                                    ");
  sprintf(str_aux, "  +--------------------------------+");
  strcat(str, str_aux);
  sprintf(str_aux, "                                      ");
  strcat(str, str_aux);
  
  screen_area_puts(ge->map, str);
}

void print_id_north_no_west_east(Graphic_engine *ge, Id id) {
  char str[WORD_SIZE] = "";
  char str_aux[WORD_SIZE] = "";

  sprintf(str, "                                    ");
  if (id > 99) {
      sprintf(str_aux, "  |                             %2d|", (int)id);
  } else {
      sprintf(str_aux, "  |                              %2d|", (int)id);
  }
  strcat(str, str_aux);
  sprintf(str_aux, "                                      ");
  strcat(str, str_aux);

  screen_area_puts(ge->map, str);
}

void print_id_no_west_east(Game *game, Graphic_engine *ge, Id id) {
  char str[WORD_SIZE] = "";
  char str_aux[WORD_SIZE] = "";
  Character *chars[MAX_CHARACTERS];
  char buffer[WORD_SIZE] = "";
  int i, num_chars;

  num_chars = game_get_characters_at_location(game, id, chars);
  buffer[0] = '\0';
  for (i = 0; i < num_chars; i++) {
      const char *gdesc = character_get_gdesc(chars[i]);
      if (gdesc) {
        if (character_is_dead(chars[i]) == FALSE)
            strcat(buffer, gdesc);
        strcat(buffer, " ");
      }
  }

  sprintf(str, "                                    ");
  if (id > 99) {
      sprintf(str_aux, "  | m0^     %-15.15s     %2d|", buffer, (int)id);
  } else {
      sprintf(str_aux, "  | m0^     %-15.15s      %2d|", buffer, (int)id);
  }
  strcat(str, str_aux);
  sprintf(str_aux, "                                      ");
  strcat(str, str_aux);

  screen_area_puts(ge->map, str);
}

/**
 * @brief Prints a centered ASCII label to indicate UP/DOWN connections
 *
 * @param ge Pointer to the graphic engine
 * @param game Pointer to the game
 * @param space_id ID of the current space to evaluate
 */
void print_vertical_connections(Graphic_engine *ge, Game *game, Id space_id) {
  Id id_up =NO_ID, id_down = NO_ID;
  char str[WORD_SIZE] = "";

  if (!ge || !game || space_id == NO_ID) return;

  id_up = game_get_connection(game, space_id, UP);
  id_down = game_get_connection(game, space_id, D);

  if (id_up != NO_ID && id_down != NO_ID) {
      sprintf(str, "                                                  [UP/DOWN]                                            ");
  } else if (id_up != NO_ID) {
      sprintf(str, "                                                    [UP]                                               ");
  } else if (id_down != NO_ID) {
      sprintf(str, "                                                   [DOWN]                                              ");
  }

  if (str[0] != '\0') {
      screen_area_puts(ge->map, str);
  }
}


void print_spaces(Graphic_engine *ge, Game *game, Space *space, int act) {
  Id id, id_north = NO_ID, id_west = NO_ID, id_east = NO_ID, id_surth = NO_ID;
  Character *chars[MAX_CHARACTERS];
  char str[WORD_SIZE] = "";
  char str_aux[WORD_SIZE] = "";
  char str_objects[WORD_SIZE] = "";
  char str_objects1[WORD_SIZE] = "";
  char str_objects2[WORD_SIZE] = "";
  char str_objects3[WORD_SIZE] = "";
  Id *ids_objects;
  char (*gdesc)[GDESC_COLS];
  char (*gdesc_north)[GDESC_COLS];
  char (*gdesc_west)[GDESC_COLS];
  char (*gdesc_east)[GDESC_COLS];
  char (*gdesc_surth)[GDESC_COLS];
  char buffer[WORD_SIZE] = "";
  int i, num_chars;


  Space *space_north = NULL;
  Space *space_west = NULL;
  Space *space_east = NULL;
  Space *space_surth = NULL;

  id = space_get_id(space);
  gdesc = space_get_gdesc(space);

  id_north = game_get_connection(game, id, N);
  space_north = game_get_space(game, id_north);
  gdesc_north = space_get_gdesc(space_north);


  id_west = game_get_connection(game, id, W);
  space_west = game_get_space(game, id_west);
  gdesc_west = space_get_gdesc(space_west);


  id_east = game_get_connection(game, id, E);
  space_east = game_get_space(game, id_east);
  gdesc_east = space_get_gdesc(space_east);

  id_surth = game_get_connection(game, id, S);
  space_surth = game_get_space(game, id_surth);
  gdesc_surth = space_get_gdesc(space_surth);

  num_chars = game_get_characters_at_location(game, id, chars);
  buffer[0] = '\0';
  for (i = 0; i < num_chars; i++) {
      const char *gdesc = character_get_gdesc(chars[i]);
      if (gdesc) {
        if (character_is_dead(chars[i]) == FALSE)
          strcat(buffer, gdesc);
        strcat(buffer, " ");
      }
  }

  if (id != NO_ID) {
    if (id_north != NO_ID) {
      /*Techo del espacio norte*/
      print_limits_no_west_east(ge);
    
      /*Id y personaje espacio*/
      print_id_north_no_west_east(ge, id_north);
      
      /*Descripcion Norte*/
      if (space_get_discovered(space_north))
        for (i = 0; i < GDESC_ROWS; i++) {
          sprintf(str, "                                    ");
          sprintf(str_aux, "  |%s      |", gdesc_north[i]);
          strcat(str, str_aux);
          sprintf(str_aux, "                                      ");
          strcat(str, str_aux);
          screen_area_puts(ge->map, str);
      }  else {
        for (i=0; i < GDESC_ROWS; i++) {
          sprintf(str, "                                    ");
          sprintf(str_aux, "  |                                |");
          strcat(str, str_aux);
          sprintf(str_aux, "                                      ");
          strcat(str, str_aux);
          screen_area_puts(ge->map, str);
        }
      }

      sprintf(str, "                                    ");
      if (space_get_num_objects(space_north) > 0) {
        ids_objects = space_get_objects(space_north);

        for (i = 0; i < space_get_num_objects(space_north); i++) {
          sprintf(str_aux, "%s ", object_get_name(game_get_object(game, ids_objects[i])));
          strcat(str_objects, str_aux);
        }
        sprintf(str_aux, "  |%-32.32s|", str_objects);
        strcat(str, str_aux);
        sprintf(str_aux, "                                      ");
        strcat(str, str_aux);
        screen_area_puts(ge->map, str);
      } else {
        sprintf(str, "                                    ");
        sprintf(str_aux, "  |                                |");
        strcat(str, str_aux);
        sprintf(str_aux, "                                      ");
        strcat(str, str_aux);
        screen_area_puts(ge->map, str);
      }

      /*Suelo del espacio norte*/
      print_limits_no_west_east(ge);

      /*Separacion entre espacio norte y el actual*/
      sprintf(str, "                                                       ^                                                       ");
      screen_area_puts(ge->map, str);
    } else {
      for (i=0; i < 11; i++) {
        sprintf(str, "                                                           ");
        screen_area_puts(ge->map, str);
      }
    }

    if (id_west != NO_ID && id_east != NO_ID) {
      /*limite superior*/
      sprintf(str, "  +--------------------------------+");
      sprintf(str_aux, "  +--------------------------------+");
      strcat(str, str_aux);
      sprintf(str_aux, "  +--------------------------------+");
      strcat(str, str_aux);
      screen_area_puts(ge->map, str);

      /*Id y personaje espacio*/
      if (id_west > 99) {
        sprintf(str, "  |                             %2d|", (int)id_west);
      } else {
        sprintf(str, "  |                              %2d|", (int)id_west);
      }
      if (id > 99) {
          sprintf(str_aux, "  | m0^     %-15.15s     %2d|", buffer, (int)id);
      } else {
          sprintf(str_aux, "  | m0^     %-15.15s      %2d|", buffer, (int)id);
      }
      strcat(str, str_aux);
      if (id_east > 99) {
        sprintf(str_aux, "  |                             %2d|", (int)id_east);
      } else {
        sprintf(str_aux, "  |                              %2d|", (int)id_east);
      }

      strcat(str, str_aux);
      screen_area_puts(ge->map, str);

      /*Descripcion*/
      for (i = 0; i < GDESC_ROWS; i++) {
        if (space_get_discovered(space_west)) {
          sprintf(str, "  |%s      |", gdesc_west[i]);
        } else {
          sprintf(str, "  |                                |");
        }
        sprintf(str_aux, "  |%s      |", gdesc[i]);
        strcat(str, str_aux);

        if (space_get_discovered(space_east)) {
          sprintf(str_aux, "  |%s      |", gdesc_east[i]);
        } else {
          sprintf(str_aux, "  |                                |");
        }
        strcat(str, str_aux);
        screen_area_puts(ge->map, str);
      }
      

      /*objects*/
      if (space_get_num_objects(space_west) > 0) {
        ids_objects = space_get_objects(space_west);

        for (i = 0; i < space_get_num_objects(space_west); i++) {
          sprintf(str_aux, "%s ", object_get_name(game_get_object(game, ids_objects[i])));
          strcat(str_objects1, str_aux);
        }
        sprintf(str, "  |%-32.32s|", str_objects1);
      } else {
        sprintf(str, "  |                                |");
      } 
      if (space_get_num_objects(space) > 0) {
        ids_objects = space_get_objects(space);

        for (i = 0; i < space_get_num_objects(space); i++) {
          sprintf(str_aux, "%s ", object_get_name(game_get_object(game, ids_objects[i])));
          strcat(str_objects2, str_aux);
        }
        sprintf(str_aux, " <|%-32.32s|", str_objects2);
        strcat(str, str_aux);
      } else {
        sprintf(str_aux, " <|                                |");
        strcat(str, str_aux);
      } 
      if (space_get_num_objects(space_east) > 0) {
        ids_objects = space_get_objects(space_east);

        for (i = 0; i < space_get_num_objects(space_east); i++) {
          sprintf(str_aux, "%s ", object_get_name(game_get_object(game, ids_objects[i])));
          strcat(str_objects3, str_aux);
        }
        sprintf(str_aux, "> |%-32.32s|", str_objects3);
        strcat(str, str_aux);
        screen_area_puts(ge->map, str);
      } else {
        sprintf(str_aux, "> |                                |");
        strcat(str, str_aux);
        screen_area_puts(ge->map, str);
      }

      sprintf(str, "  +--------------------------------+");
      sprintf(str_aux, "  +--------------------------------+");
      strcat(str, str_aux);
      sprintf(str_aux, "  +--------------------------------+");
      strcat(str, str_aux);
      
      screen_area_puts(ge->map, str);

      print_vertical_connections(ge, game, id);

    } else if (id_west != NO_ID && id_east == NO_ID) {
      /*limite superior*/
      sprintf(str, "  +--------------------------------+");
      sprintf(str_aux, "  +--------------------------------+");
      strcat(str, str_aux);
      sprintf(str_aux, "                     ");
      strcat(str, str_aux);
      screen_area_puts(ge->map, str);

      /*Id y personaje espacio*/
      if (id > 99) {
          sprintf(str, "  |                             %2d|", (int)id_west);
      } else {
          sprintf(str, "  |                              %2d|", (int)id_west);
      }
      if (id > 99) {
          sprintf(str_aux, "  | m0^     %-15.15s     %2d|", buffer, (int)id);
      } else {
          sprintf(str_aux, "  | m0^     %-15.15s      %2d|", buffer, (int)id);
      }
      strcat(str, str_aux);
      sprintf(str_aux, "                     ");
      strcat(str, str_aux);
      screen_area_puts(ge->map, str);


      /*Descripcion*/
      if (space_get_discovered(space_west)) {
        for (i = 0; i < GDESC_ROWS; i++) {
          sprintf(str, "  |%s      |", gdesc_west[i]);
          sprintf(str_aux, "  |%s      |", gdesc[i]);
          strcat(str, str_aux);
          sprintf(str_aux, "                                      ");
          strcat(str, str_aux);
          screen_area_puts(ge->map, str);
        } 
      } else {
        for (i=0; i < GDESC_ROWS; i++) {
          sprintf(str, "|                                  |");
          sprintf(str_aux, "  |%s      |", gdesc[i]);
          strcat(str, str_aux);
          sprintf(str_aux, "                                      ");
          strcat(str, str_aux);
          screen_area_puts(ge->map, str);
        }
      }

      /*objects*/
      if (space_get_num_objects(space_west) > 0) {
        ids_objects = space_get_objects(space_west);
        
        for (i = 0; i < space_get_num_objects(space_west); i++) {
          sprintf(str_aux, "%s ", object_get_name(game_get_object(game, ids_objects[i])));
          strcat(str_objects1, str_aux);
        }
        sprintf(str, "  |%-32.32s|", str_objects1);
      } else {
        sprintf(str, "  |                                |");
      } 
      if (space_get_num_objects(space) > 0) {
        ids_objects = space_get_objects(space);
        
        for (i = 0; i < space_get_num_objects(space); i++) {
          sprintf(str_aux, "%s ", object_get_name(game_get_object(game, ids_objects[i])));
          strcat(str_objects2, str_aux);
        }
        sprintf(str_aux, " <|%-32.32s|", str_objects2);
        strcat(str, str_aux);
      } else {
        sprintf(str_aux, " <|                                |");
        strcat(str, str_aux);
      }
      sprintf(str_aux, "                                      ");
      strcat(str, str_aux);
      screen_area_puts(ge->map, str);

      sprintf(str, "  +--------------------------------+");
      sprintf(str_aux, "  +--------------------------------+");
      strcat(str, str_aux);
      sprintf(str_aux, "                                      ");
      strcat(str, str_aux);
      
      screen_area_puts(ge->map, str);

      print_vertical_connections(ge, game, id);

    } else if (id_west == NO_ID && id_east != NO_ID) {
      /*limite superior*/
      sprintf(str, "                                    ");
      sprintf(str_aux, "  +--------------------------------+");
      strcat(str, str_aux);
      sprintf(str_aux, "  +--------------------------------+");
      strcat(str, str_aux);
      screen_area_puts(ge->map, str);

      /*Id y personaje espacio*/
      sprintf(str, "                                    ");
      if (id > 99) {
          sprintf(str_aux, "  | m0^     %-15.15s     %2d|", buffer, (int)id);
      } else {
          sprintf(str_aux, "  | m0^     %-15.15s      %2d|", buffer, (int)id);
      }
      strcat(str, str_aux);
      if (id > 99) {
        sprintf(str_aux, "  |                             %2d|", (int)id_east);
      } else {
          sprintf(str_aux, "  |                              %2d|", (int)id_east);
      }
      strcat(str, str_aux);
      screen_area_puts(ge->map, str);
      
      /*Descripcion*/
      if (space_get_discovered(space_east)) {
        for (i = 0; i < GDESC_ROWS; i++) {
          sprintf(str, "                                    ");
          sprintf(str_aux, "  |%s      |", gdesc[i]);
          strcat(str, str_aux);
          sprintf(str_aux, "  |%s      |", gdesc_east[i]);
          strcat(str, str_aux);
          screen_area_puts(ge->map, str);
        }
      } else {
        for (i=0; i < GDESC_ROWS; i++) {
          sprintf(str, "                                    ");
          sprintf(str_aux, "  |%s      |", gdesc[i]);
          strcat(str, str_aux);
          sprintf(str_aux, "  |                                |");
          strcat(str, str_aux);
          screen_area_puts(ge->map, str);
        }
      }

      /*objects*/
      str_objects[0] = 0;
      str[0] = 0;
      sprintf(str, "                                    ");
      if (space_get_num_objects(space) > 0) {
        ids_objects = space_get_objects(space);

        for (i = 0; i < space_get_num_objects(space); i++) {
          sprintf(str_aux, "%s ", object_get_name(game_get_object(game, ids_objects[i])));
          strcat(str_objects, str_aux);
        }
        sprintf(str_aux, "  |%-32.32s|", str_objects);
        strcat(str, str_aux);
      } else {
        sprintf(str_aux, "  |                                |");
        strcat(str, str_aux);
      } 
      str_objects[0] = 0;
      if (space_get_num_objects(space_east) > 0) {
        ids_objects = space_get_objects(space_east);

        for (i = 0; i < space_get_num_objects(space_east); i++) {
          sprintf(str_aux, "%s ", object_get_name(game_get_object(game, ids_objects[i])));
          strcat(str_objects, str_aux);
        }
        sprintf(str_aux, " <|%-32.32s|", str_objects);
        strcat(str, str_aux);
        screen_area_puts(ge->map, str);
      } else {
        sprintf(str_aux, " <|                                |");
        strcat(str, str_aux);
        screen_area_puts(ge->map, str);
      }

      sprintf(str, "                                    ");
      sprintf(str_aux, "  +--------------------------------+");
      strcat(str, str_aux);
      sprintf(str_aux, "  +--------------------------------+");
      strcat(str, str_aux);
      
      screen_area_puts(ge->map, str);

      print_vertical_connections(ge, game, id);

    } else {
      /*limite superior*/
      print_limits_no_west_east(ge);

      /*Id y personaje espacio*/
      print_id_no_west_east(game, ge, id);
      
      /*Descripcion*/
      for (i = 0; i < GDESC_ROWS; i++) {
        sprintf(str, "                                    ");
        sprintf(str_aux, "  |%s      |", gdesc[i]);
        strcat(str, str_aux);
        sprintf(str_aux, "                                      ");
        strcat(str, str_aux);
        screen_area_puts(ge->map, str);
      }

      /*objects*/
      sprintf(str, "                                    ");
      if (space_get_num_objects(space) > 0) {
        ids_objects = space_get_objects(space);

        str_objects[0] = 0;
        for (i = 0; i < space_get_num_objects(space); i++) {
          sprintf(str_aux, "%s ", object_get_name(game_get_object(game, ids_objects[i])));
          strcat(str_objects, str_aux);
        }
        sprintf(str_aux, "  |%-32.32s|", str_objects);
        strcat(str, str_aux);
        sprintf(str_aux, "                                      ");
        strcat(str, str_aux);
        screen_area_puts(ge->map, str);
      } else {
        sprintf(str, "                                    ");
        sprintf(str_aux, "  |                                |");
        strcat(str, str_aux);
        sprintf(str_aux, "                                      ");
        strcat(str, str_aux);
        screen_area_puts(ge->map, str);
      }

      /*Suelo del espacio norte*/
      print_limits_no_west_east(ge);

      print_vertical_connections(ge, game, id);
      
    }

    if (id_surth != NO_ID) {
      sprintf(str, "                                                       ^                                                       ");
      screen_area_puts(ge->map, str);

      print_limits_no_west_east(ge);
      print_id_north_no_west_east(ge, id_surth);

      if (space_get_discovered(space_surth)) {
        for (i = 0; i < GDESC_ROWS; i++) {
          sprintf(str, "                                    ");
          sprintf(str_aux, "  |%s      |", gdesc_surth[i]);
          strcat(str, str_aux);
          sprintf(str_aux, "                                      ");
          strcat(str, str_aux);
          screen_area_puts(ge->map, str);
        } 
      } else {
        for (i=0; i < GDESC_ROWS; i++) {
          sprintf(str, "                                    ");
          sprintf(str_aux, "  |                                |");
          strcat(str, str_aux);
          sprintf(str_aux, "                                      ");
          strcat(str, str_aux);
          screen_area_puts(ge->map, str);
        }
      }

      sprintf(str, "                                    ");
      if (space_get_num_objects(space_surth) > 0) {
        ids_objects = space_get_objects(space_surth);

        str_objects[0] = 0;
        for (i = 0; i < space_get_num_objects(space_surth); i++) {
          sprintf(str_aux, "%s ", object_get_name(game_get_object(game, ids_objects[i])));
          strcat(str_objects, str_aux);
        }
        sprintf(str_aux, "  |%-32.32s|", str_objects);
        strcat(str, str_aux);                 
        sprintf(str_aux, "                     ");
        strcat(str, str_aux);
        screen_area_puts(ge->map, str);
      } else {
        sprintf(str, "                                    ");
        sprintf(str_aux, "  |                                |");
        strcat(str, str_aux);
        sprintf(str_aux, "                                      ");
        strcat(str, str_aux);
        screen_area_puts(ge->map, str);
      }

      print_limits_no_west_east(ge);
     
    } else {
      for (i=0; i < 11; i++) {
        sprintf(str, "                                                          ");
        screen_area_puts(ge->map, str);
      }
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

void print_combat_screen(Graphic_engine *ge, Game *game) {
  Battle *battle = NULL;
  Character *enemy = NULL;
  Player *player = NULL;
  char (*pdesc)[GDESC_BATTLE_COLS];
  char (*cdesc)[GDESC_BATTLE_COLS];
  int player_health, player_health_init, enemy_health, enemy_health_init;
  char str[WORD_SIZE];
  int i;

  if (!ge || !game) return;

  battle = game_get_battle(game);
  if (!battle) return;

  enemy = game_get_character(game, battle_get_enemy_id(battle));
  player = game_get_player(game);

  if (!player || !enemy) return;
  
  pdesc = player_get_gdesc_battle(player);
  
  cdesc = character_get_gdesc_battle(enemy);

  player_health = game_get_player_health(game);
  player_health_init = battle_get_initial_player_health(battle);
  enemy_health = character_get_health(enemy);
  enemy_health_init = battle_get_initial_enemy_health(battle); 
  screen_area_clear(ge->map);
  screen_area_clear(ge->descript);
  screen_area_clear(ge->help);
  screen_area_clear(ge->feedback);

  /* Título */
  screen_area_puts(ge->map, "                                                  ____ ___  __  __ ____    _  _____ _____ ");
  screen_area_puts(ge->map, "                                                 / ___/ _ \\|  \\/  | __ )  / \\|_   _| ____|");
  screen_area_puts(ge->map, "                                                | |  | | | | |\\/| |  _ \\ / _ \\ | | |  _|  ");
  screen_area_puts(ge->map, "                                                | |__| |_| | |  | | |_) / ___ \\| | | |___ ");
  screen_area_puts(ge->map, "                                                 \\____\\___/|_|  |_|____/_/   \\_\\_| |_____|");



  for (i = 0; i < GDESC_BATTLE_ROWS; i++) {
      screen_area_puts(ge->map, pdesc[i]);
  }

  sprintf(str, "Vida: ");
  for (i = 0; i < player_health_init; i++) {
    strcat(str, i < player_health ? "[$]" : "[ ]");
  }
  screen_area_puts(ge->map, str);
  screen_area_puts(ge->map, "------------- VS --------------");

  for (i = 0; i < GDESC_BATTLE_ROWS; i++) {
      screen_area_puts(ge->map, cdesc[i]);
  }

  sprintf(str, "Vida enemigo: ");
  for (i = 0; i < enemy_health_init; i++) {
      strcat(str, i < enemy_health ? "[X]" : "[ ]");
  }
  screen_area_puts(ge->map, str);
  /* Ayuda */
  screen_area_puts(ge->help, "Comandos disponibles: attack or a, Quit battle or q");

  /* Feedback */
  sprintf(str, "En combate contra %s", character_get_name(enemy));
  screen_area_puts(ge->feedback, str);

  screen_paint();
  printf("prompt:> ");
}

void print_revival_screen(Graphic_engine *ge, Game *game) {
  const char **ascii;
  char str[90];
  int i,j;

  static const char *ascii_numbers[7][7] = {
      {
          "  ___  ",
          " / _ \\ ",
          "| | | |",
          "| | | |",
          "| |_| |",
          " \\___/ "
      },
      {
          " __ ",
          "/_ |",
          " | |",
          " | |",
          " | |",
          " |_|"
      },
      {
          " ___  ",
          "|__ \\ ",
          "   ) |",
          "  / / ",
          " / /__",
          "|_____|"
      },
      {
          " ____  ",
          "|___ \\ ",
          "  __) |",
          " |__ < ",
          " ___) |",
          "|_____|"
      },
      {
          " _  _   ",
          "| || |  ",
          "| || |_ ",
          "|__   _|",
          "   | |  ",
          "   |_|  "
      },
      {
          " _____ ",
          "| ____|",
          "| |__  ",
          "|___ \\ ",
          " ___| |",
          "|_____|"
      }
  };

  for (j = 5; j >= 0; j--) {
    screen_area_clear(ge->map);
    screen_area_clear(ge->help);
    screen_area_clear(ge->feedback);
    
    screen_area_puts(ge->map, "                                         ____  _____    _    ____   _    ____  _____ ____ ___ _____ _   _ ____   ___  ");
    screen_area_puts(ge->map, "                                        |  _ \\| ____|  / \\  |  _ \\ / \\  |  _ \\| ____/ ___|_ _| ____| \\ | |  _ \\ / _ \\ ");
    screen_area_puts(ge->map, "                                        | |_) |  _|   / _ \\ | |_) / _ \\ | |_) |  _|| |    | ||  _| |  \\| | | | | | | |");
    screen_area_puts(ge->map, "                                        |  _ <| |___ / ___ \\|  __/ ___ \\|  _ <| |__| |___ | || |___| |\\  | |_| | |_| |");
    screen_area_puts(ge->map, "                                        |_| \\_\\_____/_/   \\_\\_| /_/   \\_\\_| \\_\\_____\\____|___|_____|_| \\_|____/ \\___/ ");
    
    for (i=0; i < 15; i++)
      screen_area_puts(ge->map, " ");

    ascii = ascii_numbers[j];

    for (i = 0; i < 6; i++) {
      sprintf(str, "                                                                  %s", (char*)ascii[i]);
      screen_area_puts(ge->map, str);
    }

    screen_paint();
    sleep(1);
  }

  game_set_player_health(game, 1);
  if (game_get_state(game) == GAME_STATE_REVIVAL) {
    game_set_state(game, GAME_STATE_COMBAT);
  }else if (game_get_state(game) == GAME_STATE_RESPAUWN) {
    game_set_state(game, GAME_STATE_NORMAL);
  }
}


void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Id id_act = NO_ID, obj_loc = NO_ID;
  Space *space_act = NULL;
  Character **characters = NULL;
  Object **objects;
  char str[WORD_SIZE]="";
  int i, act = 0;
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];

  if (!ge || !game) {
    return;
  }

  objects = game_get_objects(game);
  id_act = game_get_player_location(game);
  space_act = game_get_space(game, id_act);

  if (game_get_state(game) == GAME_STATE_COMBAT) {
    /*Paint de area combat*/
    print_combat_screen(ge, game);
  } else if (game_get_state(game) == GAME_STATE_NORMAL) {

    /* Paint the map in the area */
    screen_area_clear(ge->map);
    if (id_act  != NO_ID) {
        print_spaces(ge, game, space_act, ++act);
        act = 0;
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
          sprintf(str, " %s:%d", object_get_name(objects[i]), (int)obj_loc);
          screen_area_puts(ge->descript, str);
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
        sprintf(str, " %s:%d (%d)", character_get_name(characters[i]),
                                    (int)character_get_location(characters[i]), 
                                    character_get_health(characters[i])
                                    );
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

    if (command_get_code(game_get_last_command(game)) == INSPECT) {
      sprintf(str, " %s", game_get_description(game));
      screen_area_puts(ge->descript, str);
    }
    if (command_get_code(game_get_last_command(game)) == MOVE) {
      sprintf(str, " %s", game_get_description(game));
      screen_area_puts(ge->descript, str);
    }
    
    /* Paint in the banner area */
    screen_area_puts(ge->banner, "    The anthill game ");

    /* Paint in the help area */
    screen_area_clear(ge->help);
    sprintf(str, " The commands you can use are:");
    screen_area_puts(ge->help, str);
    sprintf(str, "     move or m (north or n, south or s, east or e, west or w, down d up u), exit or e, take or t, drop or d, attack or a, chat or c, i or inspect,k or recruit,n or abandon");
    screen_area_puts(ge->help, str);
    

    /* Paint in the feedback area */
    last_cmd = command_get_code(game_get_last_command(game));
    sprintf(str, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS],game_get_command_status(game) == OK ? "OK" : "ERROR");
    screen_area_puts(ge->feedback, str);

    /* Dump to the terminal */
    screen_paint();
    printf("prompt:> ");
    game_set_description(game, "");
  } else if (game_get_state(game) == GAME_STATE_REVIVAL || game_get_state(game) == GAME_STATE_RESPAUWN) {
    print_revival_screen(ge, game);
  }
}