/**
 * @brief It defines the set interface
 *
 * @file space.h
 * @author Alfonso Crespo
 * @version 2.0
 * @date 26-02-2022
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
  * @author Alfonso Crespo
  * set_create allocates memory for a new set and initializes its members
  * @return a new Set, initialized
  */
Set* set_create();

/**
  * @brief It destroys a set
  * @author Alfonso Crespo
  * player_destroy frees the previous memory allocation 
  *  for a set
  * @param set pointer to the set that must be destroyed
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS set_destroy(Set* set);

/**
  * @brief It adds a new id to the set
  * @author Alfonso Crespo
  * @param set pointer to the set
  * @param id the id that must be added
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS set_add_object(Set* set,Id id);

/**
  * @brief It delates an id from the set
  * @author Alfonso Crespo
  * @param set pointer to the set
  * @param id the id that must be delated
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS set_del_object(Set* set,Id id);

/**
  * @brief It prints all the ids of the set and the number of ids
  * @author Alfonso Crespo
  * @param set pointer to the set
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS set_print(Set* set);

/**
  * @brief it finds if the given id is in the set of ids
  * @author Alfonso Crespo
  * @param set pointer to the set
  * @param id the id that must be searched
  * @return TRUE, if the id is in the set or FALSE if it is not
  */
BOOL set_find_object(Set* set,Id id);

/**
  * @brief It gets the pointer to the ids
  * @author Alfonso Crespo
  * @param set pointer to the set
  * @return an Id pointer to the ids of the set
  */
Id* set_get_pointer(Set* set);


int set_get_num_of_ids(Set* set);



#endif