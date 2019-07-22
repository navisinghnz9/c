#ifndef __MEM_MONITOR__
#define __MEM_MONITOR__

#include <sys/types.h>

#define malloc(X) malloc_monitor( X, __FILE__, __LINE__, __FUNCTION__)

void* malloc_monitor(size_t size, const char *file, int line, const char *func);

#endif
