#include <stdio.h>
#include <time.h>

#include "count.h"

#define N_NUMBERS 10
#define MAX_NUMBER 99

/* Output for a correct implementation (these tests are not exhaustive):

$ ./test_count 0
28 43 72 79 23 70 55 39 69 1
Count of even numbers: 3

$ ./test_count 123
13 23 80 75 21 79 1 63 23 33
Count of even numbers: 1
*/

int int_print(FILE *f, const void *e) { return fprintf(f, "%d ", *((int *)e)); }

Boolean is_even(void *e) {
  if (*((int *)e) % 2 == 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

int main(int argc, char *argv[]) {
  int i = 0;
  int numbers[N_NUMBERS], seed = 0;
  Stack *stack = NULL;

  if (argc > 1) {
    seed = atoi(argv[1]);
  } else {
    seed = time(NULL);
  }

  srand(seed);

  stack = stack_new();
  if (stack == NULL) {
    return EXIT_FAILURE;
  }

  for (i = 0; i < N_NUMBERS; i++) {
    numbers[i] = rand() % MAX_NUMBER;
    if (stack_push(stack, numbers + i) == ERROR) {
      stack_free(stack);
      return EXIT_FAILURE;
    }
  }

  stack_print(stdout, stack, int_print);
  printf("\nCount of even numbers: %d\n", stack_count_if(stack, is_even));

  stack_free(stack);
  return EXIT_SUCCESS;
}