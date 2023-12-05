#ifndef HASHMAP_H
#define HASHMAP_H
#define HASHMAP_CAPACITY 1000

typedef struct HashmapElem
{
    char* key;
    char* value;
    struct HashmapElem* overflow_bucket;
} HashmapElem;

int Hashmap_hash(char* key);
void Hashmap_add(HashmapElem** map, char* key, char* value);
char* Hashmap_getValue(HashmapElem** map, char* key);
void Hashmap_delete(HashmapElem** map, char* key);
char* Hashmap_All(HashmapElem** hashmap);

#endif