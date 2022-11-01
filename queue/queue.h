/***********************************************
| * author: André Felipe Mireski
| * filename: queue.h
************************************************/

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef int any;
/***********************************************
| STRUCTS
************************************************/
typedef struct queue Queue;

/***********************************************
| ACTIONS
************************************************/
Queue* queue_create();
void queue_destroy(Queue** address);
bool queue_insert(Queue* q, any element);
bool queue_remove(Queue* q, any* output);
bool queue_getFirst(Queue* q, any* output);
bool queue_isEmpty(Queue* q);
int queue_size(Queue* q);
void queue_print(Queue* q);
Queue* queue_clone(Queue* q);
bool queue_toString(Queue* q, char* str);
bool queue_insertMany(Queue* q, any* vector, int len);

#endif
