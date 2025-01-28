/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 29-11-2021
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"

typedef struct _Graphic_engine Graphic_engine;

/**
  * @brief It creates the graphic engine
  * @author Profesores PPROG
  *
  * It allocates memory for a pointer
  * to Graphic_engine and initializes its members.

  * @return the pointer, initialized
  */
Graphic_engine *graphic_engine_create();

/**
  * @brief It destroys a graphic engine
  * @author Profesores PPROG
  *
  * It destroys the graphic engine and frees the previous
  * allocation for a graphic engine.
  * 
  * @param id the identification number for the new space
  * @return a new space, initialized
  */
void graphic_engine_destroy(Graphic_engine *ge);

/**
  * @brief It paints the game in the terminal
  * @author Profesores PPROG
  *
  * @param id the identification number for the new space
  * @return a new space, initialized
  */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

#endif
