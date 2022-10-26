/***********************************************
| * author: André Felipe Mireski
| * filename: stack.h
************************************************/

#ifndef _STACK_H_
#define _STACK_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


typedef int any;
/***********************************************
| STRUCTS
************************************************/
typedef struct stack Stack;

/***********************************************
| ACTIONS
************************************************/

Stack* stack_create();
void stack_destroy(Stack** address);
bool stack_stackUp(Stack* st, any element);
bool stack_unstack(Stack* st, any* output);
bool stack_top(Stack* st, any* output);
bool stack_isEmpty(Stack* st);
void stack_print(Stack* st);
int stack_size(Stack* st);
Stack* stack_clone(Stack* st);
bool stack_revert(Stack* st);
bool stack_stackUpMany(Stack* st, any* vector, int len);
bool stack_toString(Stack* st, char* str);

#endif
