/**
 * @brief It manages the set 
 *
 * @file set.c
 * @author Alejandro Gonzalez
 * @version 1
 * @date 27-02-2025
 */

#include "set.h"

#include <stdio.h>
#include <stdlib.h>

struct _Set {
    Id ids[MAX_IDS];
    int n_ids;
};

Set* set_create() {
    Set* new_set = (Set*)malloc(sizeof(Set));
    if (!new_set) {
        return NULL;
    }
    new_set->n_ids = 0;
    return new_set;
}

Status set_destroy(Set* set) {
    if (!set) {
        printf("Error: set is NULL in set_destroy\n");
        return ERROR;
    }
    free(set);
    return OK;
}

Status set_add(Set* set, Id id) {
    int i;
    
    if (!set || id == NO_ID || set->n_ids >= MAX_IDS) {
        printf("Error: invalid parameters in set_add\n");
        return ERROR;
    }
    for (i = 0; i < set->n_ids; i++) {
        if (set->ids[i] == id) {
            printf("Error: id already exists in set_add\n");
            return ERROR;
        }
    }
    set->ids[set->n_ids++] = id;
    return OK;
}

Status set_del(Set* set, Id id) {
    int i;

    if (!set || id == NO_ID) {
        printf("Error: invalid parameters in set_del\n");
        return ERROR;
    }
    for (i = 0; i < set->n_ids; i++) {
        if (set->ids[i] == id) {
            set->ids[i] = set->ids[--set->n_ids];
            return OK;
        }
    }
    printf("Error: id not found in set_del\n");
    return ERROR;
}

Status set_print(Set* set) {
    int i;

    if (!set) {
        printf("Error: set is NULL in set_print\n");
        return ERROR;
    }
    printf("Set contains %d ids:\n", set->n_ids);
    for (i = 0; i < set->n_ids; i++) {
        printf("%ld ", set->ids[i]);
    }
    printf("\n");
    return OK;
}

int set_get_count(Set* set) {
    if (!set) {
        printf("Error: set is NULL in set_get_count\n");
        return -1;
    }
    return set->n_ids;
}

Id set_get_id_at(Set* set, int index) {
    if (!set || index < 0 || index >= set->n_ids) {
        printf("Error: invalid parameters in set_get_id_at\n");
        return NO_ID;
    }
    return set->ids[index];
}




