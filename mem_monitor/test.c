#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mem_monitor.h"


typedef struct cstring {
    char * chars;
} CString;


int main() {
  CString *cstr = malloc(sizeof(CString));
  cstr->chars = "hello";

  printf("Len: %d\n", (int)strlen(cstr->chars) );

  free(cstr);

  return 0;
}
