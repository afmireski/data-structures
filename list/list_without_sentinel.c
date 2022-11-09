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
    else
    {
        l->end->next = new;
    }

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
    }
    else if (index < 0 || index > l->qty)
    {
        printf("Error, the index should be into the interval [0, %d]!!!\n", l->qty);
        return false;
    }

    Node *new = newNode(element, NULL, NULL);

    if (l->qty == 0)
    {
        l->begin = new;
        l->end = new;
    }
    else if (index == 0)
    {
        new->next = l->begin;
        l->begin->back = new;
        l->begin = new;
    }
    else if (index == l->qty)
    {
        new->back = l->end;
        l->end->next = new;
        l->end = new;
    }
    else
    {
        Node *temp = l->begin;

        // Encontra o Node atual da posição index
        for (int i = 0; i < index; i++)
        {
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
    else if (index >= l->qty)
    {
        printf("Error, the index should be into the interval [0, %d]!!!\n", l->qty - 1);
        return false;
    }

    Node *temp = l->begin;

    // Encontra o Node atual da posição index
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }

    if (index == 0)
    {
        l->begin = temp->next;
        temp->next->back = NULL;
        temp->next = NULL;
    }
    else if (index == l->qty - 1)
    {
        l->end = temp->back;
        temp->back->next = NULL;
        temp->back = NULL;
    }
    else
    {
        temp->back->next = temp->next;
        temp->next->back = temp->back;
        temp->back = NULL;
        temp->next = NULL;
    }

    *output = temp->data;
    free(temp);
    l->qty--;

    if (l->qty == 0)
    {
        l->begin = NULL;
        l->end = NULL;
    }

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

    Node *temp = l->begin;

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

    if (i == 0)
    {
        l->begin = temp->next;
        temp->next->back = NULL;
        temp->next = NULL;
    }
    else if (i == l->qty - 1)
    {
        l->end = temp->back;
        temp->back->next = NULL;
        temp->back = NULL;
    }
    else
    {
        temp->back->next = temp->next;
        temp->next->back = temp->back;
        temp->back = NULL;
        temp->next = NULL;
    }

    free(temp);
    l->qty--;

    if (l->qty == 0)
    {
        l->begin = NULL;
        l->end = NULL;
    }

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
    else if (index >= l->qty)
    {
        printf("Error, the index should be into the interval [0, %d]!!!\n", l->qty - 1);
        return false;
    }

    Node *temp = l->begin;
    for (int i = 0; i <= index; i++)
    {
        temp = temp->next;
    }

    temp->data = newElement;
    return true;
}

int list_indexOf(List *l, any element)
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

    Node *temp = l->begin;
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
    else if (index >= l->qty)
    {
        printf("Error, the index should be into the interval [0, %d]!!!\n", l->qty - 1);
        return false;
    }

    Node *temp = l->begin;
    for (int i = 0; i <= index; i++)
    {
        temp = temp->next;
    }

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

    Node *temp = l->begin;
    while (temp != NULL)
    {
        sprintf(buffer, "%d", temp->data);
        strcat(str, buffer);
        if (temp->next != NULL)
        {
            strcat(str, ", ");
        }
        temp = temp->next;
    }
    strcat(str, "]");

    return true;
}
