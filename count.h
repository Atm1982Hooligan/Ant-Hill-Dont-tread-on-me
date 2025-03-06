/**
 * @file count.h
 * @brief Interface for stack count utilities.
 *
 */
#ifndef COUNT_H
#define	COUNT_H

#include "stack.h"
#include "types.h"

/**
 * @brief Count the number of elements in the stack satisfying a condition.
 *
 * @param stack Stack.
 * @param ele_check Function to check if the condition is satisfied.
 * @return int, the number of elements satisfying the condition or -1 if error.
 */
int stack_count_if(Stack *stack, Boolean (*ele_check)(void *));

#endif