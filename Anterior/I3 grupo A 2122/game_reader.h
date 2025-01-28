/**
 * @brief It defines the game_reader interface
 *
 * @file game_reader.h
 * @author Grupo A
 * @version 2.0
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"
#include "space.h"

/**
  * @brief It loads the spaces
  * @author Profesores PPROG
  * @param game a pointer to the game
  * @param filename the name of the file
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS game_reader_load_spaces(Game *game, char *filename);

/**
  * @brief It loads the objects
  * @author Alfonso Crespo
  * @param game a pointer to the game
  * @param filename the name of the file
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS game_reader_load_objects(Game* game,char* filename);

STATUS game_reader_load_player(Game* game,char* filename);

STATUS game_reader_load_enemy(Game* game,char* filename);

STATUS game_reader_load_links(Game *game, char *filename);
#endif