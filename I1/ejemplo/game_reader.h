#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

/**
  * @brief It loads the spaces
  * @author Profesores PPROG
  * @param game a pointer to the game
  * @param filename the name of the file
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status game_reader_load_spaces(Game *game, char *filename);


#endif