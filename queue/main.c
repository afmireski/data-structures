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

int main()
{
    printf("/***********************************************\n");
    printf("QUEUE\n");
    printf("/***********************************************\n\n");
    test_queue_create_and_destroy();
    printf("\n\n");
    test_queue_insert();
    printf("\n\n");
    test_queue_remove();
    printf("\n\n");
    test_queue_clone();
    printf("\n\n");
    test_queue_toString();
    printf("\n\n");
    test_queue_insertUpMany();
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

void test_queue_create_and_destroy()
{
    printf("/***********************************************\n");
    printf("TEST: CREATE AND DESTROY\n");
    printf("/***********************************************\n\n");

    Queue *q = queue_create();
    verify(q != NULL, "Should create a new Queue");

    queue_destroy(&q);
    verify(q == NULL, "Should destroy the Queue");
}

void test_queue_insert()
{
    printf("/***********************************************\n");
    printf("TEST: INSERT\n");
    printf("/***********************************************\n\n");
    Queue *q = NULL;

    verify(queue_insert(q, 0) == false, "Should return false because the Queue is NULL");

    q = queue_create();

    verify(queue_insert(q, 1) == true, "Should return true because a single element was inserted");

    for (int i = 2; i <= 3; i++)
    {
        queue_insert(q, i);
    }
    queue_print(q);

    verify(queue_size(q) == 3, "Queue size should be equals 3");

    queue_destroy(&q);
}

void test_queue_remove()
{
    printf("/***********************************************\n");
    printf("TEST: REMOVE\n");
    printf("/***********************************************\n\n");

    Queue *q = NULL;
    any output;

    verify(queue_remove(q, &output) == false, "Should return false because the Queue is NULL");

    q = queue_create();

    verify(queue_remove(q, &output) == false, "Should return false because the Queue is empty");

    for (int i = 1; i <= 3; i++)
    {
        queue_insert(q, i);
    }

    verify(queue_remove(q, &output) == true, "Should return true because a element was removed");
    verify(output == 1, "The removed element should be equal 1");
    verify(queue_size(q) == 2, "Queue new size should be equals 2");

    queue_destroy(&q);
}

void test_queue_clone()
{
    printf("/***********************************************\n");
    printf("TEST: CLONE\n");
    printf("/***********************************************\n\n");

    Queue *q = NULL;

    verify(queue_clone(q) == NULL, "Should return NULL because the Queue is NULL");

    q = queue_create();

    verify(queue_clone(q) == NULL, "Should return NULL because the Queue is empty");

    for (int i = 1; i <= 3; i++)
    {
        queue_insert(q, i);
    }

    Queue *q2 = queue_clone(q);

    verify(q2 != NULL, "Should return a Queue pointer because the Queue was cloned");

    queue_print(q);
    queue_print(q2);

    any first1;
    any first2;

    queue_getFirst(q, &first1);
    queue_getFirst(q2, &first2);

    verify(first1 == first2, "Both queues should be same begin");

    queue_destroy(&q);
    queue_destroy(&q2);
}

void test_queue_toString()
{
    printf("/***********************************************\n");
    printf("TEST: TO STRING\n");
    printf("/***********************************************\n\n");

    Queue *q = NULL;
    char str[100];

    verify(queue_toString(q, str) == false, "Should return false because the Queue is NULL");

    q = queue_create();

    verify(queue_toString(q, str) == false, "Should return false because the Queue is empty");

    for (int i = 1; i <= 3; i++)
    {
        queue_insert(q, i);
    }

    verify(queue_toString(q, str) == true, "Should return true because the Queue was converted to string");

    verify(strcmp(str, "| 1, 2, 3") == 0, "The generated string should be equals \"| 1, 2, 3\"");

    queue_destroy(&q);
}

void test_queue_insertUpMany()
{
    printf("/***********************************************\n");
    printf("TEST: INSERT MANY\n");
    printf("/***********************************************\n\n");
    Queue *q = NULL;

    verify(queue_insertMany(q, NULL, -1) == false, "Should return false because the Queue is NULL");

    q = queue_create();

    verify(queue_insertMany(q, NULL, -1) == false, "Should return false because vector is NULL");

    int len = 3;

    any v1[3] = {1, 2, 3};
    any v2[3] = {4, 5, 6};

    verify(queue_insertMany(q, v1, -1) == false, "Should return false because len is not greater than 0");

    verify(queue_insertMany(q, v1, len) == true, "Should return true because 3 new elements were inserted");

    // queue_print(q);
    verify(queue_size(q) == 3, "Queue size should be equals 3");

    verify(queue_insertMany(q, v2, len) == true, "Should return true because 3 new elements were inserted");

    // queue_print(q);
    verify(queue_size(q) == 6, "Queue size should be equals 6");

    queue_destroy(&q);
}
