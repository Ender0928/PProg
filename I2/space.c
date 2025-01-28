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
  Id id;                    /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the space */
  Id north;                 /*!< Id of the space at the north */
  Id south;                 /*!< Id of the space at the south */
  Id east;                  /*!< Id of the space at the east */
  Id west;                  /*!< Id of the space at the west */
  Set* objects;             /*!< The set of objects of the space */
  char gdesc[5][9];              
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
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->objects = set_create();

  for(i=0;i<5;i++){
    strcpy(newSpace->gdesc[i],"        ");

  }

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

/** It sets the id of the space located at the north
  */
STATUS space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}
/** It gets the id of the space located at the north
  */
Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}

/** It sets the id of the space located at the south
  */
STATUS space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}
/** It gets the id of the space located at the south
  */
Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}

/** It sets the id of the space located at the east
  */
STATUS space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}
/** It gets the id of the space located at the east
  */
Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}

/** It sets the id of the space located at the west
  */
STATUS space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}
/** It gets the id of the space located at the west
  */
Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
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
/** It prints the space information
  */
STATUS space_print(Space* space) {
  Id idaux = NO_ID;
  Id* array_aux=NULL;
  int i=0;
  char* gdesc=NULL;
  /* Error Control */
  if (!space) {
    return ERROR;
  }

  /* 1. Print the id and the name of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);
 
  /* 2. For each direction, print its link */ 
  idaux = space_get_north(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }
  idaux = space_get_south(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }
  idaux = space_get_east(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }
  idaux = space_get_west(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  array_aux=space_get_object_pointer(space);
  if(!array_aux) fprintf(stdout, "No object in this space.\n");

  else{
    for(i=0;i<MAX_ID;i++){
      if(array_aux[i]!=NO_ID){
      fprintf(stdout, "Object %ld in the space.\n",array_aux[i]);
      }
    }
  }

  for(i=0;i<5;i++){
    gdesc = space_get_gdesc(space,i);
    if (!gdesc){
      fprintf(stdout, "---> No gdesc in line %d",i);
    }
    
    else{
      fprintf(stdout, "---> Gdesc of line %d: %s",i,gdesc);
    }
  }


  return OK;
}

char* space_get_gdesc(Space* space,int line){
  if(!space||line<0) return NULL;

  return space->gdesc[line];

}

STATUS space_set_gdesc(Space* space, char* string, int line){
  if(!space||!string||line<0) return ERROR;

  if(strlen(string)==8){
    strcpy(space->gdesc[line],string);
    return OK;
  }
  
  return ERROR;
}
