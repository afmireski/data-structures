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
    if (q == NULL)
    {
        printf("Error, the queue cannot be null!!!\n");
        return NULL;
    }
    else if (q->qty == 0)
    {
        printf("Error, the queue is empty!!!\n");
        return NULL;
    }

    Queue *q2 = (Queue *)malloc(sizeof(Queue));

    q2->qty = q->qty;
    q2->len = q->len;
    q2->begin = q->begin;
    q2->end = q->end;
    q2->data = (any*) calloc(q->len, sizeof(any));

    for (int i = q->begin; i < q->end; i++) {
        q2->data[i] = q->data[i];
    }

    return q2;
}

bool queue_toString(Queue *q, char *str)
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

    char buffer[50];

    *str = '\0';
    strcat(str, "| ");

    for (int i = 0; i < q->end; i++)
    {
        sprintf(buffer, "%d", q->data[i]);
        strcat(str, buffer);

        if (i < q->end-1)
        {
            strcat(str, ", ");
        }
    }

    return true;
}

bool queue_insertMany(Queue *q, any *vector, int len)
{
    if (q == NULL)
    {
        printf("Error, the queue cannot be null!!!\n");
        return false;
    }
    else if (vector == NULL)
    {
        printf("Error, the vector cannot be null!!!\n");
        return false;
    }
    else if (len <= 0)
    {
        printf("Error, the vector is empty!!!\n");
        return false;
    }

    int total_qty = q->qty + len;

    if (total_qty >= q->len) {
        int new_len = q->len + len;
        any *new_data = expand_vector(&new_len, q->data);

        if (new_data == NULL)
        {
            printf("Error, the queue expansion failed!!!\n");
            return false;
        }

        free(q->data);
        q->data = new_data;
        q->len = new_len;
    }

    int j = q->end;
    for (int i = 0; i < len; i++,j++) {
        q->data[j] = vector[i];
    }
    q->end = j+1;
    q->qty = total_qty;

    return true;
}
