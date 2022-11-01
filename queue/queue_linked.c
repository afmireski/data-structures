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

    if (q->qty == 0) {
        q->begin = new_node;
    } else {
        q->end->next = new_node;
    }

    q->end = new_node;
    q->qty++;

    return true;
}

bool queue_remove(Queue *q, any *output) {
    if (q == NULL)
    {
        printf("Error, the queue cannot be null!!!\n");
        return false;
    }

    Node* begin = q->begin;

    output = begin->data;

    q->begin = begin->next;

    begin->next = NULL;
    free(begin);

    return true;
}

bool queue_getFirst(Queue *q, any *output);

bool queue_isEmpty(Queue *q);

int queue_size(Queue *q);

void queue_print(Queue *q);

Queue *queue_clone(Queue *q);

bool queue_toString(Queue *q, char *str);

bool queue_insertMany(Queue *q, any *vector, int len);
