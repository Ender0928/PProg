#ifndef GAME_MANAGEMENT_H
#define GAME_MANAGEMENT_H

#include "game.h"
#include "game_reader.h"
#include "player.h"
#include "space.h"
#include "object.h"
#include "link.h"
#include "character.h"
#include "types.h"

/**
 * @brief Loads the game from a file.
 * 
 * This function loads the game from a file, including spaces, objects, characters, and players.
 * It initializes the game structure and populates it with the data read from the file.
 * 
 * @param game Pointer to the game structure to be loaded.
 * @param filename Name of the file to load the game from.
 * 
 * @return OK if the game was loaded successfully, ERROR otherwise.
 */
Status game_management_load(Game *game, char *filename);

/**
 * @brief Saves the game to a file.
 * 
 * This function saves the current state of the game to a file, including spaces, objects, characters, and players.
 * It serializes the game structure and writes it to the specified file.
 * 
 * @param game Pointer to the game structure to be saved.
 * @param filename Name of the file to save the game to.
 * 
 * @return OK if the game was saved successfully, ERROR otherwise.
 */
 Status game_management_save(Game *game, char *filename);

#endif
