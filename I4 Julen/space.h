/**
 * @brief It defines the space interface
 *
 * @file space.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 29-11-2021
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"

typedef struct _Space Space;

#define MAX_SPACES 100
#define FIRST_SPACE 1

/**
  * @brief It creates a new space
  * @author Profesores PPROG
  *
  * space_create allocates memory for a new space
  *  and initializes its members
  * @param id the identification number for the new space
  * @return a new space, initialized
  */
Space* space_create(Id id);

/**
  * @brief It destroys a space
  * @author Profesores PPROG
  *
  * space_destroy frees the previous memory allocation 
  *  for a space
  * @param space a pointer to the space that must be destroyed  
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS space_destroy(Space* space);

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
STATUS space_set_name(Space* space, char* name);

/**
  * @brief It gets the name of a space
  * @author Profesores PPROG
  * 
  * @param space a pointer to the space
  * @return  a string with the name of the space
  */
const char* space_get_name(Space* space);

/**
  * @brief It prints the space information
  * @author Profesores PPROG
  *
  * This fucntion shows the id and name of the space, the spaces that surrounds it and wheter it has an object or not.
  * @param space a pointer to the space
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS space_print(Space* space);


/**
  * @brief It adds a new id to the set of objects
  * @author Alfonso Crespo
  * @param player pointer to the set
  * @param id the id that must be added
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS space_add_object(Space* space,Id id);

/**
  * @brief It delates an id of the set of objects
  * @author Alfonso Crespo
  * @param player pointer to the set
  * @param id the id that must be delated
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS space_del_object(Space* space,Id id);

Id* space_get_object_pointer(Space* space);
BOOL space_find_object(Space* space,Id id);

/**
  * @brief It gets the always shown description of the space
  * @author Julen Sáenz
  * @param space pointer to the space
  * @return A string with the always shown description of the space
  */
const char* space_get_description(Space* space);

/**
  * @brief It sets the always shown description of the space
  * @author Julen Sáenz
  * @param space pointer to the space
  * @param description a string with the always shown description  of the space
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS space_set_description(Space* space, char* description);

/**
  * @brief It gets the inspected description of the space
  * @author Julen Sáenz
  * @param space pointer to the space
  * @return A string with the inspected description of the space
  */
const char* space_get_idescription(Space* space);

/**
  * @brief It sets the inspected description of the space
  * @author Julen Sáenz
  * @param space pointer to the space
  * @param description a string with the inspected description  of the space
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS space_set_idescription(Space* space, char* description);

STATUS space_set (Space *s, char *cad, int i);

char* space_get (Space *s, int i);

/**
  * @brief It gets the state of the space own illumination
  * @author Julen Sáenz
  * @param space pointer to the space
  * @return TRUE, if there is natural light or FALSE if not
  */
BOOL space_get_light(Space *space);
/**
  * @brief It sets the state of the space own illumination
  * @author Julen Sáenz
  * @param space pointer to the space
  * @param state the state of the space illumination
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS space_set_light(Space *space, BOOL state);

#endif
