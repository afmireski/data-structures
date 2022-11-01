/***********************************************
| * author: André Felipe Mireski
| * filename: queue_linked.c
************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "queue.h"

/***********************************************
| STRUCTS
************************************************/
typedef struct node
{
    any data;
    struct node *next;
} Node;

struct queue
{
    Node *begin;
    Node *end;
    int qty;
};

/***********************************************
| IMPLEMENTATION
************************************************/
Queue *queue_create()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));

    q->begin = NULL;
    q->end = NULL;
    q->qty = 0;

    return q;
}

void queue_destroy(Queue **address)
{
    Node *temp = (*address)->begin;
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

Node *newNode(any value, Node *next)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    node->next = next;

    return node;
}

bool queue_insert(Queue *q, any element)
{
    if (q == NULL)
    {
        printf("Error, the queue cannot be null!!!\n");
        return false;
    }

    Node *new_node = newNode(element, NULL);

    if (q->qty == 0)
    {
        q->begin = new_node;
    }
    else
    {
        q->end->next = new_node;
    }

    q->end = new_node;
    q->qty++;

    return true;
}

bool queue_remove(Queue *q, any *output)
{
    if (q == NULL)
    {
        printf("Error, the queue cannot be null!!!\n");
        return false;
    }
    else if (q->qty == 0)
    {
        printf("Error, the queue is empty!!!\n");
        return false;
    }

    Node *begin = q->begin;

    output = begin->data;

    q->begin = begin->next;

    begin->next = NULL;
    free(begin);

    q->qty--;

    return true;
}

bool queue_getFirst(Queue *q, any *output)
{
    if (q == NULL)
    {
        printf("Error, the queue cannot be null!!!\n");
        return false;
    }
    else if (q->qty == 0)
    {
        printf("Error, the queue is empty!!!\n");
        return false;
    }

    *output = q->begin->data;

    return true;
}

bool queue_isEmpty(Queue *q)
{
    if (q == NULL)
    {
        printf("Error, the queue cannot be null!!!\n");
        return false;
    }

    return q->qty == 0;
}

int queue_size(Queue *q)
{
    if (q == NULL)
    {
        printf("Error, the queue cannot be null!!!\n");
        return -1;
    }

    return q->qty;
}

void queue_print(Queue *q)
{
    if (q == NULL)
    {
        printf("Error, the queue cannot be null!!!\n");
    }
    else if (q->qty == 0)
    {
        printf("Error, the queue is empty!!!\n");
    }
    else
    {
        Node *temp = q->begin;

        printf("<-< ");
        while (temp != NULL)
        {
            printf(" %d", temp->data);
            temp = temp->next;
        }
        printf("|\n");
    }
}

Queue *queue_clone(Queue *q)
{
    if (q == NULL)
    {
        printf("Error, the queue cannot be null!!!\n");
        return false;
    }
    else if (q->qty == 0)
    {
        printf("Error, the queue is empty!!!\n");
        return false;
    }

    Queue* q2 = (Queue*) malloc(sizeof(Queue));

    Node* temp1 = q->begin;

    q2->begin = (Queue*) malloc(sizeof(Queue));
    Node* temp2 = q2->begin;

    while (true) {
        temp2->data = temp1->data;
        temp2->next = NULL;

        temp1 = temp1->next;
        if (temp1 == NULL) {
            q2->end = temp2;
            break;
        }

        temp2->next = (Node*) malloc(sizeof(Node));
        temp2 = temp2->next;
    }

    q2->qty = q->qty;

    return q2;
}

bool queue_toString(Queue *q, char *str);

bool queue_insertMany(Queue *q, any *vector, int len);
