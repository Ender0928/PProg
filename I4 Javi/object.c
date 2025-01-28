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
  Id id;    /*id number of the object*/
  char name[WORD_SIZE];     /*the name of the object*/
  char dscr[WORD_S]; /*description of the object*/
  BOOL mobable; /*if the object can be moved or not*/
  Id dependecy; /*Objeto al que es dependiente este objeto*/
  Id open;      /*Objeto al que puede abrir */
  BOOL illuminate;  /*if the object can iluminate the space or not*/
  BOOL turnedon;    /*if the object can be turned on or not*/
};

STATUS object_set_mobable(Object *object, BOOL mobable){
    if (!object || !id)
        return ERROR;
    
    object->mobable = mobable;
    
    return OK;
}

BOOL object_get_mobable(Object *object){
    if (!object)
        return NO_ID;
    
    return object->mobable;
}

STATUS object_set_dependecy(Object *object, Id dependecy){
    if (!object || id == NO_ID)
        return ERROR;
    
    object->dependecy = dependecy;
    
    return OK;
}

Id object_get_dependecy(Object *object){
    if (!object)
        return NO_ID;
    
    return object->dependecy;
}

STATUS object_set_open(Object *object, Id open){
    if (!object || id == NO_ID)
        return ERROR;
    
    object->open = open;
    
    return OK;
}

Id object_get_open(Object *object){
    if (!object)
        return NO_ID;
    
    return object->open;
}

STATUS object_set_illuminate(Object *object, BOOL illuminate){
    if (!object || id == NO_ID)
        return ERROR;
    
    object->illuminate = illuminate;
    
    return OK;
}

BOOL object_get_illuminate(Object *object){
    if (!object)
        return NO_ID;
    
    return object->illuminate;
}

STATUS object_set_turnedon(Object *object, BOOL turnedon){
    if (!object || !id)
        return ERROR;
    
    object->turnedon = turnedon;
    
    return OK;
}

BOOL object_get_turnedon(Object *object){
    if (!object)
        return NO_ID;
    
    return object->turnedon;
}

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
    newObject->mobable = FALSE;
    newObject->dependecy = NO_ID;
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

STATUS object_set_descr(Object* object, char* descr){
    if(!object||!descr) return ERROR;

    strcpy(object->dscr,descr);

    return OK;
}

char* object_get_descr(Object* object){
    if(!object) return NULL;

    return object->dscr;
}

/** It prints the object information
  */
STATUS object_print(Object* object) {
    /* Error Control */
    if (!object)
        return ERROR;
    
    /* Print the id and the name of the space */
    fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

    return OK;
}
