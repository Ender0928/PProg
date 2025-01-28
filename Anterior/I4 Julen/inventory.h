/**
 * @brief It defines the inventory interface
 *
 * @file inventory.h
 * @author Alfonso Crespo
 * @version 2.0
 * @date 22-03-2022
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H


#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"


typedef struct _Inventory Inventory;

/**
  * @brief It creates a new inventory
  * @author Alfonso Crespo
  * inventory_create allocates memory for a new set and initializes its members
  * @return a new inventory, initialized
  */
Inventory* inventory_create();

/**
  * @brief It destroys an inventory
  * @author Alfonso Crespo
  * inventory_destroy frees the previous memory allocation 
  *  for an inventory
  * @param inv pointer to the inventory that must be destroyed
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS inventory_destroy(Inventory* inv);

/**
  * @brief It adds a new id to the inventory
  * @author Alfonso Crespo
  * @param inv pointer to the set
  * @param obj the id that must be added
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS inventory_add_object(Inventory* inv,Id obj);

/**
  * @brief It delates an id from the inventory
  * @author Alfonso Crespo
  * @param inv pointer to the set
  * @param obj the id that must be delated
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS inventory_del_object(Inventory* inv,Id obj);

/**
  * @brief it finds if the given id is in the inventory
  * @author Alfonso Crespo
  * @param inv pointer to the set
  * @param obj the id that must be searched
  * @return TRUE, if the id is in the inventory or FALSE if it is not
  */
BOOL inventory_find_object(Inventory* inv,Id obj);

/**
  * @brief it verifies if the inventory is full or not
  * @author Alfonso Crespo
  * @param inv pointer to the set
  * @return TRUE, if the inventory is full or FALSE if it is not
  */
BOOL inventory_is_full(Inventory *inv);

/**
 * @brief inventory_set_MaxInv set the num max of objects a player can carry
 * 
 * @param inv 
 * @param MaxInv
 * @return TRUE, if the inventory is full or FALSE if it is not
 */
STATUS inventory_set_MaxInv(Inventory* inv, int MaxInv);

/**
 * @brief inventory_set_MaxInv set the num max of objects a player can carry
 * @author Julen Sáenz
 * @param inv pointer to the inventory
 * @return the max_inv number
 */
int inventory_get_MaxInv(Inventory *inv);

/**
  * @brief It gets the pointer to the ids of the inventory
  * @author Julen Sáenz
  * @param inv pointer to the inventory
  * @return an Id pointer to the ids of the inventory set
  */
Id* inventory_get_set_pointer(Inventory* inv);

/**
  * @brief It prints all the ids of the inventory and the number of ids
  * @author Alfonso Crespo
  * @param inv pointer to the set
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS inventory_print(Inventory* inv);


#endif