/**
 * @file  vertex.h
 * 
 * @author Profesores Programación 2
 * @author Izan Robles
 * @author Arturo Pérez
 * 
 * @date 20 feb 2025
 * @version 1.5
 * @brief Library to manage ADT Vertex
 *
 * @details 
 * 
 * @see
 */


#ifndef VERTEX_H_
#define VERTEX_H_

#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define TAG_LENGTH 64
#define MAX_DATA 128


/** 
 * @brief Label to characterize the vertex state (to be used in P2)
 **/
typedef enum {
    WHITE, /* vertex not visited */
    BLACK,  /* vertex visited */
    ERROR_VERTEX   /* not valid vertex */   
} Label;

/** 
 * @brief Data structure to implement the ADT Vertex. To be defined 
 * in vertex.c
 *
 **/
/* START [Vertex] */
typedef struct _Vertex Vertex;
/* END [Vertex] */

struct _Vertex 
{
    long id;
    char tag[TAG_LENGTH];
    Label state;
}; 

/**
 * @brief Constructor. Initialize a vertex.
 * 
 * @author Izan Robles
 * @author Arturo Pérez
 * 
 * This function allocates memory for a vertex and sets its fields to 
 * id to 0, tag to "" and state to WHITE.
 *
 * @code
 * // Example of use
 * Vertex * v;
 * v = vertex_init();
 * @endcode
 *
 * @return Return the initialized vertex if it was done correctly, 
 * otherwise return NULL.
*/
Vertex * vertex_init ();

/**
 * @brief Constructor. Initialize a vertex from its description.
 * 
 * @author Profresores Programación 2
 * 
 * This function allocates memory for a vertex and sets its fields  
 * according to the description provided. A description string is 
 * a set of key:value pairs separated by any amount of whitespace, 
 * where the key can be any of id, tag or state. 
 * No space is allowed in the definition of a key:value pair.
 * The key:value pairs can be provided in any order.
 * 
 * Examples
 *
 * vertex_initFromString("id:1 tag:Toledo state:1");
 * vertex_initFromString("tag:Toledo state:1 id:1");
 * vertex_initFromString("tag:Toledo state:1");
 * vertex_initFromString("id:1 state:1");
 *
 * @param descr String describing the vertex.
 *
 * @return Return the initialized vertex if it was done correctly, 
 * otherwise return NULL.
*/
Vertex *vertex_initFromString(char *descr);

/**
 * @brief Frees all memory associated to given vertex
 *
 * @author Izan Robles
 * @author Arturo Pérez
 * 
 * @param v vertex to free
 */
void vertex_free (void * v);

/**
 * @brief Extracts id from given vertex
 *
 * @author Izan Robles
 * @author Arturo Pérez
 * 
 * @param v vertex pointer
 *
 * @return Returns long with the ID of the given vertex
 */
long vertex_getId (const Vertex * v);

/**
 * @brief Extracts tag from given vertex
 *
 * @author Izan Robles
 * @author Arturo Pérez
 * 
 * @param v vertex pointer
 *
 * @return Returns pointer to string with pointers tag
 */
const char* vertex_getTag (const Vertex * v);

/**
 * @brief Extracts state from given vertex
 *
 * @author Izan Robles
 * @author Arturo Pérez
 * 
 * @param v vertex pointer
 *
 * @return Returns label with the state of the given vertex
 */
Label vertex_getState (const Vertex * v);



/**
 * @brief Modifies the id of a given vertex.
 * 
 * @author Izan Robles
 * @author Arturo Pérez
 *
 * @param v Vertex pointer
 * @param id New vertex id, must be equal or greater than 0
 *
 * @return Returns OK or ERROR in case of error 
 */
Status vertex_setId (Vertex * v, const long id);


/**
 * @brief Modifies the tag of a given vertex
 * 
 * @author Izan Robles
 * @author Arturo Pérez
 *
 * @param v Vertex pointer
 * @param id New vertex tag, must fit in the Vertex
 *
 * @return  Returns OK or ERROR in case of error.
 */
Status vertex_setTag (Vertex * v, const char * tag);


/**
 * @brief Modifies the state of a given vertex
 *
 * @author Izan Robles
 * @author Arturo Pérez
 * 
 * @param v Vertex pointer
 * @param state New vertex state
 *
 * @return Returns OK or ERROR in case of error.
 */
Status vertex_setState (Vertex * v, const Label state);


/**
 * @brief Compares two vertices.
 *
 * @author Izan Robles
 * @author Arturo Pérez
 * 
 * First it compares their ids. If they are equal, then compares
 * their tags.
 * 
 * @param v1 
 * @param v2 Vertices to compare.
 *
 * @return 0 if both tags and ids are equal, if v1 > v2, returns 1, if v2 > v1, 
 * returns -1, if v1 = v2, compares tags, and returns int 1 or -1, respectively, 
 * if v1 tag > v2 tag and viceversa. Returns -2 if an error is found.
 */
int vertex_cmp (const void * v1, const void * v2);


/**
 * @brief Reserves memory for a vertex where it copies the data from
 * the vertex src.
 * 
 * @author Izan Robles
 * @author Arturo Pérez
 * 
 * @code
 * // Example of use
 * Vertex *trg, *src;
 * src = vertex_init();
 * trg = vertex_copy(src);
 * // .... aditional code ...
 * // free vertexs
 * vertex_free(src);
 * vertex_free(trg);
 * @endcode
 * 
 * @param src Original vertex pointer
 *
 * @return Returns the pointer of the copied vertex if everything 
 * went well, or NULL otherwise.
 */
void * vertex_copy (const void * src);



/** 
 * @brief Prints in pf the data of a vertex.
 * 
 * @author Izan Robles
 * @author Arturo Pérez
 * 
 * The format will be: [id, tag, state], without line break at the 
 * end. The type Label is an enumeration so it can be printed as an
 * int. 
 *
 * @code
 * Vertex * v;
 * v = vertex_init();
 * vertex_print (stdout, v);
 * @endcode
 * 
 * @param pf File descriptor
 * @param v Vertex to be printed
 *
 * @return Returns the number of characters that have been written 
 * successfully. If there have been errors returns -1.
 */
int vertex_print (FILE * pf, const void * v);

/**
 * @brief Verifies if all the fields of a vertex are valid.
 * 
 * @author Izan Robles
 * @author Arturo Pérez
 *
 * @param v Vertex pointer
 *
 * @return  Returns TRUE if the vertex is invalid, FALSE otherwise
 */
Bool is_invalid_vertex(const Vertex *v);


#endif /* VERTEX_H_ */
