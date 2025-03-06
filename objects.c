/**
 * 
 * @brief 
 *
 * @file objects.c
 * @author Andres Falcon
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "objects.h"
#include "types.h"

struct _Object {
   Id id;                            /*!< Id number of the object, it must be unique */
   char name[WORD_SIZE + 1];         /*!< Name of the object */
   char description[WORD_SIZE + 1];  /*!< Description of the object */
   Id location;                      /*!< Id number of the space the object resides in */
   Bool relocatable;                 /*!< Whether the object can be moved or not */
};

Object* object_create(Id id){
   
   Object *newObject = NULL;

   newObject = (Object*)malloc(sizeof(Object));
   if (newObject== NULL) {
      return NULL;
   }

   /* Initialization of an empty space*/
   newObject->id = id;
   newObject->location = NO_ID;
   newObject->name[0] = '\0';
   newObject->description[0] = '\0';

   newObject->relocatable = TRUE; 
   return newObject;

}

Status object_destroy(Object* object) {
  if (!object) {
    printf("Error: object is NULL in object_destroy\n");
    return ERROR;
  }

  free(object);
  object = NULL;
  return OK;
}

Id object_get_id(Object* object) {
  if (!object) {
    printf("Error: object is NULL in object_get_id\n");
    return NO_ID;
  }
  return object->id;
}

Id object_get_location(Object* object) {
  if (!object) {
    printf("Error: object is NULL in object_get_location\n");
    return NO_ID;
  }
  return object->location;
}

Id *object_get_location_pointer(Object* object) {
  if (!object) {
    printf("Error: object is NULL in object_get_location_pointer\n");
    return NULL;
  }
  return &(object->location);
}

Status object_set_name(Object* object, char* name) {
  if ((object) == NULL || !name) {
    printf("Error: invalid parameters in object_set_name\n");
    return ERROR;
  }

  if (!strcpy(object->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* object_get_name(Object* object) {
  if (object == NULL) {
    printf("Error: object is NULL in object_get_name\n");
    return NULL;
  }
  return object->name;
}

Status object_set_description(Object* object, char* description) {
  if ((object) == NULL || !description) {
    printf("Error: invalid parameters in object_set_description\n");
    return ERROR;
  }

  if (!strcpy(object->description, description)) {
    return ERROR;
  }
  return OK;
}

Status object_set_location(Object* object, Id location) {
  if (object == NULL || location == NO_ID) {
    printf("Error: invalid parameters in object_set_location\n");
    return ERROR;
  }

  object->location = location;
  return OK;
}


