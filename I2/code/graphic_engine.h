/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"

typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief It creates a new graphic engine
 *
 * Allocates memory for a new graphic engine and initializes the screen areas 
 * for displaying game information.
 *
 * @author Profesores PPROG
 *
 * @return A pointer to the newly created graphic engine, or NULL in case of error
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief It destroys a graphic engine
 *
 * Frees all allocated memory associated with the graphic engine, including 
 * the screen areas, and cleans up resources.
 *
 * @author Profesores PPROG
 *
 * @param ge A pointer to the graphic engine to be destroyed
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief It paints the game state in the screen
 *
 * This function updates the screen areas to reflect the current state of 
 * the game, including the player's location, object positions, and user feedback.
 *
 * @author Profesores PPROG
 *
 * @param ge A pointer to the graphic engine
 * @param game A pointer to the game instance to be displayed
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

#endif
