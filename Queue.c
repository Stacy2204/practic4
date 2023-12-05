#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>

void Queue_push(Queue* q, char* data)
{
    
    Node* newNode = malloc(sizeof(Node));
    newNode->value = data;
    newNode->next = NULL;
    
    if (q->head == NULL)
    {
        q->head = newNode;
        q->tail = newNode;
    }
    else
    {
        q->tail->next = newNode;
        q->tail = newNode;
    }
    return;
}

char* Queue_pop(Queue* q)
{
    if (q->head == NULL) {
        return "Queue is empty";
    }
    char* value = q->head->value;
    Node* tmp = q->head;
    q->head=q->head->next;
    if (q->head == NULL)
        q->tail = NULL;

    free(tmp);

    return value;
}

void Queue_print(Node* head)
{
    if (head==NULL)
    {
        printf("Queue is empty\n");
        return;
    }

    Node* tmp = head;
    while (tmp!=NULL)
    {
        printf("%s ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

char* Queue_read(Queue* q)
{
    if (q->head == NULL)
        return "Queue is empty";
    return q->head->value;
}
