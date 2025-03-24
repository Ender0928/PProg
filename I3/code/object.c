/** 
 * @brief It implements the object module
 * 
 * @file object.c
 * @author Javier and Rubén
 * @version 1.0 
 * @date 28-01-2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"

struct _Object{
  Id id;            /*!< Id number of the object, it must be unique */
  char name[TAM];   /*!< Name of the space */
  char description[TAM];
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

    return newObject;
}

/** object_destroy frees the previous memory allocation 
  *  for an object
  */
Status object_destroy(Object* object) {
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

Status object_set_id(Object* object, Id id) {
    if (!object || id == NO_ID)
        return ERROR;
        
    object->id = id;
    return OK;
}

/** It sets the name of an object
  */
Status object_set_name(Object* object, char* name) {
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

/** It sets the description of an object
  */
Status object_set_description(Object* object, char *description) {
    if (!object ||!description) {
        return ERROR;
    }
    if (!strcpy(object->description, description)){
        return ERROR;
    }
    return OK;
}

/** It gets the description of an object
  */
char *object_get_description(Object* object) {
    if (!object) 
        return NULL;
    
    return object->description;
}

/** It prints the object information
  */
Status object_print(Object* object) {
    /* Error Control */
    if (!object)
        return ERROR;
    
    /* Print the id and the name of the space */
    fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

    return OK;
}