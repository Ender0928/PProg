/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 2.0
 * @date 30-11-2020
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphic_engine.h"
#include "game.h"
#include "command.h"

/**
  * @brief It start the game and the graphics engine
  * @author Profesores PPROG
  * @param game a pointer to the new game
  * @param gengine a double pointer to the graphics engine
  * @param file_name a pointer to a character with the name of the .txt file
  * @return returns 0 if there were no errors, otherwise 1
  */
int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);

/**
  * @brief makes the game continue, the graphical interface and all the necessary processes until otherwise indicated
  * @author Profesores PPROG
  * @param game variable type game
  * @param gengine a pointer to the graphics engine
  * @return nothing
  * frees up GUI and game memory
  */
void game_loop_run(Game game, Graphic_engine *gengine);

/**
  * @brief frees up GUI and game memory
  * @author Profesores PPROG
  * @param game variable type game
  * @param gengine a pointer to the graphics engine
  * @return nothing
  */
void game_loop_cleanup(Game game, Graphic_engine *gengine);

int main(int argc, char *argv[])
{
  /*error handling*/
  Game game;
  Graphic_engine *gengine;

  /*asks the user for the .txt file*/
  if (argc < 2)
  {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }

  /*start and end the game*/
  if (!game_loop_init(&game, &gengine, argv[1]))
  {
    game_loop_run(game, gengine);
    game_loop_cleanup(game, gengine);
  }

  return 0;
}

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name)
{
  /*start the game and error control*/
  if (game_create_from_file(game, file_name) == ERROR)
  {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  }

  if ((*gengine = graphic_engine_create()) == NULL)
  {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    return 1;
  }

  return 0;
}

/*makes the game not end until the user wants*/
void game_loop_run(Game game, Graphic_engine *gengine)
{
  T_Command command = NO_CMD;

  while ((command != EXIT) && !game_is_over(&game))
  {
    graphic_engine_paint_game(gengine, &game);
    command = command_get_user_input();
    game_update(&game, command);
  }
}

/*frees the allocated memory*/
void game_loop_cleanup(Game game, Graphic_engine *gengine)
{
  game_destroy(&game);
  graphic_engine_destroy(gengine);
}
