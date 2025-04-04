/**
 * @brief It defines the character interface
 *
 * @file character.h
 * @author Javier Pérez
 * @version 2.0
 */

#ifndef CHARACTER_H
#define CHARACTER_H
#include "types.h"

#define P 1

/**
 * @brief Defines the maximum health of the characters
 */
#define CHARACTER_HEALTH 3

typedef struct _Character Character;

/**
 * @brief It creates a new character
 * @author Javier Pérez
 *
 * character_create allocates memory for a new character and initializes its members
 * @param id the identification number for the new object
 * @return a new character, initialized
 */
Character *character_create(Id id);

/**
 * @brief It destroys a character, freeing its memory
 * @param character pointer to the character that must be destroyed
 * @return OK if successful, ERROR otherwise
 */
Status character_destroy(Character *character);

/**
 * @brief Gets the id of a character
 * @param character pointer to the character
 * @return the id of the character or NO_ID if error
 */
Id character_get_id(Character *character);

/**
 * @brief Gets the name of a character
 * @param character pointer to the character
 * @return the name of the character or NULL if error
 */
const char *character_get_name(Character *character);

/**
 * @brief Sets the name of a character
 * @param character pointer to the character
 * @param name pointer to the name
 * @return OK if successful, ERROR otherwise
 */
Status character_set_name(Character *character, char *name);

/**
 * @brief Gets the graphic description of a character
 * @param character pointer to the character
 * @return the graphic description or NULL if error
 */
const char *character_get_gdesc(Character *character);

/**
 * @brief Sets the graphic description of a character
 * @param character pointer to the character
 * @param gdesc pointer to a string of exactly 6 characters
 * @return OK if successful, ERROR otherwise
 */
Status character_set_gdesc(Character *character, char *gdesc);

/**
 * @brief Gets the health of a character
 * @param character pointer to the character
 * @return the health of the character or -1 if error
 */
int character_get_health(Character *character);

/**
 * @brief Sets the health of a character
 * @param character pointer to the character
 * @param health the new health value (must be >= 0)
 * @return OK if successful, ERROR otherwise
 */
Status character_set_health(Character *character, int health);

/**
 * @brief Checks if a character is friendly
 * @param character pointer to the character
 * @return TRUE if friendly, FALSE otherwise
 */
Bool character_is_friendly(Character *character);

/**
 * @brief Sets the friendly status of a character
 * @param character pointer to the character
 * @param friendly TRUE if friendly, FALSE otherwise
 * @return OK if successful, ERROR otherwise
 */
Status character_set_friendly(Character *character, Bool friendly);

/**
 * @brief Gets the message of a character
 * @param character pointer to the character
 * @return the message or NULL if error
 */
char *character_get_message(Character *character);

/**
 * @brief Sets the message of a character
 * @param character pointer to the character
 * @param message pointer to the message string
 * @return OK if successful, ERROR otherwise
 */
Status character_set_message(Character *character, char *message);

/**
 * @brief Gets the location of a character
 * @param character pointer to the character
 * @return the location ID or NO_ID if error
 */
Id character_get_location(Character *character);

/**
 * @brief Sets the location of a character
 * @param character pointer to the character
 * @param location the new location ID
 * @return OK if successful, ERROR otherwise
 */
Status character_set_location(Character *character, Id location);

/**
 * @brief Prints the information of a character
 * @param character pointer to the character
 * @return OK if successful, ERROR otherwise
 */
Status character_print(Character *character);

#endif
