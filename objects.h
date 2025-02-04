/**
 * 
 * 
 * 
 * 
 */

#ifndef OBJECTS_H
#define OBJECTS_H

#include "types.h"

typedef struct _Object Object;

#define MAX_SPACES 100

/*Requisitos:

    - Campo de identificación (id)
    - Nombre del objeto (name)
    - Crear objetos (create)
    - Destruir objetos (destroy)
    - Leer y cambiar los valores de sus campos (get y set)
    - Imprimir (print) el contenido de los mismos  

---------------------------------------------------*/


Object* object_create(Id id);

Status object_destroy(Object* object);

Id object_get_id(Object* object);

Status object_set_name(Object* object, char* name);

const char* object_get_name(Object* object);

Status object_print(Object* object);

//Faltan cambiar los alores de campos.



//printf("");








#endif
