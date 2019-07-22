/* 
 * This file is part of the Navi Singh's experiments 
 * (https://github.com/xxxx or http://xxx.github.io).
 *
 * Copyright (c) 2019 Navjot Singh.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Navjot Singh
 * Email: navisinghnz9@gmail.com
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct cstring {
    char * chars;
    int (* length)();
} CString;

int length(CString *self) {
    return strlen(self->chars);
}

CString* initCString(char *chars){
  CString *cstr = malloc(sizeof(CString));
  cstr->chars = chars;
  cstr->length = &length;
  return cstr;
}

int main() {
  CString *cstr = initCString("Test");
  printf("Len: %d\n", cstr->length(cstr));
  free(cstr);

  return 0;
}
