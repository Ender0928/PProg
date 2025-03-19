/**
 * @brief It defines the inventory interface
 *
 * @file inventory.h
 * @author Javier Pérez
 * @version 1.0
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"


typedef struct _Inventory Inventory;

/**
  * @brief It creates a new inventory
  * @author Javier Pérez
  * inventory_create allocates memory for a new set and initializes its members
  * @return a new inventory, initialized
  */
Inventory* inventory_create();

/**
  * @brief It destroys an inventory
  * @author Javier Pérez
  * inventory_destroy frees the previous memory allocation 
  *  for an inventory
  * @param inv pointer to the inventory that must be destroyed
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status inventory_destroy(Inventory* inv);

/**
  * @brief It adds a new id to the inventory
  * @author Javier Pérez
  * @param inv pointer to the set
  * @param obj the id that must be added
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status inventory_add_object(Inventory* inv,Id obj);

/**
  * @brief It delates an id from the inventory
  * @author Javier Pérez
  * @param inv pointer to the set
  * @param obj the id that must be delated
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status inventory_remove_object(Inventory* inv,Id obj);

/**
  * @brief it finds if the given id is in the inventory
  * @author Javier Pérez
  * @param inv pointer to the set
  * @param obj the id that must be searched
  * @return TRUE, if the id is in the inventory or FALSE if it is not
  */
Bool inventory_find_object(Inventory* inv, Id obj);

/**
  * @brief it verifies if the inventory is full or not
  * @author Javier Pérez
  * @param inv pointer to the set
  * @return TRUE, if the inventory is full or FALSE if it is not
  */
Bool inventory_is_full(Inventory *inv);

/**
  * @brief it verifies if the inventory is empty or not
  * @param inv pointer to the set
  * @return TRUE, if the inventory is empty or FALSE if it is not
  */
Bool inventory_is_empty(Inventory *inv);

/**
 * @brief inventory_set_max_value set the num max of objects a player can carry
 * @author Javier Pérez
 * @param inv 
 * @param maxValue
 * @return TRUE, if the inventory is full or FALSE if it is not
 */
Status inventory_set_max_value(Inventory* inv, int maxValue);

/**
  * @brief It prints all the ids of the inventory and the number of ids
  * @author Javier Pérez
  * @param inv pointer to the set
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status inventory_print(Inventory* inv);


#endif