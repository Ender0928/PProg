/** 
 * @brief It implements the link module
 * 
 * @file link.c
 * @author Profesores PPROG
 * @version 2.0 
 * @date 29-11-2021 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"

/**
 * @brief Link
 *
 * This struct stores all the information of a link.
 */
struct _Link {
  Id id;                        /*!< Id number of the link, it must be unique */
  char name[WORD_SIZE + 1];     /*!< Name of the link */
  Id origin;                    /*!< Id of the origin space of the link*/
  Id destination;               /*!< Id of the destination space of the link */
  DIRECTION direction;          /*!< Direction of the link */
  STATUS st;                    /*!< Status of the link(OK if it is open, else close) */
};

/** link_create allocates memory for a new link
  *  and initializes its members
  */
Link* link_create(Id id){
  Link *newLink = NULL;

  /* Error control */
  if (id == NO_ID)
    return NULL;

  newLink = (Link *) malloc(sizeof (Link));
  if (newLink == NULL) {
    return NULL;
  }

  /* Initialization of an empty link*/
  newLink->id = id;
  newLink->name[0] = '\0';
  newLink->origin = NO_ID;
  newLink->destination = NO_ID;
  newLink->direction = NO_DIRECTION; 
  newLink->st = ERROR;
  

  return newLink;
}

/** link_destroy frees the previous memory allocation 
  *  for a link
  */
STATUS link_destroy(Link* link) {
  if (!link) {
    return ERROR;
  }

  free(link);
  link = NULL;
  return OK;
}

/** It gets the id of a link
  */
Id link_get_id(Link* link) {
  if (!link){
    return NO_ID;
  }
  return link->id;
}

/** It sets the name of a link
  */
STATUS link_set_name(Link* link, char* name) {
  if (!link || !name) {
    return ERROR;
  }

  if (!strcpy(link->name, name)) {
    return ERROR;
  }
  return OK;
}
/** It gets the name of a link
  */
const char *link_get_name(Link* link) {
  if (!link){
    return NULL;
  }
  return link->name;
}

/** It sets the id of the origin of the link
  */
STATUS link_set_origin(Link* link, Id id) {
  if (!link || id == NO_ID){
    return ERROR;
  }
  link->origin = id;
  return OK;
}
/** It gets the id of the origin of the link
  */
Id link_get_origin(Link* link){
  if (!link) {
    return NO_ID;
  }
  return link->origin;
}

/** It sets the id of the destination of the link
  */
STATUS link_set_destination(Link* link, Id id) {
  if (!link || id == NO_ID) {
    return ERROR;
  }
  link->destination = id;
  return OK;
}
/** It gets the id of the destination of the link
  */
Id link_get_destination(Link* link) {
  if (!link) {
    return NO_ID;
  }
  return link->destination;
}

/** It sets the direction of the link
  */
STATUS link_set_direction(Link* link, DIRECTION direction) {
  if (!link || direction == NO_DIRECTION) {
    return ERROR;
  }
  link->direction = direction;
  return OK;
}
/** It gets the id of the link located at the east
  */
DIRECTION link_get_direction(Link* link) {
  if (!link) {
    return NO_ID;
  }
  return link->direction;
}

/** It sets the status of the link 
  */
STATUS link_set_status(Link* link, STATUS st) {
  if (!link) {
    return ERROR;
  }
  link->st = st;
  return OK;
}
/** It gets the status of the link
  */
STATUS link_get_status(Link* link){
  if (!link) {
    return ERROR;
  }
  return link->st;
}
/** It prints the link information
  */
STATUS link_print(Link* link){
  /* Error Control */
  if (!link) {
    return ERROR;
  }

  fprintf(stdout, "--> Link (Id: %ld; Name: %s; Origin: %ld; Destination: %ld; Direction: %d; Status: %d)\n", link->id, link->name, link->origin, link->destination, link->direction, link->st);
  
  return OK;
}


