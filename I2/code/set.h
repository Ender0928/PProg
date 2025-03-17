/**
 * @brief It defines the set interface
 *
 * @file space.h
 * @author Javier Pérez
 * @version 2.0
 * @date 23-02-2025
 */

#ifndef SET_H
#define SET_H

#include "types.h"

/**
* @brief set struct
*
*/
typedef struct _Set Set;

/**
  * @brief It creates a new set
  * @author Javier Pérez
  * set_create allocates memory for a new set and initializes its members
  * @return a new Set, initialized
  */
Set* set_create();

/**
  * @brief It destroys a set
  * @author Javier Pérez
  * player_destroy frees the previous memory allocation 
  *  for a set
  * @param set pointer to the set that must be destroyed
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status set_destroy(Set* set);

/**
  * @brief It adds a new id to the set
  * @author Javier Pérez
  * @param player pointer to the set
  * @param id the id that must be added
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status set_add_object(Set* set,Id id);

int set_size(Set *set);

/**
  * @brief It delates an id from the set
  * @author Javier Pérez
  * @param player pointer to the set
  * @param id the id that must be delated
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status set_remove_object(Set* set,Id id);

/**
  * @brief It prints all the ids of the set and the number of ids
  * @author Javier Pérez
  * @param player pointer to the set
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status set_print(Set* set);

/**
  * @brief it finds if the given id is in the set of ids
  * @author Javier Pérez
  * @param player pointer to the set
  * @param id the id that must be searched
  * @return TRUE, if the id is in the set or FALSE if it is not
  */
Bool set_find_object(Set* set,Id id);

/**
  * @brief It gets the pointer to the ids
  * @author Javier Pérez
  * @param player pointer to the set
  * @return an Id pointer to the ids of the set
  */
Id* set_get_ids(Set* set);






#endif