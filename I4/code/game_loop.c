/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "graphic_engine.h"
#include "game_rules.h"

/**
 * @brief It initializes the game loop
 *
 * It initializes the game and the graphic engine.
 * @param game The game to be initialized
 * @param gengine The graphic engine to be initialized
 * @param file_name The name of the file to be loaded
 *
 * @return 0 if everything is OK, 1 if there is an ERROR
 */
int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);

/**
 * @brief It runs the game loop
 *
 * It runs the game loop until the game is finished or the user exits.
 *
 * @param game The game to be run
 * @param gengine The graphic engine to be used
 */
void game_loop_run(Game *game, Graphic_engine *gengine);

/**
 * @brief It cleans up the game loop
 *
 * It cleans up the game and the graphic engine.
 *
 * @param game The game to be cleaned up
 * @param gengine The graphic engine to be cleaned up
 */
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

void game_loop_store_input(Game *game, char* file_name, Command *last_cmd, Status status);

void game_loop_run_with_file(Game *game, Graphic_engine *gengine, char *file_name);

int main(int argc, char *argv[]) {
  Game *game = NULL;
  Graphic_engine *gengine = NULL;

  if (argc < 2) {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }

  if (argc == 2){
    if (!game_loop_init(&game, &gengine, argv[1])) {
      game_loop_run(game, gengine);
      game_loop_cleanup(game, gengine);
    }
  }

  if (argc == 4) {
    if (strcmp(argv[2], "-l") == 0){
      if (!game_loop_init(&game, &gengine, argv[1])) {
        game_loop_run_with_file(game, gengine, argv[3]);
        game_loop_cleanup(game, gengine);
      }
    } else {
      fprintf(stderr, "Use: %s <game_data_file> -l <log_file>\n", argv[0]);
      return 1;
    }
  }
  return 0;
}

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name) {
  if (game_create_from_file(game, file_name) == ERROR) {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  }

  if ((*gengine = graphic_engine_create()) == NULL) {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    return 1;
  }

  return 0;
}

void game_loop_run(Game *game, Graphic_engine *gengine) {
  Command *last_cmd;
  Status status;

  if (!gengine) {
    return;
  }

  last_cmd = game_get_last_command(game);

  while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE)) {
    graphic_engine_paint_game(gengine, game);
    command_get_user_input(last_cmd);

    status = game_actions_update(game, last_cmd);
    game_set_command_status(game, status);
    gamerules_run(game);
    game_next_turn(game);
  }
}

void game_loop_run_with_file(Game *game, Graphic_engine *gengine, char *file_name) {
  Command *last_cmd;
  Status status;

  if (!gengine) {
    return;
  }

  last_cmd = game_get_last_command(game);

  while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE)) {
    graphic_engine_paint_game(gengine, game);
    command_get_user_input(last_cmd);

    status = game_actions_update(game, last_cmd);
    game_set_command_status(game, status);
    game_loop_store_input(game, file_name, last_cmd, status);
    game_next_turn(game);
  }
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine) {
  game_destroy(&game);
  game = NULL;
  graphic_engine_destroy(gengine);
  gengine = NULL;
}

void game_loop_store_input(Game *game, char* file_name, Command *last_cmd, Status status) {
  FILE *file = NULL;
  if (!game) {
    return;
  }

  file = fopen(file_name, "a+");
  if (file == NULL) {
    fprintf(stderr, "Error opening log file.\n");
    return;
  }

  fprintf(file, "\n%s %s", game_get_str_command(game), status == OK ? "OK" : "ERROR");
  fclose(file);
}
