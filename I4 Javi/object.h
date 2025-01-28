/**
 * @brief It implements the object module
 *
 * @file object.h
 * @author Julen
 * @version 2.0
 * @date 16-02-2022
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

typedef struct _Object Object;

/**
  * @brief It creates a new object
  * @author Profesores PPROG
  *
  * object_create allocates memory for a new object
  *  and initializes its members
  * @param id the identification number for the new object
  * @return a new object, initialized
  */
Object* object_create(Id id);

/**
  * @brief It destroys an object
  * @author Profesores PPROG
  *
  * object_destroy frees the previous memory allocation 
  *  for an object
  * @param object a pointer to the object that must be destroyed  
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS object_destroy(Object* object);

/**
  * @brief It gets the id of an object
  * @author Profesores PPROG
  * 
  * @param object a pointer to the object  
  * @return the id of object
  */
Id object_get_id(Object* object);

/**
  * @brief It sets the name of a object
  * @author Profesores PPROG
  * 
  * @param object a pointer to the object
  * @param name a string with the name to store
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS object_set_name(Object* object, char* name);

/**
  * @brief It gets the name of a object
  * @author Profesores PPROG
  * 
  * @param object a pointer to the object
  * @return  a string with the name of the object
  */
const char* object_get_name(Object* object);

/**
  * @brief It sets the id of the location of the object
  * @author Julen
  *
  * @param object a pointer to the object
  * @param location the id of the location
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS object_set_location(Object* object, Id location);
/**
  * @brief It sets the mobable of an object
  * @author Daniel Tirado and Alfonso Crespo
  * 
  * @param object a pointer to the object
  * @param mobable if it can be moved or not
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS object_set_mobable(Object *object, BOOL mobable);
/**
  * @brief It gets the mobable of an object
  * @author Daniel Tirado and Alfonso Crespo
  * 
  * @param object a pointer to the object
  * @return  if the object can be moved 
  */
BOOL object_get_mobable(Object *object);
/**
  * @brief It sets the dependecy of an object
  * @author Daniel Tirado and Alfonso Crespo
  * 
  * @param object a pointer to the object
  * @param dependecy the id of the object
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS object_set_dependecy(Object *object, Id dependecy);
/**
  * @brief It gets the dependecy of an object
  * @author Daniel Tirado and Alfonso Crespo
  * 
  * @param object a pointer to the object
  * @return  the object which it depends
  */
Id object_get_dependecy(Object *object);
/**
  * @brief It sets if this object can open a door
  * @author Daniel Tirado and Alfonso Crespo
  * 
  * @param object a pointer to the object
  * @param open the id of the object that it opens
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS object_set_open(Object *object, Id open);
/**
  * @brief It gets the object it opens
  * @author Daniel Tirado and Alfonso Crespo
  * 
  * @param object a pointer to the object
  * @return  a string with the name of the object
  */
Id object_get_open(Object *object);
/**
  * @brief It sets if the object is illuminated
  * @author Daniel Tirado and Alfonso Crespo
  * 
  * @param object a pointer to the object
  * @param illuminate if the object is illuminated or not
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS object_set_illuminate(Object *object, BOOL illuminate);
/**
  * @brief It gets if the object is illuminated
  * @author Daniel Tirado and Alfonso Crespo
  * 
  * @param object a pointer to the object
  * @return  if the object is illuminated or not
  */
BOOL object_get_illuminate(Object *object);
/**
  * @brief It sets if an object is turned on or not
  * @author Daniel Tirado and Alfonso Crespo
  * 
  * @param object a pointer to the object
  * @param turnedon if the object is turned on or not
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS object_set_turnedon(Object *object, BOOL turnedon);
/**
  * @brief It gets if an object is turned on or not
  * @author Daniel Tirado and Alfonso Crespo
  * 
  * @param object a pointer to the object
  * @return  if the object can be turned on ro not
  */
BOOL object_get_turnedon(Object *object);
/**
  * @brief It prints the object information
  * @author Profesores PPROG
  *
  * This fucntion shows the id and name of the object.
  * @param object a pointer to the object
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS object_print(Object* object);

#endif