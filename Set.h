#ifndef SET_H
#define SET_H
#include <stdbool.h>
#include "Hashmap.h"
typedef HashmapElem Set;


int Set_hash(char* key);
bool Set_Add(Set** set, char* key);
char* Set_getValue(Set** set, char* key);
void Set_Delete(Set** set, char* key);
bool setIsMember(Set** set, char *elem);
#endif