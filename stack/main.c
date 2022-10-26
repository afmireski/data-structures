/***********************************************
| * author: André Felipe Mireski
| * filename: main.c
| * date: 21/10/2022
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "stack.h"

void verify(int condition, char *message);

void test_stack_create_and_destroy();
void test_stack_stackUp();
void test_stack_unstack();
void test_stack_top();
void test_stack_isEmpty();
void test_stack_clone();
void test_stack_revert();
void test_stack_stackUpMany();
void test_stack_toString();

int main()
{
    printf("/***********************************************\n");
    printf("STACK\n");
    printf("/***********************************************\n\n");
    test_stack_create_and_destroy();
    printf("\n\n");
    test_stack_stackUp();
    printf("\n\n");
    test_stack_unstack();
    printf("\n\n");
    test_stack_top();
    printf("\n\n");
    test_stack_isEmpty();
    printf("\n\n");
    test_stack_clone();
    printf("\n\n");
    test_stack_revert();
    printf("\n\n");
    test_stack_stackUpMany();
    printf("\n\n");
    test_stack_toString();
    printf("\n\n");
    printf("\n\n");    
    printf("/****************** END ********************/\n");
    return 0;
}

void verify(int condition, char *message)
{
    if (condition)
    {
        printf("[PASSED] : %s\n", message);
    }
    else
    {
        printf("[FAILED] : %s\n", message);
    }
}

void test_stack_create_and_destroy()
{
    printf("/***********************************************\n");
    printf("TEST: CREATE AND DESTROY\n");
    printf("/***********************************************\n\n");

    Stack *st = stack_create();

    verify(st != NULL, "Should create a new Stack");

    stack_destroy(&st);

    verify(st == NULL, "Should destroy the Stack");
}

void test_stack_stackUp()
{
    printf("/***********************************************\n");
    printf("TEST: STACK UP\n");
    printf("/***********************************************\n\n");
    Stack *st = NULL;

    any element = 10;

    verify(stack_stackUp(st, element) == false, "Should return false because the Stack is NULL");

    st = stack_create();

    for (int i = 1; i <= 5; i++)
    {
        stack_stackUp(st, (any)i);
    }

    verify(stack_size(st) == 5, "Should create a stack with five elements");

    int top;

    stack_top(st, &top);

    verify(top == 5, "The element on the top of the Stack should be equals 5");

    stack_stackUp(st, element);

    verify(stack_size(st) == 6, "The stack size must be equal to 6, as the expansion was successful.");

    stack_top(st, &top);

    verify(top == element, "The element on the top of the Stack should be equals 10");

    stack_destroy(&st);
}

void test_stack_unstack()
{
    printf("/***********************************************\n");
    printf("TEST: UNSTACK\n");
    printf("/***********************************************\n\n");
    Stack *st = NULL;

    any output;

    verify(stack_unstack(st, &output) == false, "Should return false because the Stack is NULL");

    st = stack_create();

    verify(stack_unstack(st, &output) == false, "Should return false because the Stack is empthy");

    for (int i = 1; i <= 5; i++)
    {
        stack_stackUp(st, (any)i);
    }

    verify(stack_unstack(st, &output) == true, "Should return true because the last element was removed");

    verify(output == 5, "The removed element shoul be equal 5");

    verify(stack_size(st) == 4, "The stack size must be equal to 4, as the removing was successful.");

    any top;

    stack_top(st, &top);

    verify(top == 4, "The new last element should be equal 4");

    stack_destroy(&st);
}

void test_stack_top()
{
    printf("/***********************************************\n");
    printf("TEST: TOP\n");
    printf("/***********************************************\n\n");
    Stack *st = NULL;

    any output;

    verify(stack_top(st, &output) == false, "Should return false because the Stack is NULL");

    st = stack_create();

    verify(stack_top(st, &output) == false, "Should return false because the Stack is empthy");

    for (int i = 1; i <= 3; i++)
    {
        stack_stackUp(st, (any)i);
    }

    stack_top(st, &output);
    verify(output == 3, "The element on the top of the stack should be equals 3.");

    stack_print(st);
    stack_destroy(&st);
}

