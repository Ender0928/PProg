/**
 * @brief It defines a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Profesores PPROG
 * @version 2.0
 * @date 29-11-2021
 * @copyright GNU Public License
 */

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "graphic_engine.h"
#include "libscreen.h"
#include "command.h"
#include "space.h"
#include "types.h"
#include "link.h"


#define ROWS 43
#define COLUMNS 150

#define ENEMY_TAM 32

struct _Graphic_engine
{
  Area *map, *descript, *banner, *help, *feedback;
};

/** It allocates memory for a pointer
  * to Graphic_engine and initializes its members.
  */
Graphic_engine *graphic_engine_create() 
{
  static Graphic_engine *ge = NULL;

  if (ge)
    return ge;

  screen_init(ROWS, COLUMNS);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL)
    return NULL;

  ge->map = screen_area_init(1, 1, 85, 30);
  ge->descript = screen_area_init(87, 1, 62, 30);
  ge->banner = screen_area_init(63, 32, 23, 1);
  ge->help = screen_area_init(1, 33, 148, 4);
  ge->feedback = screen_area_init(1, 38, 148, 4);

  return ge;
}

/** It destroys the graphic engine and frees the previous
  * allocation for a graphic engine.
  */
void graphic_engine_destroy(Graphic_engine *ge) 
{
  if (!ge)
    return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

/** It paints the game in the terminal
  */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game) 
{
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_east = NO_ID, id_west = NO_ID;
  char obj1[WORD_SIZE],obj2[WORD_SIZE],obj3[WORD_SIZE],obj4[WORD_SIZE];
  char str[3500];
  char enemy[ENEMY_TAM];
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i,j, k;




  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID)
  {
    id_back = game_get_connection(game, id_act, N);
    id_next = game_get_connection(game, id_act, S);
    id_east = game_get_connection(game, id_act, E);
    id_west = game_get_connection(game, id_act, W);


    if (id_back != NO_ID) {
      sprintf(str, " ");
      screen_area_puts(ge->map, str);
      if ((int) id_back > 99)
        sprintf(str, "  |            %2d|", (int)id_back);

      else
        sprintf(str, "  |             %2d|", (int)id_back);

      screen_area_puts(ge->map, str);

      for (j=0; j<NROWS; j++) {
        sprintf(str, "  |%s      |", space_get(game_get_space(game, id_back), j));
        screen_area_puts(ge->map, str);
      }
        
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "          ^");
      screen_area_puts(ge->map, str);
    }

    strcpy(obj1," ");  
    strcpy(obj2," ");  
    strcpy(obj3," "); 
    strcpy(obj4," ");  

    for(i=0;i<MAX_OBJ;i++){
      if(game_get_object_location(game,object_get_id(game_get_object(game,i)))==id_act){ 
        if(i==0){
          strcpy(obj1, "/"); 
        }
        if(i==1){
          strcpy(obj2, "O");  
        }
        if(i==2){
          strcpy(obj3, "D");  
        }
        if(i==3){
          strcpy(obj4, ">");  
        }
      }
    }

    if (game_get_enemy_location(game) == id_act)
      strcpy(enemy, "//\\\\o//\\\\");
      
    else
      strcpy(enemy, "         ");

  if (id_act != NO_ID && id_east != NO_ID && id_west != NO_ID) {

      for (i=0; i<10; i++) {
        sprintf(str, " ");
        screen_area_puts(ge->map, str);
      }

      sprintf(str, "  +---------------+     +---------------+     +---------------+");
      screen_area_puts(ge->map, str);

      if ((int) id_east == 14) {
        sprintf(str, "  |            %2d|     | m0^        %2d|     |             %2d|", (int)id_west, (int)id_act, (int)id_east);
        screen_area_puts(ge->map, str);
      }

      else {
        sprintf(str, "  |            %2d|     | m0^        %2d|     |            %2d|", (int)id_west, (int)id_act, (int)id_east);
        screen_area_puts(ge->map, str);
      }

      
      sprintf(str, "  |               |     |   %s  %s  %s  %s  |     |               |", obj1,obj2,obj3,obj4);
      screen_area_puts(ge->map, str);


      for (j=0; j<NROWS; j++) {
        if (j==2) {
          sprintf(str, "  |%s      |  >  |%s      |  >  |%s      |", space_get(game_get_space(game, id_west), j), space_get(game_get_space(game, id_act), j), space_get(game_get_space(game, id_east), j));
          screen_area_puts(ge->map, str);
        }
        else {
          sprintf(str, "  |%s      |     |%s      |     |%s      |", space_get(game_get_space(game, id_west), j), space_get(game_get_space(game, id_act), j), space_get(game_get_space(game, id_east), j));
          screen_area_puts(ge->map, str);
        }
      }

      sprintf(str, "  |               |     |   %s   |     |               |", enemy);

      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+     +---------------+     +---------------+");
      screen_area_puts(ge->map, str);

    }

    else if (id_act != NO_ID && id_east != NO_ID) {
      
      sprintf(str, "  +---------------+     +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | m0^        %2d|     |            %2d|", (int)id_act, (int)id_east);
      screen_area_puts(ge->map, str);

      sprintf(str, "  | %s  %s  %s  %s    |     |               |", obj1,obj2,obj3,obj4);
      screen_area_puts(ge->map, str);

      for (j=0; j<NROWS; j++) {
        if (j==2) {
          sprintf(str, "  |%s      |  >  |%s      |", space_get(game_get_space(game, id_act), j), space_get(game_get_space(game, id_east), j));
          screen_area_puts(ge->map, str);
        }
        else {
          sprintf(str, "  |%s      |     |%s      |", space_get(game_get_space(game, id_act), j), space_get(game_get_space(game, id_east), j));
          screen_area_puts(ge->map, str);
        }
      }

      sprintf(str, "  |   %s   |     |               |", enemy);
 
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+     +---------------+");
      screen_area_puts(ge->map, str);
    }

    else if (id_act != NO_ID && id_west != NO_ID) {

      for (i=0; i<10; i++) {
        sprintf(str, " ");
        screen_area_puts(ge->map, str);
      }
      
      sprintf(str, "  +---------------+     +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |            %2d|     | m0^         %2d|   ", (int)id_west, (int)id_act);
      screen_area_puts(ge->map, str);

      sprintf(str, "  |               |     | %s  %s  %s  %s    |", obj1,obj2,obj3,obj4);
      screen_area_puts(ge->map, str);

      for (j=0; j<NROWS; j++) {
        if (j==2) {
          sprintf(str, "  |%s      |  <  |%s      |", space_get(game_get_space(game, id_west), j), space_get(game_get_space(game, id_act), j));
          screen_area_puts(ge->map, str);
        }
        else {
          sprintf(str, "  |%s      |     |%s      |", space_get(game_get_space(game, id_west), j), space_get(game_get_space(game, id_act), j));
          screen_area_puts(ge->map, str);
        }
      }

      

      sprintf(str, "  |               |     |   %s   |", enemy);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+     +---------------+");
      screen_area_puts(ge->map, str);
    }


    else if (id_act != NO_ID) {
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);

      if ((int)id_act > 99) {
        sprintf(str, "  | m0^        %2d|", (int)id_act);
        screen_area_puts(ge->map, str);
        sprintf(str, "  | %s  %s  %s  %s    |", obj1,obj2,obj3,obj4);
      }

      else {
        sprintf(str, "  | m0^         %2d|", (int)id_act);
        screen_area_puts(ge->map, str);
        sprintf(str, "  | %s  %s  %s  %s    |", obj1,obj2,obj3,obj4);
      }

      screen_area_puts(ge->map, str);

      
      for (j=0; j<NROWS; j++) {
        sprintf(str, "  |%s      |", space_get(game_get_space(game, id_act), j));
        screen_area_puts(ge->map, str);
      }

      
      
      sprintf(str, "  | %s     |", enemy);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
      
      
      

    }

    


    if (id_next != NO_ID)
    {
      if ((int)id_act == 14) {
        

        sprintf(str, "                               ???");
        screen_area_puts(ge->map, str);
        sprintf(str, "                        +---------------+");
        screen_area_puts(ge->map, str);

        if (id_next > 99)
          sprintf(str, "                        |            %2d|", (int)id_next);
        else
          sprintf(str, "                        |             %2d|", (int)id_next);

        screen_area_puts(ge->map, str);
        sprintf(str, "                        |               |");
        screen_area_puts(ge->map, str);
        for (j=0; j<NROWS; j++) {
          sprintf(str, "                        |%s      |", space_get(game_get_space(game, id_next), j));
          screen_area_puts(ge->map, str);
        }
      }

      else { 
        sprintf(str, "          v");
        screen_area_puts(ge->map, str);
        sprintf(str, "  +---------------+");
        screen_area_puts(ge->map, str);

        if (id_next > 99)
          sprintf(str, "  |            %2d|", (int)id_next);
        else
          sprintf(str, "  |             %2d|", (int)id_next);

        screen_area_puts(ge->map, str);
        sprintf(str, "  |               |");
        screen_area_puts(ge->map, str);
        for (j=0; j<NROWS; j++) {
          sprintf(str, "  |%s      |", space_get(game_get_space(game, id_next), j));
          screen_area_puts(ge->map, str);
        }
      }
    }
  }

  /* Paint in the description area */
  screen_area_clear(ge->descript);
  sprintf(str, "  Object locations");
  screen_area_puts(ge->descript, str);

  for(k=0;k<MAX_OBJ;k++){
    if(game_get_object_location(game,object_get_id(game_get_object(game,k)))!=NO_ID){ /*if the player has te object*/
    sprintf(str, "  O%ld:%ld",object_get_id(game_get_object(game,k)),game_get_object_location(game,object_get_id(game_get_object(game,k))));
    screen_area_puts(ge->descript, str);
    }
  }

  sprintf(str,"    ");
  screen_area_puts(ge->descript,str);

  sprintf(str,"  Player inventory");
  screen_area_puts(ge->descript,str);

  if (game_inventory_find_object(game, object_get_id(game_get_object(game, 0))) == TRUE) 
    sprintf(str, "   O1: Equipped");
  

  else 
    sprintf(str, "   O1: --");
  screen_area_puts(ge->descript,str);

  
  if (game_inventory_find_object(game, object_get_id(game_get_object(game, 1))) == TRUE) 
    sprintf(str, "   O2: Equipped");
  

  else 
    sprintf(str, "   O2: --");
  screen_area_puts(ge->descript,str);


  if (game_inventory_find_object(game, object_get_id(game_get_object(game, 2))) == TRUE) 
    sprintf(str, "   O3: Equipped");
  

  else 
    sprintf(str, "   O3: --");
  screen_area_puts(ge->descript,str);


  if (game_inventory_find_object(game, object_get_id(game_get_object(game, 3))) == TRUE) 
    sprintf(str, "   O4: Equipped");
  

  else {
    sprintf(str, "   O4: --");
  }
  
  screen_area_puts(ge->descript,str);
  sprintf(str,"    ");
  screen_area_puts(ge->descript,str);


  /*player object
  if(player_get_object(game_get_player(game))!=NO_ID){
    sprintf(str, "   Player Object: o%ld",player_get_object(game_get_player(game)));
    screen_area_puts(ge->descript, str);
  }

  

  else{
    sprintf(str, "   Player object: -- ");  player has not an object
    screen_area_puts(ge->descript, str);
  }*/

  sprintf(str, "  Player Health: %d", player_get_health(game_get_player(game)) );
  screen_area_puts(ge->descript, str);

  sprintf(str, "  Enemy Health: %d", enemy_get_health(game_get_enemy(game)) );
  screen_area_puts(ge->descript, str);

  sprintf(str,"     ");
  screen_area_puts(ge->descript, str);


  
  sprintf(str, "  Inspection area:");
  screen_area_puts(ge->descript, str);

  sprintf(str, "   %s", game_get_descr(game));
  screen_area_puts(ge->descript, str);

  /* Paint in the banner area */
  screen_area_puts(ge->banner, "    The anthill game ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " move(m) + coordenate (n,s,e,w), exit(e), take(t), drop(d), attack(a), inspect(i), turnon(ton), turnoff(toff)");
  screen_area_puts(ge->help, str);
  


  /* Paint in the feedback area */
  last_cmd = game_get_last_command(game);
  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
