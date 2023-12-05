#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>

void Stack_push(stackNode** head, char* data) {
    stackNode* tmp = malloc(sizeof(stackNode));
    if (tmp == NULL) {
        printf("error");
        exit(-1);
    }
    tmp->next = *head;
    tmp->data = data;
    *head = tmp;
}

char* Stack_pop(stackNode** head) {
    stackNode* out;
    char* value = NULL;
    if (*head == NULL) {
        return "stack is empty";
    }
    out = *head;
    *head = (*head)->next;
    value = out->data;
    free(out);
    return value;
}

void Stack_print(stackNode* head)
{
    if (head==NULL)
    {
        printf("Stack is empty\n");
        return;
    }

    stackNode* tmp = head;
    while (tmp!=NULL)
    {
        printf("%s ", tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}
