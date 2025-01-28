/** 
 * @brief It implements the space module
 * 
 * @file space.c
 * @author Profesores PPROG
 * @version 2.0 
 * @date 29-11-2021 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"
#include "set.h"

/**
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Space {
  Id id;                       /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1];    /*!< Name of the space */
  Set* objects;                /*!< The set of objects of the space */
  char description[MAX_DESCR]; /*!< The description of the space */
  char gdesc[NROWS][NCOLS+1];
  BOOL light;                  /*!< Whether the space has its own light or not */
};

/** space_create allocates memory for a new space
  *  and initializes its members
  */
Space* space_create(Id id) {
  Space *newSpace = NULL;
  int i;

  /* Error control */
  if (id == NO_ID)
    return NULL;

  newSpace = (Space *) malloc(sizeof (Space));
  if (newSpace == NULL) {
    return NULL;
  }

  /* Initialization of an empty space*/
  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->objects = set_create();

  for (i=0; i<NROWS; i++) 
    strcpy(newSpace->gdesc[i], "         ");

  return newSpace;
}

/** space_destroy frees the previous memory allocation 
  *  for a space
  */
STATUS space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

  set_destroy(space->objects);

  free(space);
  return OK;
}

/** It gets the id of a space
  */
Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

/** It sets the name of a space
  */
STATUS space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }
  return OK;
}
/** It gets the name of a space
  */
const char * space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

STATUS space_add_object(Space* space,Id id){
  if(!space || id==NO_ID) return ERROR;

  set_add_object(space->objects,id);

  return OK;
}

STATUS space_del_object(Space* space,Id id){
  if(!space || id==NO_ID) return ERROR;
  if (space_find_object(space,id)==TRUE){
  set_del_object(space->objects,id);
  return OK;
  }
  if(space_find_object(space,id)==FALSE) return ERROR;

  return ERROR;
}

BOOL space_find_object(Space* space,Id id){
  if(!space||id==NO_ID) return FALSE;

  return (set_find_object(space->objects,id));
}

Id* space_get_object_pointer(Space* space){
  if(!space) return NULL;

  return (set_get_pointer(space->objects));
}

/** It gets the description of a space
  */
const char * space_get_description(Space* space){
  if (!space) {
    return NULL;
  }
  return space->description;
}

/** It sets the description of a space
  */
STATUS space_set_description(Space* space, char* description){
  if (!space || !description) {
    return ERROR;
  }

  if (!strcpy(space->description, description)){
    return ERROR;
  }
  return OK;
}

STATUS space_set (Space *s, char *cad, int i) {
  if (!s || !cad || i<0 || i>(NROWS-1)) return ERROR;


  strcpy(s->gdesc[i], cad); 
  return OK;
  
}

char* space_get (Space *s, int i) {
  if (!s || i<0 || i>NCOLS) return NULL;

  return s->gdesc[i];
}

BOOL space_get_light(Space *space) {
  if (!space) {
    return NULL;
  }
  return space->light;
}

STATUS space_set_light(Space *space, BOOL state) {
  if (!space || state==NULL) {
    return ERROR;
  }
  space->light = state;
  return OK;
}

/** It prints the space information
  */
STATUS space_print(Space* space) {
  Id* array_aux=NULL;
  int i=0;
  /* Error Control */
  if (!space) {
    return ERROR;
  }

  /* 1. Print the id and the name of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s; Description: %s; Illumination: %s)\n", space->id, space->name,space->description, space->light);
 
  array_aux=space_get_object_pointer(space);
  if(!array_aux) fprintf(stdout, "No object in this space.\n");

  else{
    for(i=0;i<MAX_ID;i++){
      if(array_aux[i]!=NO_ID){
      fprintf(stdout, "Object %ld in the space.\n",array_aux[i]);
      }
    }
  }


  return OK;
}

