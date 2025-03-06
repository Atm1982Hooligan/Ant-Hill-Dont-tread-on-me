/**
 * @file stack.h
 * @author Programming II Teaching Team
 * @date 10 Feb 2023
 * @brief Public interface for Stack implementation.
 *
 * The Stack admits arbitrary elements, received as pointers to void.
 *
 */

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

/**
 * Stack type definition: a stack of arbitrary elements.
 */
/*<STACK>*/
typedef struct _Stack Stack;
/*</STACK>*/

/**
 * p_stack_ele_print type definition: pointer to a function that prints a
 * Stack element to an output stream. It is assumed that this function returns:
 * (1) the number of characters printed upon success; or
 * (2) a negative number in case of error.
 */
typedef int (*p_stack_ele_print)(FILE *, const void *);

/**
 * @brief Public function that creates a new Stack.
 *
 * Allocates memory for the new Stack.
 *
 * @return Returns the address of the new stack, or NULL in case of error.
 */
/*<NEW>*/
Stack *stack_new();
/*</NEW>*/

/**
 * @brief Public function that checks if a Stack is empty.
 *
 * Note that the return value is TRUE for a NULL Stack.
 *
 * @param ps Pointer to the Stack.
 *
 * @return Boolean value TRUE if the list is empty or NULL, Boolean value FALSE
 * otherwise.
 */
/*<ISEMPTY>*/
Boolean stack_is_empty(const Stack *ps);
/*</ISEMPTY>*/

/**
 * @brief Public function that pushes an element into a Stack.
 *
 * Inserts the element received as argument.
 *
 * @param ps Pointer to the Stack.
 * @param e Element to be inserted into the Stack.
 *
 * @return Status value OK if the insertion could be done, Status value ERROR
 * otherwise.
 */
/*<PUSH>*/
Status stack_push(Stack *ps, const void *e);
/*</PUSH>*/

/**
 * @brief Public function that pops the top element from a Stack.
 *
 * Extracts the first element from the Stack, returning it.
 *
 * @param ps Pointer to the Stack.
 *
 * @return Extracted element, NULL if the Stack is empty or NULL.
 */
/*<POP>*/
void *stack_pop(Stack *ps);
/*</POP>*/

/**
 * @brief Public function that returns the top element from a Stack.
 *
 * Extracts the top element from the Stack, returning it.
 *
 * @param ps Pointer to the Stack.
 *
 * @return Extracted element, NULL if the Stack is empty or NULL.
 */
/*<TOP>*/
void *stack_top(const Stack *ps);
/*</TOP>*/

/**
 * @brief Public function that frees a Stack.
 *
 * Frees the memory allocated for the Stack.
 *
 * @param ps Pointer to the Stack.
 */
/*<FREE>*/
void stack_free(Stack *ps);
/*</FREE>*/

/**
 * @brief Public function that returns the number of elements in a Stack.
 *
 * @param ps Pointer to the Stack.
 *
 * @return Returns the number of elements in the Stack, or -1 if the Stack is NULL.
 */
/*<SIZE>*/
int stack_size(const Stack *ps);
/*</SIZE>*/

/**
 * @brief Public function that prints the contenf of a Stack.
 *
 * Prints all the elements in the Stack to an output stream.
 *
 * Note that this function simply calls the P_ele_print function for each Stack
 * element, without printing any additional information. Any desired format must
 * be included in the P_ele_print function.
 *
 * @param fp Output stream.
 * @param ps Pointer to the Stack.
 * @param f Pointer to the print function.
 *
 * @return The sum of the return values of all the calls to f if these values are
 * all positive; the first negative value encountered otherwise. If the function
 * f is well constructed, this means that, upon successful return, this function
 * returns the number of characters printed, and a negative value if an error
 * occurs.
 */
/*<PRINT>*/
int stack_print(FILE *fp, const Stack *ps, int (*ele_print)(FILE *, const void *));
/*</PRINT>*/

/* Inefficient versions. */
Status stack_push_inefficient(Stack *ps, const void *e);

#endif /* STACK_H */
