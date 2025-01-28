/** 
 * @brief It implements the object module
 * 
 * @file object.c
 * @author Daniel Tirado and Alfonso Crespo
 * @version 2.0 
 * @date 12-02-2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"

/**
 * @brief Object
 *
 * This struct stores all the information of an object.
 */
struct _Object{
  Id id;                       /*!< Id number of the object */
  char name[WORD_SIZE];        /*!< The name of the object */
  char description[MAX_DESCR]; /*!< Description of the object */
  BOOL mobable;                /*!< Whether the object can be moved or not */
  Id dependency;                /*!< The id of the object in which this depends */
  Id open;                     /*!< The link it can open */
  BOOL illuminate;             /*!< If the object can be turned on or not */
  BOOL turnedon;               /*!< If the object is turned on or not */
};


/** object_create allocates memory for a new object
  *  and initializes its members
  */
Object* object_create (Id id) { 
    Object *newObject = NULL;
    
    /* Error control */
    if (id == NO_ID)
        return NULL;
    
    newObject = (Object *) malloc(sizeof(Object));
    if (newObject == NULL)
        return NULL;
    
    /* Initialization of an empty object*/
    newObject->id = id;
    newObject->name[0] = '\0';
    newObject->description[0] = '\0';
    newObject->mobable = FALSE;
    newObject->dependency = NO_ID;
    newObject->open = NO_ID;
    newObject->illuminate = FALSE;
    newObject->turnedon = FALSE;

    return newObject;
}

/** object_destroy frees the previous memory allocation 
  *  for an object
  */
STATUS object_destroy(Object* object) {
    if (!object) {
        return ERROR;
    }
    
    free(object);
    object = NULL;
    return OK;
}

/** It gets the id of an object
  */
Id object_get_id(Object* object) {
    if (!object)
        return NO_ID;
    
    return object->id;
}

STATUS object_set_id(Object* object, Id id) {
    if (!object || id == NO_ID)
        return ERROR;
    
    object->id = id;
    
    return OK;
}

/** It sets the name of an object
  */
STATUS object_set_name(Object* object, char* name) {
    if (!object || !name) 
        return ERROR;
    
    if (!strcpy(object->name, name))
        return ERROR;
    
    return OK;
}

/** It gets the name of an object
  */
const char * object_get_name(Object* object) {
    if (!object) 
        return NULL;
    
    return object->name;
}


/** It gets the description of an object
  */
const char * object_get_description(Object* object) {
    if (!object) 
        return NULL;
    
    return object->description;
}

/** It sets the description of an object
  */
STATUS object_set_description(Object* object, char* description) {
    if (!object || !description) 
        return ERROR;
    
    if (!strcpy(object->description, description))
        return ERROR;
    
    return OK;
}

STATUS object_set_illuminate(Object *object, BOOL illuminate){
    if (!object || !illuminate)
        return ERROR;
    
    object->illuminate = illuminate;
    
    return OK;
}

BOOL object_get_illuminate(Object *object){
    if (!object)
        return NULL;
    
    return object->illuminate;
}

STATUS object_set_turnedon(Object *object, BOOL turnedon){
    if (!object || !turnedon)
        return ERROR;
    
    object->turnedon = turnedon;
    
    return OK;
}

BOOL object_get_turnedon(Object *object){
    if (!object)
        return NULL;
    
    return object->turnedon;
}

/** It prints the object information
  */
STATUS object_print(Object* object) {
    /* Error Control */
    if (!object)
        return ERROR;
    
    /* Print the id and the name of the space */
    fprintf(stdout, "--> Object (Id: %ld; Name: %s; Descr: %s)\n", object->id, object->name, object->description);

    return OK;
}
