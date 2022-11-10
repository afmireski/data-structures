/***********************************************
| * author: André Felipe Mireski
| * filename: main.c
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"

void verify(int condition, char *message);

void test_list_create_and_destroy();
void test_list_append();
void test_list_isEmpty();
void test_list_insert();
void test_list_removeAt();
void test_list_remove();
void test_list_replace();
void test_list_indexOf();
void test_list_returnAt();
void test_list_toString();

int main()
{
    printf("/***********************************************\n");
    printf("LIST\n");
    printf("/***********************************************\n\n");
    // test_list_create_and_destroy();
    printf("\n\n");
    // test_list_append();
    printf("\n\n");
    // test_list_isEmpty();
    printf("\n\n");
    // test_list_insert();
    printf("\n\n");
    // test_list_removeAt();
    printf("\n\n");
    test_list_remove();
    printf("\n\n");
    // test_list_replace();
    printf("\n\n");
    // test_list_indexOf();
    printf("\n\n");
    // test_list_returnAt();
    printf("\n\n");
    // test_list_toString();
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

void test_list_create_and_destroy()
{
    printf("/***********************************************\n");
    printf("TEST: CREATE AND DESTROY\n");
    printf("/***********************************************\n\n");

    List *l = list_create();

    verify(l != NULL, "Should create a new List");

    list_destroy(&l);

    verify(l == NULL, "Should destroy the List");
}

void test_list_append()
{
    List *l = NULL;

    int element = 1;

    verify(list_append(l, element) == false, "Should return 'false' because the list is NULL");

    l = list_create();

    verify(list_append(l, element) == true, "Should return 'true' and add the first element (1)");
    // list_print(l);

    element = 2;

    verify(list_append(l, element) == true, "Should return 'true' and add a new element (2)");
    // list_print(l);

    verify(list_size(l) == 2, "The list should contain two elements");

    list_destroy(&l);
}

void test_list_isEmpty()
{
    printf("/***********************************************\n");
    printf("TEST: IS EMPTY\n");
    printf("/***********************************************\n\n");
    List *l = NULL;

    verify(list_isEmpty(l) == false, "Should return 'false' because the list is NULL");

    l = list_create();

    verify(list_isEmpty(l) == true, "Should return 'true' because the list is Empty");

    list_append(l, 1);

    verify(list_isEmpty(l) == false, "Should return 'false' because the list is not Empty");

    list_destroy(&l);
}

void test_list_insert() {
    printf("/***********************************************\n");
    printf("TEST: INSERT\n");
    printf("/***********************************************\n\n");

    List* l = NULL;
    any element = 3;

    verify(list_insert(l, element, -1) == false, "Should return 'false' because the list is empty");

    l = list_create();

    verify(list_insert(l, element, -1) == false, "Should return 'false' because index is less than 0");
    verify(list_insert(l, element, 11) == false, "Should return 'false' because index is greater than list size");

    verify(list_insert(l, element, 0) == true, "Should return 'true' because the first element was inserted");
    // list_print(l);

    element = 1;

    verify(list_insert(l, element, 0) == true, "Should return 'true' because 1 was inserted in the first position");
    // list_print(l);

    element = 5;

    verify(list_insert(l, element, 2) == true, "Should return 'true' because 5 was inserted in the last position");
    // list_print(l);

    element = 2;

    verify(list_insert(l, element, 1) == true, "Should return 'true' because 2 was inserted at index 1");
    // list_print(l);

    element = 4;

    verify(list_insert(l, element, 3) == true, "Should return 'true' because 4 was inserted at index 3");
    // list_print(l);

    verify(list_size(l) == 5, "The list should contain five elements");
    // list_print(l);

    list_destroy(&l);
}

void test_list_removeAt() {
    printf("/***********************************************\n");
    printf("TEST: REMOVE AT\n");
    printf("/***********************************************\n\n");
    
    List* l = NULL;
    any output;

    verify(list_removeAt(l, -1, &output) == false, "Should return 'false' because the list is NULL");

    l = list_create();

    verify(list_removeAt(l, -1, &output) == false, "Should return 'false' because the list is empty");

    for (int i = 1; i <= 5; i++) {
        list_append(l, i);
    }

    verify(list_removeAt(l, -1, &output) == false, "Should return 'false' because index is less than 0");

    verify(list_removeAt(l, 5, &output) == false, "Should return 'false' because index is greather than 4");

    list_print(l);
    verify(list_removeAt(l, 0, &output) == true, "Should return 'true' because the first element was removed");
    verify(output == 1, "The removed element should be equals 1");
    verify(list_size(l) == 4, "The list should contains 4 elements after remotion");

    list_print(l);
    verify(list_removeAt(l, 3, &output) == true, "Should return 'true' because the last element was removed");
    verify(output == 5, "The removed element should be equals 5");
    verify(list_size(l) == 3, "The list should contains 3 elements after remotion");
    
    list_print(l);
    verify(list_removeAt(l, 1, &output) == true, "Should return 'true' because the middle element was removed");
    verify(output == 3, "The removed element should be equals 3");
    verify(list_size(l) == 2, "The list should contains 2 elements after remotion");

    list_removeAt(l, 0, &output);
    list_removeAt(l, 0, &output);
    
    verify(list_isEmpty(l), "The list should be empty");

    list_destroy(&l);
}

void test_list_remove() {
    printf("/***********************************************\n");
    printf("TEST: REMOVE \n");
    printf("/***********************************************\n\n");
    
    List* l = NULL;

    verify(list_remove(l, 0) == -1, "Should return '-1' because the list is NULL");

    l = list_create();

    verify(list_remove(l, 0) == -1, "Should return '-1' because the list is empty");

    for (int i = 1; i <= 5; i++) {
        list_append(l, i);
    }

    verify(list_remove(l, 0) == -1, "Should return '-1' because 0 is not in the list");

    // list_print(l);
    verify(list_remove(l, 1) == 0, "Should return '0' because the first element was removed");    
    verify(list_size(l) == 4, "The list should contains 4 elements after remotion");

    // list_print(l);
    verify(list_remove(l, 5) == 3, "Should return '3' because the last element was removed");
    verify(list_size(l) == 3, "The list should contains 3 elements after remotion");
    
    // list_print(l);
    verify(list_remove(l, 3) == 1, "Should return '1' because the middle element was removed");
    verify(list_size(l) == 2, "The list should contains 2 elements after remotion");

    // list_print(l);
    list_remove(l, 4);
    list_remove(l, 2);
    
    verify(list_isEmpty(l), "The list should be empty");

    list_destroy(&l);
}

