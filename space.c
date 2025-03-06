/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "space.h"
#include "objects.h"
#include "set.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  Set *objects;             /*!< Set of objects in the space */
};

Space* space_create(Id id) {
  Space* newSpace = NULL;
  
  /* Error control */
  if (id == NO_ID) return NULL;

  newSpace = (Space*)malloc(sizeof(Space));
  if (newSpace == NULL) {
    return NULL;
  }

  /* Initialization of an empty space */
  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;

  newSpace->objects = set_create();
  if (newSpace->objects == NULL) {
    free(newSpace);
    return NULL;
  }

  return newSpace;
}

Status space_destroy(Space* space) {
  if (!space) {
    printf("Error: space is NULL in space_destroy\n");
    return ERROR;
  }

  if (space->objects != NULL) {
    set_destroy(space->objects);
  }

  free(space);
  space = NULL;
  return OK;
}

Id space_get_id(Space* space) {
  if (!space) {
    printf("Error: space is NULL in space_get_id\n");
    return NO_ID;
  }
  return space->id;
}

Status space_set_name(Space* space, char* name) {
  if (!space || !name) {
    printf("Error: invalid parameters in space_set_name\n");
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* space_get_name(Space* space) {
  if (!space) {
    printf("Error: space is NULL in space_get_name\n");
    return NULL;
  }
  return space->name;
}

Status space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    printf("Error: invalid parameters in space_set_north\n");
    return ERROR;
  }
  space->north = id;
  return OK;
}

Id space_get_north(Space* space) {
  if (!space) {
    printf("Error: space is NULL in space_get_north\n");
    return NO_ID;
  }
  return space->north;
}

Status space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    printf("Error: invalid parameters in space_set_south\n");
    return ERROR;
  }
  space->south = id;
  return OK;
}

Id space_get_south(Space* space) {
  if (!space) {
    printf("Error: space is NULL in space_get_south\n");
    return NO_ID;
  }
  return space->south;
}

Status space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    printf("Error: invalid parameters in space_set_east\n");
    return ERROR;
  }
  space->east = id;
  return OK;
}

Id space_get_east(Space* space) {
  if (!space) {
    printf("Error: space is NULL in space_get_east\n");
    return NO_ID;
  }
  return space->east;
}

Status space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    printf("Error: invalid parameters in space_set_west\n");
    return ERROR;
  }
  space->west = id;
  return OK;
}

Id space_get_west(Space* space) {
  if (!space) {
    printf("Error: space is NULL in space_get_west\n");
    return NO_ID;
  }
  return space->west;
}

Status space_add_object(Space* space, Id id) {
  if (!space || id == NO_ID) {
    printf("Error: invalid parameters in space_add_object\n");
    return ERROR;
  }
  return set_add(space->objects, id);
}

Status space_remove_object(Space* space, Id id) {
  if (!space || id == NO_ID) {
    printf("Error: invalid parameters in space_remove_object\n");
    return ERROR;
  }
  return set_del(space->objects, id);
}

Bool space_has_object(Space* space, Id id) {
  if (!space || id == NO_ID) {
    printf("Error: invalid parameters in space_has_object\n");
    return FALSE;
  }
  return set_get_id_at(space->objects, id) != NO_ID;
}

Status space_print(Space* space) {
  Id idaux = NO_ID;
  int i, n_ids;

  /* Error Control */
  if (!space) {
    return ERROR;
  }

  /* 1. Print the id and the name of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  /* 2. For each direction, print its link */
  idaux = space_get_north(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }
  idaux = space_get_south(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }
  idaux = space_get_east(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }
  idaux = space_get_west(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  /* 3. Print if there are objects in the space or not */
  n_ids = set_get_count(space->objects);
  if (n_ids > 0) {
    fprintf(stdout, "---> Objects in the space:\n");
    for (i = 0; i < n_ids; i++) {
      fprintf(stdout, "------> Object Id: %ld\n", set_get_id_at(space->objects, i));
    }
  } else {
    fprintf(stdout, "---> No objects in the space.\n");
  }

  return OK;
}
