/***********************************************
| * author: André Felipe Mireski
| * filename: main.c
************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "queue.h"

void verify(int condition, char *message);

void test_queue_create_and_destroy();
void test_queue_insert();
void test_queue_remove();
void test_queue_getFirst();
void test_queue_isEmpty();
void test_queue_clone();
void test_queue_toString();
void test_queue_insertUpMany();

int main() {    
    printf("/***********************************************\n");
    printf("QUEUE\n");
    printf("/***********************************************\n\n");
    // test_queue_create_and_destroy();
    printf("\n\n");
    // test_queue_insert();
    
    
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

void test_queue_create_and_destroy() {
    printf("/***********************************************\n");
    printf("TEST: CREATE AND DESTROY\n");
    printf("/***********************************************\n\n");

    Queue* q = queue_create();
    verify(q != NULL, "Should create a new Queue");

    queue_destroy(&q);
    verify(q == NULL, "Should destroy the Queue");
}

void test_queue_insert() {
    printf("/***********************************************\n");
    printf("TEST: INSERT\n");
    printf("/***********************************************\n\n");
    Queue* q = NULL;

    verify(queue_insert(q, 0) == false, "Should return false because the Queue is NULL");

    q = queue_create();

    verify(queue_insert(q, 1) == true, "Should return true because a single element was inserted");

    for (int i = 2; i <= 3; i++) {
        queue_insert(q, i);
    }
    queue_print(q);

    verify(queue_size(q) == 3, "Queue size should be equals 3");

    queue_destroy(&q);
}