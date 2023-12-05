#ifndef STACK_H
#define STACK_H
typedef struct stackNode {
    char* data;
    struct stackNode* next;
} stackNode;

void Stack_push(stackNode** head, char* data);
char* Stack_pop(stackNode** head);
#endif