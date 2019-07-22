#include <stdio.h>
#include <stdlib.h>

#include "mem_monitor.h"


/*
 * preventing preprocessor on malloc call in this file to call malloc_monitor
 * leading to an infinite recursion
 */
#define malloc malloc


void* malloc_monitor(size_t size, const char *file, int line, const char *func) {

    void *ptr = malloc(size);
    printf ("Allocated = %s, %i, %s, %p[%li]\n", file, line, func, ptr, size);

    // FIXME - Add the mem allocation info to linked list

    return ptr;
}
