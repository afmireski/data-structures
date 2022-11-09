/***********************************************
| * author: André Felipe Mireski
| * filename: list_without_sentinel.c
************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"

/***********************************************
| STRUCTS
************************************************/
typedef struct node
{
    any data;
    struct node *back;
    struct node *next;
} Node;

struct list
{
    Node *begin;
    Node *end;
    int qty;
};

/***********************************************
| ACTIONS
************************************************/
List *list_create()
{
    List *l = (List *)malloc(sizeof(List));

    l->begin = NULL;
    l->end = NULL;
    l->qty = 0;

    return l;
}

void list_destroy(List **address)
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

Node *newNode(any value, Node *back, Node *next)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    node->back = back;
    node->next = next;

    return node;
}

void list_print(List *l)
{
    if (l == NULL)
    {
        printf("Error, the list cannot be null!!!\n");
    }
    else if (l->qty == 0)
    {
        printf("Error, the list is empty!!!\n");
    }
    else
    {
        Node *temp = l->begin;

        printf("[");
        while (temp != NULL)
        {
            printf("%d, ", temp->data);
            temp = temp->next;
        }
        printf("\b\b]\n");
    }
}

int list_size(List *l)
{
    if (l == NULL)
    {
        printf("Error, the list cannot be null!!!\n");
        return -1;
    }
    return l->qty;
}

bool list_isEmpty(List *l)
{
    if (l == NULL)
    {
        printf("Error, the list cannot be null!!!\n");
        return false;
    }

    return l->qty == 0;
}

bool list_append(List *l, any element)
{
    if (l == NULL)
    {
        printf("Error, the list cannot be null!!!\n");
        return false;
    }

    Node *new = newNode(element, l->end, NULL);

    if (l->qty == 0)
    {
        l->begin = new;
    }

    l->end->next = new;
    l->end = new;
    l->qty++;

    return true;
}

bool list_insert(List *l, any element, int index)
{
    if (l == NULL)
    {
        printf("Error, the list cannot be null!!!\n");
        return false;
    } else if (index > l->qty) {
        printf("Error, the index should be into the interval [0, %d]!!!\n", l->qty);
        return false;
    }

    Node *new = newNode(element, NULL, NULL);

    if (l->qty == 0) {
        l->begin = new;
        l->end = new;
    } else if (index == 0) {
        new->next = l->begin;
        l->begin->back = new;
        l->begin = new;       
    } else if (index = l->qty) {
        new->back = l->end;
        l->end->next = new;
        l->end = new;
    } else {
        Node* temp = l->begin;

        // Encontra o Node atual da posição index
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }

        new->next = temp;
        new->back = temp->back;
        temp->back = new;
        new->back->next = new;
    }

    l->qty++;
    return true;
}

bool list_removeAt(List *l, int index, any *output);

int list_remove(List *l, any element);

bool list_replace(List *l, int index, any newElement);

int list_indexOf(List *l, any element);

bool list_returnAt(List *l, int index, any *output);

bool list_toString(List *l, char *str);
