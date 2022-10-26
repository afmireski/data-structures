/***********************************************
| * author: André Felipe Mireski
| * filename: stack_contiguous.h
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
struct stack
{
    any *data;
    int len;
    int qty;
};

/***********************************************
| IMPLEMENTATION
************************************************/

Stack *stack_create()
{
    Stack *st = (Stack *)calloc(1, sizeof(Stack));

    st->data = (any *)calloc(DEFAULT_LEN, sizeof(any));
    st->len = DEFAULT_LEN;
    st->qty = 0;

    return st;
}

void stack_destroy(Stack **address)
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

bool stack_stackUp(Stack *st, any element)
{
    if (st == NULL)
    {
        printf("Error, the stack cannot be null!!!\n");
        return false;
    }

    int len = st->len;
    int qty = st->qty;

    if (qty >= len)
    {
        any *new_data = expand_vector(&st->len, st->data);

        if (new_data == NULL)
        {
            printf("Error, the stack expansion failed!!!\n");
            return false;
        }

        free(st->data);
        st->data = new_data;
    }

    for (int i = qty - 1; i >= 0; i--)
    {
        st->data[i + 1] = st->data[i];
    }

    st->data[0] = element;
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

    *output = st->data[0];

    int qty = st->qty;
    for (int i = 0; i < qty - 1; i++)
    {
        st->data[i] = st->data[i + 1];
    }

    st->data[qty - 1] = 0;
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

    *output = st->data[0];

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
        for (int i = 0; i < st->qty; i++)
        {
            printf("|  %d  |\n", st->data[i]);
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

    st2->data = (any *)calloc(st->len, sizeof(any));
    st2->len = st->len;
    st2->qty = st->qty;

    for (int i = 0; i < st->qty; i++)
    {
        st2->data[i] = st->data[i];
    }

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

    int i = 0;
    int j = st->qty - 1;

    any temp;
    while (i < j)
    {
        temp = st->data[i];
        st->data[i] = st->data[j];
        st->data[j] = temp;
        i++;
        j--;
    }

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

    any *data = st->data;
    int t_qty = st->qty + len;

    int new_len = st->len;

    if (st->qty >= st->len || t_qty >= st->len)
    {
        new_len = (len + st->len) * 2;
    }

    /*
     Se a pilha precisar de expansão será utilizado o valor
     gerado no if.
     Caso contrário usa-se o tamanho original.
     */
    st->data = (any *)calloc(new_len, sizeof(any));

    if (st->data == NULL)
    {
        printf("Error, the stack expansion failed!!!\n");
        return false;
    }

    st->len = new_len;

    int i = 0;
    for (int k = len - 1; k >= 0; k--, i++)
    {
        st->data[i] = vector[k];
    }
    for (int j = 0; j < st->qty; j++, i++)
    {
        st->data[i] = data[j];
    }

    st->qty = t_qty;

    free(data);

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
    for (int i = 0; i < st->qty; i++)
    {
        sprintf(buffer, "%d", st->data[i]);
        strcat(str, buffer);

        if (i < st->qty - 1)
        {
            strcat(str, " | ");
        }
    }
    strcat(str, " ]");
}