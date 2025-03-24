/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"
#include "object.h"
#include "player.h"
#include "character.h"
#include "link.h"

#define MAX_SPACES 100

typedef struct _Game Game; 

/**  
   * @brief It creates a new game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @return a new Game, initialized
   */
Status game_create(Game **game);

/**  
   * @brief It creates a new game from a file
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param filename a pointer to the name of the file
   * @return a new Game, initialized
   */
Status game_create_from_file(Game **game, char *filename);

/**  
   * @brief It destroys a game and frees its memory allocation
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game that must be destroyed
   * @return OK, if everything goes well or ERROR if there was some mistake
   */
Status game_destroy(Game **game);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Space *game_get_space(Game *game, Id id);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Status game_add_space(Game *game, Space *space);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Id game_get_player_location(Game *game);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Status game_set_player_location(Game *game, Id id);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Id game_get_object_location(Game *game, Id object_id);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a poinchar *game_get_object_name_by_id(Game *game, Id id)ter to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Status game_set_object_location(Game *game, Id id, Id space_id);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Command* game_get_last_command(Game *game);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Status game_set_last_command(Game *game, Command *command);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Bool game_get_finished(Game *game);

/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief Retrieves the player from the game.
 * 
 * @param game Pointer to the game structure.
 * @return Pointer to the player.
 */
Player *game_get_player(Game *game);

/**
 * @brief Adds an object to the game.
 * 
 * @param game Pointer to the game structure.
 * @param object Pointer to the object to be added.
 * @return Status indicating success or failure.
 */
Status game_add_object(Game *game, Object *object);

/**
 * @brief Retrieves an object from the game by its ID.
 * 
 * @param game Pointer to the game structure.
 * @param id ID of the object to retrieve.
 * @return Pointer to the object, or NULL if not found.
 */
Object *game_get_object(Game *game, Id id);

/**
 * @brief Checks if the game contains an object with the given ID.
 * 
 * @param game Pointer to the game structure.
 * @param id ID of the object to check.
 * @return TRUE if the object exists, FALSE otherwise.
 */
Bool game_has_object(Game *game, Id id);

/**
 * @brief Adds a character to the game.
 * 
 * @param game Pointer to the game structure.
 * @param character Pointer to the character to be added.
 * @return Status indicating success or failure.
 */
Status game_add_character(Game *game, Character *character);

/**
 * @brief Removes a character from the game by its ID.
 * 
 * @param game Pointer to the game structure.
 * @param id ID of the character to remove.
 * @return Status indicating success or failure.
 */
Status game_remove_character(Game *game, Id id);

/**
 * @brief Checks if the game contains a character with the given ID.
 * 
 * @param game Pointer to the game structure.
 * @param id ID of the character to check.
 * @return TRUE if the character exists, FALSE otherwise.
 */
Bool game_has_character(Game *game, Id id);

/**
 * @brief Retrieves all objects in the game.
 * 
 * @param game Pointer to the game structure.
 * @return Array of pointers to objects, or NULL if no objects exist.
 */
Object **game_get_objects(Game *game);

/**
 * @brief Retrieves the character located at a specific location.
 * 
 * @param game Pointer to the game structure.
 * @param location ID of the location to check.
 * @return Pointer to the character at the location, or NULL if none exists.
 */
Character *game_get_character_at_location(Game *game, Id location);

/**
 * @brief Retrieves the player's health.
 * 
 * @param game Pointer to the game structure.
 * @return The player's health as an integer.
 */
int game_get_player_health(Game *game);

/**
 * @brief Retrieves the health of a specific character.
 * 
 * @param game Pointer to the game structure.
 * @param character Pointer to the character.
 * @return The character's health as an integer.
 */
int game_get_character_health(Game *game, Character *character);

/**
 * @brief Sets the player's health.
 * 
 * @param game Pointer to the game structure.
 * @param health New health value for the player.
 * @return Status indicating success or failure.
 */
Status game_set_player_health(Game *game, int health);

/**
 * @brief Sets the health of a specific character.
 * 
 * @param game Pointer to the game structure.
 * @param character Pointer to the character.
 * @param health New health value for the character.
 * @return Status indicating success or failure.
 */
Status game_set_character_health(Game *game, Character *character, int health);

/**
 * @brief Retrieves the game's description.
 * 
 * @param game Pointer to the game structure.
 * @return Pointer to the game's description string.
 */
char *game_get_description(Game *game);

/**
 * @brief Retrieves all characters in the game.
 * 
 * @param game Pointer to the game structure.
 * @return Array of pointers to characters, or NULL if no characters exist.
 */
Character **game_get_characters(Game *game);

/**
 * @brief Sets the status of the last executed command in the game.
 * 
 * @param game Pointer to the game structure.
 * @param status Status to set for the last command.
 * @return Status indicating success or failure.
 */
Status game_set_command_status(Game *game, Status status);

/**
 * @brief Retrieves the status of the last executed command in the game.
 * 
 * @param game Pointer to the game structure.
 * @return Status of the last executed command.
 */
Status game_get_command_status(Game *game);

/**
 * @brief Sets the game's description.
 * 
 * @param game Pointer to the game structure.
 * @param description New description string for the game.
 * @return Status indicating success or failure.
 */
Status game_set_description(Game *game, char *description);

/**
 * @brief Retrieves the ID of a specific object by its name.
 * 
 * @param game Pointer to the game structure.
 * @param name Name of the object to search for.
 * @return ID of the object, or NO_ID if not found.
 */
Id game_get_object_id_by_name(Game *game, char *name);

/**
 * @brief Adds an object to the player's inventory.
 * 
 * @param game Pointer to the game structure.
 * @param object_id ID of the object to add.
 * @return Status indicating success or failure.
 */
Status game_add_object_to_player(Game *game, Id object_id);

/**
 * @brief Removes an object from the player's inventory.
 * 
 * @param game Pointer to the game structure.
 * @param object_id ID of the object to remove.
 * @return Status indicating success or failure.
 */
Status game_remove_object_from_player(Game *game, Id object_id);
/**  
   * @brief It returns the id of a space in a game
   * @author Profesores PPROG
   * 
   * @param game a pointer to the game
   * @param position an integer with the position of the space
   * @return the id of the space located at the position given
   */
void game_print(Game *game);


char*game_get_object_description(Game *game, Id id_object);
Status game_set_object_description(Game *game, char *description, Id id_object);
Inventory *game_get_player_backpack(Game *game);

Id game_get_connection(Game *game, Id space_id, Direction dir);

Bool game_connection_is_open(Game *game, Id space_id, Direction dir);

Status game_add_link(Game *game, Link *link);

Status game_add_player(Game *game, Player *player);

#endif
