/**
 * @file count.c
 * @brief Implementation of stack count utilities.
 *
 */
#include "count.h"

#include "stack.h"
#include "types.h"

/* ALL THE CODE must between written between the <START_CODE> and <END_CODE>
tags. Auxiliary functions can also be defined between those lines.
*/

#define COUNT_ERROR -1

/*<START_CODE>*/

int stack_count_if(Stack *stack, Boolean (*ele_check)(void *)) {
    if (stack == NULL || ele_check == NULL) {
        return -1;
    }
    int count = 0, i, n_elements = stack_size(stack);

    if (n_elements == -1) {
      return -1;
    }

    Stack *stack_aux = stack_new();
    if (stack_aux == NULL) {
        return -1;
    }

    

    for (i = 0; i < n_elements; i++) {
      void *ele = stack_top(stack);
        if (ele == NULL) {
            stack_free(stack_aux);
            return -1;
        }

        if(stack_push(stack_aux, ele) == ERROR){
          free(stack_aux);
          return -1;
        }

        if (ele_check(ele) == TRUE) {
            count++;
        }

        if(stack_pop(stack) == NULL){
          free(stack_aux);
          return -1;
        }
    }

    for (i = 0; i < n_elements; i++) {
        void *ele = stack_top(stack_aux);
        if (ele == NULL) {
            stack_free(stack_aux);
            return -1;
        }

        if (stack_push(stack, ele) == ERROR){
            free(stack_aux);
            return -1;
        }

        if (stack_pop(stack_aux) == NULL ){
            free(stack_aux);
            return -1;
        }
    }

    stack_free(stack_aux);
    return count;
}

/*<END_CODE>*/