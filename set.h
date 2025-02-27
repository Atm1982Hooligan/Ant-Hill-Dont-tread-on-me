/**
 * @brief It implements the set module
 *
 * @file set.h
 * @author Izan Robles
 * @author Alejandro González
 * @version 1.0
 * @date 27-02-2025
 */

#ifndef SET_H
#define SET_H

#include "types.h"

#define MAX_IDS 100

typedef struct _Set Set;

/**
 * @brief Creates a new set, allocating memory and initializing its members.
 * @author Alejandro González
 * 
 * @return A pointer to the new set, or NULL if an error occurs.
 */
Set* set_create();

/**
 * @brief Destroys a set, freeing the allocated memory.
 * @author Alejandro González
 * 
 * @param set A pointer to the set to be destroyed.
 * @return OK if the set was destroyed successfully, ERROR otherwise.
 */
Status set_destroy(Set* set);

/**
 * @brief Adds an identifier to the set.
 * @author Alejandro González
 * 
 * @param set A pointer to the set.
 * @param id The identifier to add.
 * @return OK if the identifier was added successfully, ERROR otherwise.
 */
Status set_add(Set* set, Id id);

/**
 * @brief Removes an identifier from the set.
 * @author Alejandro González
 * 
 * @param set A pointer to the set.
 * @param id The identifier to remove.
 * @return OK if the identifier was removed successfully, ERROR otherwise.
 */
Status set_del(Set* set, Id id);

/**
 * @brief Prints the contents of the set for debugging purposes.
 * @author Alejandro González
 * 
 * @param set A pointer to the set.
 * @return OK if the set was printed successfully, ERROR otherwise.
 */
Status set_print(Set* set);

#endif