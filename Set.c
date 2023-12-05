#include "Set.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Hashmap.h"
#include <string.h>

int Set_hash(char* key)
{
    int hash =0;
    for (int i=0; i<strlen(key); i++)
    {
        hash += key[i];
    }

    return (hash % HASHMAP_CAPACITY);
}

bool Set_Add(Set** set, char* key)
{
    char* value = key;
    int index = Set_hash(key);
    Set *newElem = malloc(sizeof(Set));
    newElem->key = key;
    newElem->value = value;
    newElem->overflow_bucket = NULL;

    if (set[index]==NULL)
        {
            set[index] = newElem;
        }
    else
    {
        Set* tmp = set[index];
        while (tmp)
        {
            if (strcmp(tmp->key, key) == 0)
            {
                return false;
            }
            tmp = tmp->overflow_bucket;
        }
        {
            newElem->overflow_bucket = set[index];
            set[index] = newElem;
        }
    }
}

char* Set_getValue(Set** set, char* key)
{
    char*value = key;
    int index = Set_hash(key);
    Set* elem = set[index];
    
    
    while (elem!=NULL)
    {
        if (strcmp(elem->key,key)==0)
            return elem->value;
        elem = elem->overflow_bucket;
    }
    return NULL;
}

void Set_Delete(Set** set, char* key)
{
    char* value = key;
    int index = Set_hash(key);
    Set* currEl = set[index];
    Set* prevEl = NULL;
    while (currEl!=NULL)
    {
        if (strcmp(currEl->key,key)==0)
        {
            if (prevEl != NULL)
            {
                prevEl->overflow_bucket = currEl->overflow_bucket;
            }
            else
            {
                set[index] = currEl -> overflow_bucket;
            }
            free(currEl);
            printf("Значение удалено.\n");
            return;
        }
        prevEl= currEl;
        currEl = currEl->overflow_bucket;
    }
    printf("Значение не найдено.\n");
    return;

}

bool setIsMember(Set** set, char *elem)
{
    char* result = Set_getValue(set, elem);
    if (result == NULL)
        return false;

    return true;
}
