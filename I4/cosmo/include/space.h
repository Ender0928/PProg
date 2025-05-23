/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"

typedef struct _Space Space;

/**
 * @brief It creates a new space, allocating memory and initializing its members
 * @author Profesores PPROG
 *
 * @param id the identification number for the new space
 * @return a new space, initialized
 */
Space* space_create(Id id);

/**
 * @brief It destroys a space, freeing the allocated memory
 * @author Profesores PPROG
 *
 * @param space a pointer to the space that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_destroy(Space* space);

/**
 * @brief It gets the id of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id of space
 */
Id space_get_id(Space* space);

/**
 * @brief It sets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_name(Space* space, char* name);

/**
 * @brief It gets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return  a string with the name of the space
 */
const char* space_get_name(Space* space);

/**
 * @brief It sets the id of the space located at the north
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the north
 * @return OK, if everything goes well or ERROR if there was some mistake
 */

Status space_set_north(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the north
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the north
 */
Id space_get_north(Space* space);

/**
 * @brief It sets the id of the space located at the south
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the south
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_south(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the south
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the south
 */
Id space_get_south(Space* space);

/**
 * @brief It sets the id of the space located at the east
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the east
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_east(Space* space, Id id);

/**
 * @brief It sets whether the space has been discovered or not
 * @author leandro p
 *
 * @param space a pointer to the space
 * 
 * @return TRUE if the space has been discovered, FALSE otherwise
 */
Bool space_get_discovered(Space* space);
/**
 * @brief It gets whether the space has been discovered or not
 *
 * @author leandro p
 *
 * @param space a pointer to the space
 * @param discovered a boolean, specifying if the space has been discovered (TRUE) or not (FALSE)
 * 
 * @return OK if the space has been discovered, ERROR otherwise
 */
Status space_set_discovered(Space* space, Bool discovered);

/**
 * @brief It gets the id of the space located at the east
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the east
 */
Id space_get_east(Space* space);

/**
 * @brief It sets the id of the space located at the west
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the west
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_west(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the west
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the west
 */
Id space_get_west(Space* space);

/**
 * @brief It sets whether the space has an object or not
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param value a boolean, specifying if in the space there is an object (TRUE) or not (FALSE)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_add_object(Space* space, Id id);

/**
 * @brief It gets whether the space has an object or not
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return a boolean, specifying if in the space there is an object (TRUE) or not (FALSE)
 */
Status space_remove_object(Space* space, Id id);

/**
 * @brief Checks if a space contains a specific object.
 *
 * @param space Pointer to the space.
 * @param id ID of the object to check.
 * @return TRUE if the object is in the space, FALSE otherwise.
 */
Bool space_has_object(Space* space, Id id);

/**
 * @brief Retrieves the IDs of all objects in a space.
 *
 * @param space Pointer to the space.
 * @return Pointer to an array of object IDs, or NULL if no objects exist.
 */
Id* space_get_objects(Space* space);

/**
 * @brief Retrieves the number of objects in a space.
 *
 * @param space Pointer to the space.
 * @return The number of objects in the space.
 */
int space_get_num_objects(Space* space);

/**
 * @brief Retrieves the graphical description (gdesc) of a space.
 *
 * @param space Pointer to the space.
 * @return A 2D array representing the graphical description of the space.
 */
char (*space_get_gdesc(Space *space))[GDESC_COLS];

/**
 * @brief Sets the graphical description (gdesc) of a space.
 *
 * @param space Pointer to the space.
 * @param gdesc A 2D array representing the new graphical description.
 * @return Status indicating success or failure.
 */
Status space_set_gdesc(Space* space, char gdesc[GDESC_ROWS][GDESC_COLS]);

/**
 * @brief It prints the space information
 * @author Profesores PPROG
 *
 * This fucntion shows the id and name of the space, the spaces that surrounds it and wheter it has an object or not.
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_print(Space* space);

#endif
