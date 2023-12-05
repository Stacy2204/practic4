#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include "Stack.h"
#include "Queue.h"
#include "Hashmap.h"
#include "Set.h"
#include <string.h>

char* basedata(char* str)
{
    setlocale(LC_ALL, "Russian");
    static stackNode* stack = NULL;
    static Queue* q = NULL;
    if (q==NULL)
    {
        q=malloc(sizeof(Queue));
        q->head = NULL;
        q->tail = NULL;
    }
    static Queue* queue = NULL;
    if (queue==NULL)
    {
        queue=malloc(sizeof(Queue));
        queue->head = NULL;
        queue->tail = NULL;
    }
    static HashmapElem* hashmap[HASHMAP_CAPACITY] = {NULL};
    static Set* set[HASHMAP_CAPACITY] = {NULL};


        if (strstr(str,"mystack")!=NULL)
        {
            if (strstr(str,"SPOP")!=NULL)
            {
                return Stack_pop(&stack);
            }
            else if (strstr(str,"SPUSH")!=NULL)
            {   
                char delim[] = " ";
                char *token;
                int count = 0;
                char data[100]; //массив для хранения третьего слова команды
                token = strtok(str, delim);
                while(token != NULL) {
                    count++;
                    if (count == 3) {
                        strcpy(data, token);
                        break;
                    }
                    token = strtok(NULL, delim);
                }
                if (count<3)
                    return "Недостаточно аргументов.";
               else
               {
                char* pup = strdup(data);
                if (pup[strlen(pup)-1] == '\n')
                        pup[strlen(pup)-1]='\0';

                Stack_push(&stack, pup);
                return "Элемент успешно добавлен в стэк.";
               }
            } 
            else 
            {
                return "Команда некорректна.";
            }
        }
        else if (strstr(str,"myqueue")!=NULL)
        {
           if (strstr(str,"QPOP")!=NULL)
            {
               return Queue_pop(q);
            }
            else if (strstr(str,"QPUSH")!=NULL)
            {   
                char delim[] = " ";
                char *token;
                int count = 0;
                char data[100]; // массив для хранения третьего слова команлы
                token = strtok(str, delim);
                while(token != NULL) {
                    count++;
                    if (count == 3) {
                        strcpy(data, token);
                        break;
                    }
                    token = strtok(NULL, delim);
                }
                if (count<3)
                    return "Недостаточно аргументов.";
                else
                {
                    char* pup = strdup(data);
                    if (pup[strlen(pup)-1] == '\n')
                        pup[strlen(pup)-1]='\0';

                    Queue_push(q, pup);
                    return  "Элемент успешно добавлен в очередь.";
                }
            } 
            else if (strstr(str, "QREAD")!= NULL)
            {
                return Queue_read(q);
            }
            else 
            {
                return "Команда некорректна.";
            } 
        }

        else if (strstr(str,"MYQUEUE")!=NULL)
        {
           if (strstr(str,"QPOP")!=NULL)
            {
               return Queue_pop(queue);
            }
            else if (strstr(str,"QPUSH")!=NULL)
            {   
                char delim[] = " ";
                char *token;
                int count = 0;
                char data[100]; // массив для хранения третьего слова команлы
                token = strtok(str, delim);
                while(token != NULL) {
                    count++;
                    if (count == 3) {
                        strcpy(data, token);
                        break;
                    }
                    token = strtok(NULL, delim);
                }
                if (count<3)
                    return "Недостаточно аргументов.";
                else
                {
                    char* pup = strdup(data);
                    if (pup[strlen(pup)-1] == '\n')
                        pup[strlen(pup)-1]='\0';

                    Queue_push(queue, pup);
                    return  "Элемент успешно добавлен в очередь.";
                }
            } 
            
            else if (strstr(str, "QREAD")!= NULL)
            {
                return Queue_read(queue);
            }
            else
            {
                return "Команда некорректна.";
            } 
        }

        else if (strstr(str,"myhash")!=NULL)
        {
            if(strstr(str,"HSET")!=NULL)
            {
                char delim[] = " ";
                char *token;
                int count = 0;
                char key[1024]; 
                char value[1024];
                token = strtok(str, delim);
                while(token != NULL) {
                    count++;
                    if (count == 3) {
                        strcpy(key, token);
                    }
                    if (count == 4) {
                        strcpy(value, token);
                        break;
                    }
                    token = strtok(NULL, delim);
                }
                if (count<4)
                    return "Недостаточно аргументов.";
               else 
               {
                char* pup = strdup(key);
                char* cl = strdup(value);
                if (cl[strlen(cl)-1]=='\n')
                    cl[strlen(cl)-1]='\0';
                Hashmap_add(hashmap, pup, cl);
                return  "Элемент успешно добавлен в хэш-таблицу.";
               }

            }
            else if (strstr(str, "HALL")!=NULL)
            {
                return Hashmap_All(hashmap);
            }
            else if(strstr(str,"HGET")!=NULL)
            {
                char delim[] = " ";
                char *token;
                int count = 0;
                char key[100]; 
                token = strtok(str, delim);
                while(token != NULL) {
                    count++;
                    if (count == 3) {
                        strcpy(key, token);
                        break;
                    }
                    token = strtok(NULL, delim);
                }
                if (count<3)
                    return "Недостаточно аргументов.";
                else 
                {
                    char* pup = strdup(key);
                    if (pup[strlen(pup)-1] == '\n')
                        pup[strlen(pup)-1]='\0';

                    if (Hashmap_getValue(hashmap, pup)!=NULL) 
                    {   
                        return Hashmap_getValue(hashmap, pup);
                    }
                    else return "Значение не найдено.";
                }
            }
            else if(strstr(str,"HDEL")!=NULL)
            {
                char delim[] = " ";
                char *token;
                int count = 0;
                char key[100]; //Массив для хранения третьего слова команды
                token = strtok(str, delim);
                while(token != NULL) {
                    count++;
                    if (count == 3) {
                        strcpy(key, token);
                        break;
                    }
                    token = strtok(NULL, delim);
                }
                if (count<3)
                    return "Недостаточно аргументов.";
                else 
                {
                    char* pup = strdup(key);
                    if (pup[strlen(pup)-1] == '\n')
                        pup[strlen(pup)-1]='\0';

                    Hashmap_delete(hashmap, pup);
                    return  "Элемент успешно удален из хэш-таблицы.";
                }
            }
            else
            {
                return "Команда некорректна.";
            }
        }
        else if (strstr(str,"myset")!=NULL)
        {
            if(strstr(str,"SADD")!=NULL)
            {
                char delim[] = " ";
                char *token;
                int count = 0;
                char key[100]; 
                char value[100];
                token = strtok(str, delim);
                while(token != NULL) {
                    count++;
                    if (count == 3) {
                        strcpy(key, token);
                        break;
                    }
                    token = strtok(NULL, delim);
                }
                if (count<3)
                {
                    return "Недостаточно аргументов.";
                }
                else
               {
                char* pup = strdup(key);
                if (pup[strlen(pup)-1] == '\n')
                        pup[strlen(pup)-1]='\0';

                if(Set_Add(set, pup))
                    return  "Элемент успешно добавлен в множество.";
                else return "Элемент уже существует.";
               }

            }
            else if(strstr(str,"SREM")!=NULL)
            {
                char delim[] = " ";
                char *token;
                int count = 0;
                char key[100]; 
                token = strtok(str, delim);
                while(token != NULL) {
                    count++;
                    if (count == 3) {
                        strcpy(key, token);
                        break;
                    }
                    token = strtok(NULL, delim);
                }
                if (count<3)
                    return "Недостаточно аргументов.";
                else
                {
                    char* pup = strdup(key);
                    if (pup[strlen(pup)-1] == '\n')
                        pup[strlen(pup)-1]='\0';

                    Set_Delete(set, pup);
                    return  "Элемент успешно удален из множества.";
                }
            }
            else if(strstr(str,"SISMEMBER")!=NULL)
            {
                char delim[] = " ";
                char *token;
                int count = 0;
                char key[100]; //массив для хранения третьего слова команды
                token = strtok(str, delim);
                while(token != NULL) {
                    count++;
                    if (count == 3) {
                        strcpy(key, token);
                        break;
                    }
                    token = strtok(NULL, delim);
                }
                char* pup = strdup(key);
                if (pup[strlen(pup)-1] == '\n')
                        pup[strlen(pup)-1]='\0';

                if (setIsMember(set, pup)==true)
                {
                    return "is a member";
                }
                else return "is not a member";
            }
            else
            {
                return "Команда некорректна.";
            }
        }
        else 
            return "Команда некорректна.";

        return "secret";
    
}