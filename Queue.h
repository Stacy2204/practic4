#ifndef QUEUE_H
#define QUEUE_H


typedef struct Node {
    char* value;
    struct Node *next;
} Node;

typedef struct Queue
{
    Node* head;
    Node* tail;
} Queue;

void Queue_push(Queue* q, char* data);
char* Queue_pop(Queue* q);
void Queue_print(Node* head);
char* Queue_read(Queue* q);
#endif