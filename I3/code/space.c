/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 27-02-2025
 * @copyright GNU Public License
 */

#include "space.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  Set* objects;             /*!< Objects in the space */
  char gdesc[GDESC_ROWS][GDESC_COLS]; /*!< Grafical description>*/
};

Space* space_create(Id id) {
  Space* newSpace = NULL;
  int i;

  if (id == NO_ID) return NULL;

  newSpace = (Space*)malloc(sizeof(Space));
  if (newSpace == NULL) {
    return NULL;
  }

  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->objects = set_create();
  
  for (i=0; i < GDESC_ROWS; i++) {
    newSpace->gdesc[i][0] = '\0';
  }
  return newSpace;
}

Status space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

  set_destroy(space->objects);
  free(space);
  return OK;
}

Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

Status space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

Status space_set_north(Space* space, Id id) {
  if (!space) {
    return ERROR;
  }
  space->north = id;
  return OK;
}

Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}

Status space_set_south(Space* space, Id id) {
  if (!space) {
    return ERROR;
  }
  space->south = id;
  return OK;
}

Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}

Status space_set_east(Space* space, Id id) {
  if (!space) {
    return ERROR;
  }
  space->east = id;
  return OK;
}

Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}

Status space_set_west(Space* space, Id id) {
  if (!space) {
    return ERROR;
  }
  space->west = id;
  return OK;
}

Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}

Status space_add_object(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  return set_add_object(space->objects, id);
}

Status space_remove_object(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  return set_remove_object(space->objects, id);
}

Bool space_has_object(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return FALSE;
  }
  return set_find_object(space->objects, id);
}


Id* space_get_objects(Space* space) {
  if (!space) {
    return NULL;
  }
  return set_get_ids(space->objects);
}

int space_get_num_objects(Space* space) {
  if (!space) {
    return -1;
  }

  return set_size(space->objects);
}
char (*space_get_gdesc(Space *space))[GDESC_COLS] {
  if (!space) {
    return NULL;
  }

  return space->gdesc;
}

Status space_set_gdesc(Space* space, char gdesc[GDESC_ROWS][GDESC_COLS]) {
  int i;
  if (!space || !gdesc) {
    return ERROR;
  }
  for (i = 0; i < GDESC_ROWS; i++) {
    strncpy(space->gdesc[i], gdesc[i], GDESC_COLS);
    space->gdesc[i][GDESC_COLS - 1] = '\0';
  }
  return OK;
}

Status space_print(Space* space) {
  int i;

  if (!space) {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);
  fprintf(stdout, "---> North: %ld\n", space->north);
  fprintf(stdout, "---> South: %ld\n", space->south);
  fprintf(stdout, "---> East: %ld\n", space->east);
  fprintf(stdout, "---> West: %ld\n", space->west);

  fprintf(stdout, "---> Graphical description:\n");
  for (i = 0; i < GDESC_ROWS; i++) {
    fprintf(stdout, "%s\n", space->gdesc[i]);
  }

  fprintf(stdout, "---> Objects in space:\n");
  set_print(space->objects);

  return OK;
}
