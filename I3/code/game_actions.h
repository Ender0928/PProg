/**
 * @brief It defines the game update interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "command.h"
#include "game.h"
#include "types.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include "character.h"

/**
 * @brief Updates the game state based on user input
 *
 * This function processes the last command entered by the player and
 * executes the corresponding action, modifying the game state accordingly.
 * 
 * The function recognizes and handles the following commands:
 * - `UNKNOWN`: Does nothing when an unrecognized command is entered.
 * - `EXIT`: Handles the exit action.
 * - `NEXT`: Moves the player to the next space (south).
 * - `BACK`: Moves the player to the previous space (north).
 * - `TAKE`: Allows the player to pick up an object if they are at the same location as the object.
 * - `DROP`: Allows the player to drop the currently held object.
 *
 * @author Profesores PPROG
 *
 * @param game A pointer to the game instance
 * @param command A pointer to the command entered by the player
 * @return OK if the command was processed successfully, ERROR otherwise
 */
Status game_actions_update(Game *game, Command *cmd);

/**
 * @brief Pick up an object from the current location
 * 
 * This function allows the player to pick up an object from the current location
 * if the object is present and the player is not already holding an object.
 * 
 * @param game A pointer to the game instance
 * @param name The name of the object to pick up
 * @param location The ID of the current location
 * @param objects A pointer to the array of objects in the current location
 * @return OK if the object was picked up successfully, ERROR otherwise
 */

Id select_object_in_current_location_by_name(Game *game, char *name, Id location, Object **objects);


#endif