void test_stack_isEmpty()
{
    printf("/***********************************************\n");
    printf("TEST: IS EMPTY\n");
    printf("/***********************************************\n\n");
    Stack *st = NULL;

    verify(stack_isEmpty(st) == false, "Should return false because the Stack is NULL");

    st = stack_create();

    verify(stack_isEmpty(st) == true, "Should return true because the Stack is empty");

    stack_stackUp(st, 1);

    verify(stack_isEmpty(st) == false, "Should return false because the Stack is not empty");

    stack_destroy(&st);
}

void test_stack_clone()
{
    printf("/***********************************************\n");
    printf("TEST: CLONE\n");
    printf("/***********************************************\n\n");
    Stack *st = NULL;

    verify(stack_clone(st) == false, "Should return false because the Stack is NULL");

    st = stack_create();

    verify(stack_clone(st) == false, "Should return false because the Stack is empty");

    for (int i = 1; i <= 5; i++)
    {
        stack_stackUp(st, i);
    }

    Stack *st2 = stack_clone(st);

    int stSize = stack_size(st);
    int st2Size = stack_size(st2);

    verify(stSize == st2Size, "The size of stack2 should be the same of the original stack");

    any top1, top2;
    stack_top(st, &top1);
    stack_top(st2, &top2);

    verify(top1 == top2, "The last element in both stacks should be the same");

    stack_destroy(&st);
    stack_destroy(&st2);
}

void test_stack_revert()
{
    printf("/***********************************************\n");
    printf("TEST: REVERT\n");
    printf("/***********************************************\n\n");
    Stack *st = NULL;

    verify(stack_revert(st) == false, "Should return false because the Stack is NULL");

    st = stack_create();

    verify(stack_revert(st) == false, "Should return false because the Stack is empty");

    for (int i = 1; i <= 5; i++)
    {
        stack_stackUp(st, i);
    }

    // stack_print(st);
    verify(stack_revert(st) == true, "Should return true because the reversion was successful");

    any top;
    stack_top(st, &top);

    verify(top == 1, "The new last element should be equals 1, because the stack was reverted");
    // stack_print(st);

    stack_destroy(&st);
}

void test_stack_stackUpMany()
{
    printf("/***********************************************\n");
    printf("TEST: STACK UP MANY\n");
    printf("/***********************************************\n\n");
    Stack *st = NULL;

    any *v = NULL;

    int len = 3;

    verify(stack_stackUpMany(st, v, len) == false, "Should return false because the Stack is NULL");

    st = stack_create();

    verify(stack_stackUpMany(st, v, len) == false, "Should return false because the vector is NULL");

    v = (any *)calloc(len, sizeof(any));

    verify(stack_stackUpMany(st, v, 0) == false, "Should return false because len is not a positive value");


    for (int i = 1; i <= 2; i++)
    {
        stack_stackUp(st, i);
    }

    stack_print(st);

    for (int j = 0; j < len; j++) {
        v[j] = j + 3;
    }

    verify(stack_stackUpMany(st, v, len) == true, "Should return true because the inserction was successful");
    verify(stack_size(st) == 5, "The new stack size should be equals 5");

    any top;
    stack_top(st, &top);

    verify(top == 5, "The last element of the stack should be equals 5");

    stack_print(st);

    any v2[3] = {6, 7, 8};

    verify(stack_stackUpMany(st, v2, len) == true, "Should return true because the expansion was successful");
    verify(stack_size(st) == 8, "The new stack size should be equals 8");

    stack_top(st, &top);

    verify(top == 8, "The last element of the stack should be equals 8");

    stack_print(st);

    stack_destroy(&st);
    free(v);
}

void test_stack_toString() {
    printf("/***********************************************\n");
    printf("TEST: TO STRING\n");
    printf("/***********************************************\n\n");
    Stack *st = NULL;

    char str[200];

    verify(stack_toString(st, str) == false, "Should return false because the Stack is NULL");

    st = stack_create();

    verify(stack_toString(st, str) == false, "Should return false because the Stack is empty");

    any v[5] = {0, -6, 25, 3, -10};

    stack_stackUpMany(st, v, 5);

    verify(stack_toString(st, str) == true, "Should return true because the conversion was successful");
    
    verify(strcmp(str, "[ 0 | -6 | 25 | 3 | -10 ]"), "The spected result is: [ 0 | -6 | 25 | 3 | -10 ]");

    stack_destroy(&st);


}
