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
List *list_create();
void list_destroy(List **address);
void list_print(List *l);
int list_size(List *l);
bool list_isEmpty(List *l);

bool list_append(List *l, any element);
bool list_insert(List *l, any element, int index);

bool list_removeAt(List *l, int index, any *output);
int list_remove(List *l, any element);

bool list_replace(List *l, int index, any newElement);
int list_indexOf(List *l, any element);
bool list_returnAt(List *l, int index, any *output);

bool list_toString(List *l, char *str);
