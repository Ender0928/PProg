/**
 * @brief It defines the object interface
 *
 * @file object.h
 * @author Daniel Tirado and Alfonso Crespo
 * @version 2.0
 * @date 12-02-2022
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

#define O 45
#define TAM 256

typedef struct _Object Object;

/**
  * @brief It creates a new object
  * @author Daniel Tirado and Alfonso Crespo
  *
  * object_create allocates memory for a new object
  *  and initializes its members
  * @param id the identification number for the new object
  * @return a new object, initialized
  */
Object* object_create (Id id);

/**
  * @brief It destroys an object
  * @author Daniel Tirado and Alfonso Crespo
  *
  * object_destroy frees the previous memory allocation 
  *  for an object
  * @param object a pointer to the object that must be destroyed  
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS object_destroy(Object* object);


/**
  * @brief It gets the id of an object
  * @author Daniel Tirado and Alfonso Crespo
  * 
  * @param object a pointer to the object  
  * @return the id of object
  */
Id object_get_id(Object* object);

/**
  * @brief It sets the id of an object
  * @author Daniel Tirado and Alfonso Crespo
  * 
  * @param object a pointer to the object  
  * @return the id of object
  */
STATUS object_set_id(Object* object, Id id);

/**
  * @brief It sets the name of an object
  * @author Daniel Tirado and Alfonso Crespo
  * 
  * @param space a pointer to the object
  * @param name a string with the name to store
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS object_set_name(Object* object, char* name);

/**
  * @brief It gets the name of an object
  * @author Daniel Tirado and Alfonso Crespo
  * 
  * @param object a pointer to the object
  * @return  a string with the name of the object
  */
const char * object_get_name(Object* object);


STATUS object_print(Object* object);

#endif
