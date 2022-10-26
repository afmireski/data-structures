/***********************************************
| * author: André Felipe Mireski
| * filename: stack_linked.h
************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "stack.h"

#define DEFAULT_LEN 5
/***********************************************
| STRUCTS
************************************************/

typedef struct node
{
    any data;
    struct node *next;
} Node;

struct stack
{
    Node *top;
    int qty;
};

/***********************************************
| IMPLEMENTATION
************************************************/

Stack *stack_create()
{
    Stack *st = (Stack *)calloc(1, sizeof(Stack));

    st->top = NULL;
    st->qty = 0;

    return st;
}

void stack_destroy(Stack **address)
{
    Node *temp = (*address)->top;
    Node *aux;
    while (temp != NULL)
    {
        aux = temp;
        temp = temp->next;
        free(aux);
    }

    free(*address);

    *address = NULL;
}

// any *expand_vector(int *len, any *v)
// {
//     int n = *len > 1000 ? *len + 100 : *len * 2;
//     any *new_array = (any *)calloc(n, sizeof(any));

//     int i;
//     for (i = 0; i < *len; i++)
//     {
//         any ele = *(v + i);
//         *(new_array + i) = ele;
//     }

//     *len = n;

//     return new_array;
// }

Node *newNode(any value, Node *next)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    node->next = next;

    return node;
}

bool stack_stackUp(Stack *st, any element)
{
    if (st == NULL)
    {
        printf("Error, the stack cannot be null!!!\n");
        return false;
    }

    Node *new_node = newNode(element, st->top);

    st->top = new_node;
    st->qty++;

    return true;
}

bool stack_unstack(Stack *st, any *output)
{
    if (st == NULL)
    {
        printf("Error, the stack cannot be null!!!\n");
        return false;
    }
    else if (st->qty == 0)
    {
        printf("Error, the stack is empty!!!\n");
        return false;
    }

    Node *top = st->top;

    *output = top->data;
    st->top = top->next;

    free(top);

    st->qty--;

    return true;
}

bool stack_top(Stack *st, any *output)
{
    if (st == NULL)
    {
        printf("Error, the stack cannot be null!!!\n");
        return false;
    }
    else if (st->qty == 0)
    {
        printf("Error, the stack is empty!!!\n");
        return false;
    }

    *output = st->top->data;

    return true;
}

bool stack_isEmpty(Stack *st)
{
    if (st == NULL)
    {
        printf("Error, the stack cannot be null!!!\n");
        return false;
    }

    return st->qty == 0 ? true : false;
}

void stack_print(Stack *st)
{
    if (st == NULL)
    {
        printf("Error, the stack cannot be null!!!\n");
    }
    else if (st->qty == 0)
    {
        printf("Error, the stack is empty!!!\n");
    }
    else
    {
        printf("-------\n");
        Node *temp = st->top;
        while (temp != NULL)
        {
            printf("|  %d  |\n", temp->data);
            temp = temp->next;
        }
        printf("-------\n");
    }
}

int stack_size(Stack *st)
{
    if (st == NULL)
    {
        printf("Error, the stack cannot be null!!!\n");
        return -1;
    }

    return st->qty;
}

Stack *stack_clone(Stack *st)
{
    if (st == NULL)
    {
        printf("Error, the stack cannot be null!!!\n");
        return false;
    }
    else if (st->qty == 0)
    {
        printf("Error, the stack is empty!!!\n");
        return false;
    }

    Stack *st2 = (Stack *)calloc(1, sizeof(Stack));

    Node *temp1 = st->top;

    st2->top = (Node *)malloc(sizeof(Node));

    Node *temp2 = st2->top;
    while (true)
    {
        temp2->data = temp1->data;
        temp2->next = NULL;

        temp1 = temp1->next;
        if (temp1 == NULL)
            break;

        temp2->next = (Node *)malloc(sizeof(Node));
        temp2 = temp2->next;
    }

    st2->qty = st->qty;

    return st2;
}

bool stack_revert(Stack *st)
{
    if (st == NULL)
    {
        printf("Error, the stack cannot be null!!!\n");
        return false;
    }
    else if (st->qty == 0)
    {
        printf("Error, the stack is empty!!!\n");
        return false;
    }

    Node **nodes = (Node **)calloc(st->qty, sizeof(Node *));

    Node *temp = st->top;

    int i = 0;
    while (temp != NULL)
    {
        nodes[i] = temp;
        temp = temp->next;
        i++;
    }
    for (int j = st->qty - 1; j > 0; j--)
    {
        nodes[j]->next = nodes[j - 1];
    }

    nodes[0]->next = NULL;
    st->top = nodes[st->qty - 1];

    free(nodes);

    return true;
}

bool stack_stackUpMany(Stack *st, any *vector, int len)
{
    if (st == NULL)
    {
        printf("Error, the stack cannot be null!!!\n");
        return false;
    }
    else if (vector == NULL)
    {
        printf("Error, the vector cannot be null!!!\n");
        return false;
    }
    else if (len <= 0)
    {
        printf("Error, the len value should be a positive value!!!\n");
        return false;
    }

    Node *new_top = (Node *)malloc(sizeof(Node));
    Node *temp = new_top;
    for (int i = len - 1; i >= 0; i--)
    {
        temp->data = vector[i];

        if (i > 0)
        {
            temp->next = (Node *)malloc(sizeof(Node));
            temp = temp->next;
        }
    }
    temp->next = st->top;
    st->top = new_top;
    st->qty += len;

    return true;
}

bool stack_toString(Stack *st, char *str)
{
    if (st == NULL)
    {
        printf("Error, the stack is NULL!!!\n");

        return false;
    }
    else if (st->qty == 0)
    {
        printf("Error, the stack is empthy!!!\n");

        return false;
    }

    char buffer[50];

    *str = '\0';
    strcat(str, "[ ");

    Node *temp = st->top;

    while (temp != NULL)
    {
        sprintf(buffer, "%d", temp->data);
        strcat(str, buffer);

        if (temp->next != NULL)
        {
            strcat(str, " | ");
        }

        temp = temp->next;
    }
    strcat(str, " ]");

    return true;
}