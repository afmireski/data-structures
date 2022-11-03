/***********************************************
| * author: André Felipe Mireski
| * filename: queue_contiguos.c
************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "queue.h"

#define DEFAULT_LEN 10
/***********************************************
| STRUCTS
************************************************/

struct queue
{
    any *data;
    int len;
    int qty;
    int begin;
    int end;
};

/***********************************************
| IMPLEMENTATION
************************************************/
Queue *queue_create()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));

    q->data = (any *)calloc(DEFAULT_LEN, sizeof(any));
    q->len = DEFAULT_LEN;
    q->qty = 0;
    q->begin = 0;
    q->end = 0;

    return q;
}

void queue_destroy(Queue **address)
{
    free((*address)->data);
    free(*address);

    *address = NULL;
}

any *expand_vector(int *len, any *v)
{
    int n = *len > 1000 ? *len + 100 : *len * 2;
    any *new_array = (any *)calloc(n, sizeof(any));

    int i;
    for (i = 0; i < *len; i++)
    {
        any ele = *(v + i);
        *(new_array + i) = ele;
    }

    *len = n;

    return new_array;
}

bool queue_insert(Queue *q, any element)
{
    if (q == NULL)
    {
        printf("Error, the queue cannot be null!!!\n");
        return false;
    }

    if (q->qty >= q->len)
    {
        any *new_data = expand_vector(&q->len, q->data);

        if (new_data == NULL)
        {
            printf("Error, the queue expansion failed!!!\n");
            return false;
        }

        free(q->data);
        q->data = new_data;
    }

    q->data[q->end] = element;

    q->end++;
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

    *output = q->data[q->begin];
    q->begin++;

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

    *output = q->data[q->begin];

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
        printf("<-< ");
        for (int i = q->begin; i < q->end; i++)
        {
            printf(" %d", q->data[i]);
        }
        printf("|\n");
    }
}

Queue *queue_clone(Queue *q)
{
    // if (q == NULL)
    // {
    //     printf("Error, the queue cannot be null!!!\n");
    //     return NULL;
    // }
    // else if (q->qty == 0)
    // {
    //     printf("Error, the queue is empty!!!\n");
    //     return NULL;
    // }

    // Queue *q2 = (Queue *)malloc(sizeof(Queue));

    // Node *temp1 = q->begin;

    // q2->begin = (Node *)malloc(sizeof(Node));
    // Node *temp2 = q2->begin;

    // while (true)
    // {
    //     temp2->data = temp1->data;
    //     temp2->next = NULL;

    //     temp1 = temp1->next;
    //     if (temp1 == NULL)
    //     {
    //         q2->end = temp2;
    //         break;
    //     }

    //     temp2->next = (Node *)malloc(sizeof(Node));
    //     temp2 = temp2->next;
    // }

    // q2->qty = q->qty;

    // return q2;
}

bool queue_toString(Queue *q, char *str)
{
    // if (q == NULL)
    // {
    //     printf("Error, the queue cannot be null!!!\n");
    //     return false;
    // }
    // else if (q->qty == 0)
    // {
    //     printf("Error, the queue is empty!!!\n");
    //     return false;
    // }

    // char buffer[50];

    // *str = '\0';
    // strcat(str, "| ");

    // Node *temp = q->begin;

    // while (temp != NULL)
    // {
    //     sprintf(buffer, "%d", temp->data);
    //     strcat(str, buffer);

    //     if (temp->next != NULL)
    //     {
    //         strcat(str, ", ");
    //     }

    //     temp = temp->next;
    // }

    // return true;
}

bool queue_insertMany(Queue *q, any *vector, int len)
{
    // if (q == NULL)
    // {
    //     printf("Error, the queue cannot be null!!!\n");
    //     return false;
    // }
    // else if (vector == NULL)
    // {
    //     printf("Error, the vector cannot be null!!!\n");
    //     return false;
    // }
    // else if (len <= 0)
    // {
    //     printf("Error, the vector is empty!!!\n");
    //     return false;
    // }

    // Node *first = (Node *)malloc(sizeof(Node));
    // Node *temp = first;

    // for (int i = 0; i < len; i++)
    // {
    //     temp->data = vector[i];

    //     if (i < len - 1)
    //     {
    //         temp->next = (Node *)malloc(sizeof(Node));
    //         temp = temp->next;
    //     }
    // }

    // temp->next = NULL;

    // if (q->qty == 0)
    // {
    //     q->begin = first;
    // }
    // else
    // {
    //     q->end->next = first;
    // }

    // q->end = temp;
    // q->qty += len;

    // return true;
}
