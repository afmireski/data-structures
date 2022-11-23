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
    Node *sentinel;
    int qty;
};

/***********************************************
| ACTIONS
************************************************/
Node *newNode(any value, Node *back, Node *next)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    node->back = back;
    node->next = next;

    return node;
}

Node *findNode(List *l, int index)
{
    Node *temp = l->sentinel->next;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }

    return temp;
}

List *list_create()
{
    List *l = (List *)malloc(sizeof(List));

    l->sentinel = newNode(0, NULL, NULL);
    l->sentinel->next = l->sentinel;
    l->sentinel->back = l->sentinel;
    l->qty = 0;

    return l;
}

void list_destroy(List **address)
{
    Node *sentinel = (*address)->sentinel;
    Node *temp = sentinel->next;
    Node *aux;

    while (temp != sentinel)
    {
        aux = temp;
        temp = temp->next;
        free(aux);
    }
    free(sentinel);
    free(*address);
    *address = NULL;
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
        Node *temp = l->sentinel->next;

        printf("[");
        while (temp != l->sentinel)
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

    Node *sentinel = l->sentinel;
    Node *new = newNode(element, NULL, sentinel);

    new->back = sentinel->back;
    sentinel->back->next = new;
    sentinel->back = new;

    l->qty++;

    return true;
}

bool list_insert(List *l, any element, int index)
{
    if (l == NULL)
    {
        printf("Error, the list cannot be null!!!\n");
        return false;
    }
    else if (index < 0 || index > l->qty)
    {
        printf("Error, the index should be into the interval [0, %d]!!!\n", l->qty);
        return false;
    }

    Node *new = newNode(element, NULL, NULL);

    Node *temp = findNode(l, index);

    new->next = temp;
    new->back = temp->back;
    temp->back = new;
    new->back->next = new;

    l->qty++;
    return true;
}

bool list_removeAt(List *l, int index, any *output)
{
    if (l == NULL)
    {
        printf("Error, the list cannot be null!!!\n");
        return false;
    }
    else if (l->qty == 0)
    {
        printf("Error, the list is empty!!!\n");
        return false;
    }
    else if (index < 0 || index >= l->qty)
    {
        printf("Error, the index should be into the interval [0, %d]!!!\n", l->qty - 1);
        return false;
    }

    Node *temp = findNode(l, index);

    temp->back->next = temp->next;
    temp->next->back = temp->back;
    temp->back = NULL;
    temp->next = NULL;

    *output = temp->data;
    free(temp);
    l->qty--;

    return true;
}

int list_remove(List *l, any element)
{
    if (l == NULL)
    {
        printf("Error, the list cannot be null!!!\n");
        return -1;
    }
    else if (l->qty == 0)
    {
        printf("Error, the list is empty!!!\n");
        return -1;
    }

    Node *temp = l->sentinel->next;

    // Encontra o Node que abriga o element informado
    int i;
    bool hasElement = false;
    for (i = 0; i < l->qty; i++)
    {
        if (temp->data == element)
        {
            hasElement = true;
            break;
        }
        temp = temp->next;
    }

    if (!hasElement)
    {
        printf("Error, %d not found!!!\n", element);
        return -1;
    }

    temp->back->next = temp->next;
    temp->next->back = temp->back;
    temp->back = NULL;
    temp->next = NULL;

    free(temp);
    l->qty--;

    return i;
}

bool list_replace(List *l, int index, any newElement)
{
    if (l == NULL)
    {
        printf("Error, the list cannot be null!!!\n");
        return false;
    }
    else if (l->qty == 0)
    {
        printf("Error, the list is empty!!!\n");
        return false;
    }
    else if (index < 0 || index >= l->qty)
    {
        printf("Error, the index should be into the interval [0, %d]!!!\n", l->qty - 1);
        return false;
    }

    Node *temp = findNode(l, index);

    temp->data = newElement;
    return true;
}

int list_indexOf(List *l, any element)
{
    if (l == NULL)
    {
        printf("Error, the list cannot be null!!!\n");
        return -1;
    }
    else if (l->qty == 0)
    {
        printf("Error, the list is empty!!!\n");
        return -1;
    }

    Node *temp = l->sentinel->next;
    for (int i = 0; i < l->qty; i++)
    {
        if (temp->data == element)
            return i;

        temp = temp->next;
    }

    return -1;
}

bool list_returnAt(List *l, int index, any *output)
{
    if (l == NULL)
    {
        printf("Error, the list cannot be null!!!\n");
        return false;
    }
    else if (l->qty == 0)
    {
        printf("Error, the list is empty!!!\n");
        return false;
    }
    else if (index < 0 || index >= l->qty)
    {
        printf("Error, the index should be into the interval [0, %d]!!!\n", l->qty - 1);
        return false;
    }

    Node *temp = findNode(l, index);

    *output = temp->data;

    return true;
}

bool list_toString(List *l, char *str)
{
    if (l == NULL)
    {
        printf("Error, the list cannot be null!!!\n");
        return false;
    }
    else if (l->qty == 0)
    {
        printf("Error, the list is empty!!!\n");
        return false;
    }

    char buffer[50];

    *str = '\0';
    strcat(str, "[");

    Node *temp = l->sentinel->next;
    while (temp != l->sentinel)
    {
        sprintf(buffer, "%d", temp->data);
        strcat(str, buffer);
        if (temp->next != l->sentinel)
        {
            strcat(str, ", ");
        }
        temp = temp->next;
    }
    strcat(str, "]");

    return true;
}
