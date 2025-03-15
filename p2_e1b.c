/*
 * File: p2_e1b.c
 * Author: Izan Robles
 */

#include "utils.h"
#include "file_utils.h"
#include "vertex.h"


int main(int argc, char *argv[])
{
    /* -------------------------------------------- Error control and varaible creation -------------------------------------------- */
    
    P_stack_ele_print print_func = vertex_print;
    int error_manager = -1;
    Stack *sin1 = NULL;
    Stack *sin2 = NULL;
    Stack *sout = NULL;
    FILE *file = NULL;
   
    if (argc != 3)
    {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    /* -------------------------------------------- Read data and add to stacks -------------------------------------------- */

    if (!(file = fopen(argv[1], "r")))
    {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }

    if (!(sin1 = stack_of_vertex_from_file(file)))
    {
        printf("Error reading file %s\n", argv[1]);
        fclose(file);
        return 1;
    }

    fclose(file);

    if (!(file = fopen(argv[2], "r")))
    {
        printf("Error opening file %s\n", argv[2]);
        stack_free_with_elements(sin1);
        return 1;
    }

    if (!(sin2 = stack_of_vertex_from_file(file)))
    {
        printf("Error reading file %s\n", argv[2]);
        fclose(file);
        stack_free_with_elements(sin1);
        return 1;
    }

    fclose(file);
    
    /* -------------------------------------------- Print and merge stacks -------------------------------------------- */

    printf("Ranking 0:\n");
    if ((error_manager = stack_print(stdout, sin1, print_func)) < 0)
    {
        printf("Could not print first ranking\n");
        stack_free_with_elements(sin1);
        stack_free_with_elements(sin2);
        return 1;
    }
    
    printf("\nRanking 1:\n");
    if ((error_manager = stack_print(stdout, sin2, print_func)) < 0)
    {
        printf("Could not print second ranking\n");
        stack_free_with_elements(sin1);
        stack_free_with_elements(sin2);
        return 1;
    }

    sout = stack_init();
    if (!sout)
    {
        printf("Could not create output stack\n");
        stack_free_with_elements(sin1);
        stack_free_with_elements(sin2);
        return 1;
    }

    if (mergeStacks(sin1, sin2, sout, vertex_cmp) == ERROR)
    {
        printf("Could not merge stacks\n");
        stack_free_with_elements(sin1);
        stack_free_with_elements(sin2);
        stack_free_with_elements(sout);
        return 1;
    }

    printf("\nJoint Ranking:\n");
    if ((error_manager = stack_print(stdout, sout, print_func)) < 0)
    {
        printf("Could not print joint ranking\n");
        stack_free_with_elements(sin1);
        stack_free_with_elements(sin2);
        stack_free_with_elements(sout);
        return 1;
    }

    stack_free_with_elements(sin1);
    stack_free_with_elements(sin2);
    stack_free_with_elements(sout);

    return 0;
}