#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Hashmap.h"
#include <string.h>

int Hashmap_hash(char* key)
{
    int hash =0;
    for (int i=0; i<strlen(key); i++)
    {
        hash += key[i];
    }

    return (hash % HASHMAP_CAPACITY);
}

void Hashmap_add(HashmapElem** map, char* key, char* value)
{
    int index = Hashmap_hash(key);
    HashmapElem *newElem = malloc(sizeof(HashmapElem));
    newElem->key = key;
    newElem->value = value;
    newElem->overflow_bucket = NULL;

    if (map[index]==NULL)
        {
            map[index] = newElem;
        }
    else
    {
        HashmapElem* tmp = map[index];
        while (tmp)
        {
            if (strcmp(tmp->key, key) == 0)
            {
                tmp->value = newElem->value;
                return;
            }
            tmp = tmp->overflow_bucket;
        }
        {
            newElem->overflow_bucket = map[index];
            map[index] = newElem;
        }
    }
}

char* Hashmap_getValue(HashmapElem** map, char* key)
{
    int index = Hashmap_hash(key);
    HashmapElem* elem = map[index];
    
    
    while (elem!=NULL)
    {
        if (strcmp(elem->key,key)==0)
            return elem->value;
        elem = elem->overflow_bucket;
    }
    return NULL;
}

void Hashmap_delete(HashmapElem** map, char* key)
{
    int index = Hashmap_hash(key);
    HashmapElem* currEl = map[index];
    HashmapElem* prevEl = NULL;
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
                map[index] = currEl -> overflow_bucket;
            }
            free(currEl);
            return;
        }
        prevEl= currEl;
        currEl = currEl->overflow_bucket;
    }
    printf("Значение не найдено.\n");
    return;

}

char* Hashmap_All(HashmapElem** hashmap)
{
    char string[1024] = {'\0'};
    bool empty = true;
    for (int i = 0; i<HASHMAP_CAPACITY; i++)
    {
        HashmapElem* hashelem = hashmap[i];
        if (hashelem)
        {
            empty = false;
            HashmapElem* overflow = hashelem->overflow_bucket;
            strcat(string,hashelem->key);
            strcat(string, ":");
            strcat(string, hashelem->value);
            strcat(string, ";");
            while (overflow)
            {
                strcat(string,hashelem->key);
                strcat(string, ":");
                strcat(string, hashelem->value);
                strcat(string, ";");
                overflow=overflow->overflow_bucket;
            }
        }
    }
    if (empty)
        return "is empty.";
    return strdup(string);
}