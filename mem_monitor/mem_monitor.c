#include <stdio.h>
#include <stdlib.h>

#include "mem_monitor.h"


void* malloc_monitor(size_t size, const char *file, int line, const char *func) {

    printf ("malloc_monitor \n");

    int x = 0;

    void *ptr = malloc(size);

    printf ("Allocated = %s, %i, %s, %p[%li]\n", file, line, func, ptr, size);

    // ToDo - Add the mem allocation info to linked list

    return ptr;
}
