#include "file_utils.h"

/* ------------------------------------------------------------- */

int _float_print(FILE *pf, const void *a)
{
    if (!pf || !a)
        return -1;
    return fprintf(pf, "%.2f", *(float *)a);
}