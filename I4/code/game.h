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
#include "battle.h"

#define MAX_SPACES 100

typedef struct _Game Game; 
typedef struct _GameRules GameRules;


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
Status game_set_object_location(Game *game, Id id, Id space_id);

   /**  
      * @brief It returns the movable variable of a selected object 
      * @author Profesores PPROG
      * 
      * @param game a pointer to the game
      * @param object_id an id with the object's id
      * @return the value of the movable variable
      */
Bool  game_get_object_movable(Game *game, Id object_id);
   
   /**  
      * @brief It returns the dependency variable of a selected object 
      * @author Profesores PPROG
      * 
      * @param game a pointer to the game
      * @param object_id an id with the object's id
      * @return the value of the dependency variable
      */
Id game_get_object_dependency(Game *game, Id object_id);
   
   /**  
      * @brief It returns the Id of the object that depends from a given one
      * @author Profesores PPROG
      * 
      * @param game a pointer to the game
      * @param object_id an id with the id of the object we want to know which other object depends from it
      * @return the id of the dependent object
      */
Id game_get_object_that_depent_from_a_given(Game *game, Id object_id);
   
   /**  
      * @brief It returns a pointer to a link by a given id 
      * @author Profesores PPROG
      * 
      * @param game a pointer to the game
      * @param link_id the id form the link wanted
      * @return a pointer to the searched link
      */
Link *game_get_link_by_id(Game *game, Id link_id);
   
   /**  
      * @brief It returns the id of a link by a given name
      * @author Profesores PPROG
      * 
      * @param game a pointer to the game
      * @param link_name the name of the link's id we want
      * @return the id of the link
      */
Id game_get_link_id_by_name(Game *game,char *link_name);

   /**  
      * @brief It returns the id of a character by a given name
      * @author Profesores PPROG
      * 
      * @param game a pointer to the game
      * @param character_name the name of the character's id we want
      * @return the id of the Character
      */

Id game_get_character_id_by_name(Game *game, char *character_name);
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


/**
 * @brief it gets the name of an object by its id
 *
 * @param game a pointer to the game
 * @param id_object the id of the object
 * @return the name of the object
 */
char* game_get_object_description(Game *game, Id id_object);

/**
 * @brief it sets the name of an object by its id
 *
 * @param game a pointer to the game
 * @param description the name of the object
 * @param id_object the id of the object
 * @return OK if everything goes well, ERROR if there was some mistake
 */
Status game_set_object_description(Game *game, char *description, Id id_object);

/**
 * @brief Retrieves the player's backpack (inventory).
 *
 * @param game Pointer to the game structure.
 * @return Pointer to the player's inventory.
 */
 Inventory *game_get_player_backpack(Game *game);

/**
 * @brief Retrieves the ID of the connection in a specific direction from a space.
 *
 * @param game Pointer to the game structure.
 * @param space_id ID of the space.
 * @param dir Direction of the connection.
 * @return ID of the connected space, or NO_ID if no connection exists.
 */
 Id game_get_connection(Game *game, Id space_id, Direction dir);
 
/**
 * @brief Checks if a connection in a specific direction is open.
 *
 * @param game Pointer to the game structure.
 * @param space_id ID of the space.
 * @param dir Direction of the connection.
 * @return TRUE if the connection is open, FALSE otherwise.
 */
 Bool game_connection_is_open(Game *game, Id space_id, Direction dir);
 
/**
 * @brief Adds a link to the game.
 *
 * @param game Pointer to the game structure.
 * @param link Pointer to the link to be added.
 * @return Status indicating success or failure.
 */
 Status game_add_link(Game *game, Link *link);
 
/**
 * @brief Adds a player to the game.
 *
 * @param game Pointer to the game structure.
 * @param player Pointer to the player to be added.
 * @return Status indicating success or failure.
 */
 Status game_add_player(Game *game, Player *player);
 
/**
 * @brief Advances the game to the next turn.
 *
 * @param game Pointer to the game structure.
 * @return Status indicating success or failure.
 */
 Status game_next_turn(Game *game);

 int game_get_n_characters(Game *game);

 char *game_get_str_command(Game *game);

 Character * game_get_character_by_name_at_location(Game *game, char *name, Id location);

 Status game_set_character_location(Game *game, Character *c, Id location_id);

 Status game_set_character_follow(Game *game, Id character_id, Id player_id);

 int game_get_n_characters(Game *game);
 
 Character *game_get_character_by_index(Game *game, int i);
 
 int game_get_n_spaces(Game *game);

 Space *game_get_space_by_index(Game *game, Id index);

 int game_get_n_links(Game *game);

 Link *game_get_link_by_index(Game *game, Id index);

 int game_get_n_players(Game *game);

 Player *game_get_player_by_index(Game *game, Id index);

 int game_get_n_objects(Game *game);
 
 Object *game_get_object_by_index(Game *game, Id index); 
 
 void game_clean(Game *game);
 
/**
 * @brief Prints the details of a specific space in the game.
 *
 * @param game Pointer to the game structure.
 * @param space Pointer to the space to be printed.
 * @return Status indicating success or failure.
 */
 Status game_space_print(Game *game, Space *space);

/**
 * @brief Obtiene un personaje por su ID
 * 
 * @param game El juego
 * @param id El ID del personaje a buscar
 * @return Character* puntero al personaje o NULL si no se encuentra
 */
 

 Character *game_get_character(Game *game, Id id);


/**
 * @brief Obtiene si se ha formado un grupo
 * 
 * @param game El juego
 * 
 * @return true si se ha formado un grupo, false en caso contrario
 */

 Bool game_get_group(Game *game);

 /**
 * @brief Settea si se ha formado un grupo
 * 
 * @param game El juego
 * @param group true si se ha formado un grupo, false en caso contrario
 * 
 * @return Ok si se ha seteado correctamente, error en caso contrario
 */

 Status game_set_group(Game *game, Bool group);

 int game_get_characters_at_location(Game *game, Id location, Character **result);

 GameRules *game_get_rules(Game *game);

 Link *game_get_link(Game *game, Id link_id);

 void game_set_state(Game *game, GameState state);

 GameState game_get_state(Game *game);

 Battle *game_get_battle(Game *game);

void game_set_revival_space(Game *game, Id space_id); 

Id game_get_revival_space(Game *game);

Status game_drop_all_objects(Game *game);

#endif
