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
void test_list_indexOf();
void test_list_returnAt();
void test_list_replace();
void test_list_toString();

void fillList(List *l, any end);

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
    // test_list_remove();
    printf("\n\n");
    // test_list_indexOf();
    printf("\n\n");
    // test_list_returnAt();
    printf("\n\n");
    // test_list_replace();
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

void fillList(List *l, any end)
{
    for (int i = 1; i <= end; i++)
    {
        list_append(l, i);
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
    list_print(l);

    element = 2;

    verify(list_append(l, element) == true, "Should return 'true' and add a new element (2)");
    list_print(l);

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

void test_list_insert()
{
    printf("/***********************************************\n");
    printf("TEST: INSERT\n");
    printf("/***********************************************\n\n");

    List *l = NULL;
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

void test_list_removeAt()
{
    printf("/***********************************************\n");
    printf("TEST: REMOVE AT\n");
    printf("/***********************************************\n\n");

    List *l = NULL;
    any output;

    verify(list_removeAt(l, -1, &output) == false, "Should return 'false' because the list is NULL");

    l = list_create();

    verify(list_removeAt(l, -1, &output) == false, "Should return 'false' because the list is empty");

    for (int i = 1; i <= 5; i++)
    {
        list_append(l, i);
    }

    verify(list_removeAt(l, -1, &output) == false, "Should return 'false' because index is less than 0");

    verify(list_removeAt(l, 5, &output) == false, "Should return 'false' because index is greather than 4");

    // list_print(l);
    verify(list_removeAt(l, 0, &output) == true, "Should return 'true' because the first element was removed");
    verify(output == 1, "The removed element should be equals 1");
    verify(list_size(l) == 4, "The list should contains 4 elements after remotion");

    // list_print(l);
    verify(list_removeAt(l, 3, &output) == true, "Should return 'true' because the last element was removed");
    verify(output == 5, "The removed element should be equals 5");
    verify(list_size(l) == 3, "The list should contains 3 elements after remotion");

    // list_print(l);
    verify(list_removeAt(l, 1, &output) == true, "Should return 'true' because the middle element was removed");
    verify(output == 3, "The removed element should be equals 3");
    verify(list_size(l) == 2, "The list should contains 2 elements after remotion");

    // list_print(l);
    list_removeAt(l, 0, &output);
    list_removeAt(l, 0, &output);

    verify(list_isEmpty(l), "The list should be empty");

    list_destroy(&l);
}

void test_list_remove()
{
    printf("/***********************************************\n");
    printf("TEST: REMOVE \n");
    printf("/***********************************************\n\n");

    List *l = NULL;

    verify(list_remove(l, 0) == -1, "Should return '-1' because the list is NULL");

    l = list_create();

    verify(list_remove(l, 0) == -1, "Should return '-1' because the list is empty");

    for (int i = 1; i <= 5; i++)
    {
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

void test_list_indexOf()
{
    printf("/***********************************************\n");
    printf("TEST: INDEX OF\n");
    printf("/***********************************************\n\n");

    List *l = NULL;

    verify(list_indexOf(l, 0) == -1, "Should return '-1' because the list is NULL");

    l = list_create();

    verify(list_indexOf(l, 0) == -1, "Should return '-1' because the list is empty");

    fillList(l, 5);

    // list_print(l);
    verify(list_indexOf(l, -10) == -1, "Should return '-1' because the -10 is not in the list");

    verify(list_indexOf(l, 100) == -1, "Should return '-1' because the 100 is not in the list");

    verify(list_indexOf(l, 1) == 0, "Should return '0' because '1' is in this index");
    verify(list_indexOf(l, 5) == 4, "Should return '4' because '5' is in this index");
    verify(list_indexOf(l, 2) == 1, "Should return '1' because '1' is in this index");
    verify(list_indexOf(l, 3) == 2, "Should return '2' because '3' is in this index");
    verify(list_indexOf(l, 4) == 3, "Should return '3' because '4' is in this index");

    list_destroy(&l);
}

void test_list_returnAt()
{
    printf("/***********************************************\n");
    printf("TEST: RETURN AT\n");
    printf("/***********************************************\n\n");

    List *l = NULL;
    any output;

    verify(list_returnAt(l, -1, &output) == false, "Should return 'false' because the list is NULL");

    l = list_create();

    verify(list_returnAt(l, -1, &output) == false, "Should return 'false' because the list is empty");

    fillList(l, 5);

    verify(list_returnAt(l, -1, &output) == false, "Should return 'false' because index '-1' is out of range ");
    verify(list_returnAt(l, 5, &output) == false, "Should return 'false' because index '5' is out of range ");

    // list_print(l);
    verify(list_returnAt(l, 0, &output) == true && output == 1, "Should return 'true' and find '1' at index 0");
    verify(list_returnAt(l, 4, &output) == true && output == 5, "Should return 'true' and find '5' at index 4");
    verify(list_returnAt(l, 2, &output) == true && output == 3, "Should return 'true' and find '3' at index 2");
    verify(list_returnAt(l, 1, &output) == true && output == 2, "Should return 'true' and find '2' at index 1");
    verify(list_returnAt(l, 3, &output) == true && output == 4, "Should return 'true' and find '4' at index 3");

    list_destroy(&l);
}

void test_list_replace()
{
    printf("/***********************************************\n");
    printf("TEST: REPLACE\n");
    printf("/***********************************************\n\n");

    List *l = NULL;

    verify(list_replace(l, -1, -1) == false, "Should return 'false' because the list is NULL");

    l = list_create();

    verify(list_replace(l, -1, -1) == false, "Should return 'false' because the list is empty");

    fillList(l, 5);

    // list_print(l);
    verify(list_replace(l, -1, -1) == false, "Should return 'false' because the '-1' index is out of range'");
    verify(list_replace(l, 5, -1) == false, "Should return 'false' because the '5' index is out of range'");

    any output;

    verify(list_replace(l, 0, -1) == true, "Should return 'true' because the element at index 0 as change to -1");
    list_returnAt(l, 0, &output);
    verify(output == -1, "1 was changed to -1");

    verify(list_replace(l, 1, -2) == true, "Should return 'true' because the element at index 1 as change to -2");
    list_returnAt(l, 1, &output); 
    verify(output == -2, "2 was changed to -2");

    verify(list_replace(l, 2, -3) == true, "Should return 'true' because the element at index 2 as change to -3");
    list_returnAt(l, 2, &output);
    verify(output == -3, "3 was changed to -3");

    verify(list_replace(l, 3, -4) == true, "Should return 'true' because the element at index 3 as change to -4");
    list_returnAt(l, 3, &output);
    verify(output == -4, "4 was changed to -4");

    verify(list_replace(l, 4, -5) == true, "Should return 'true' because the element at index 4 as change to -5");
    list_returnAt(l, 4, &output);
    verify(output == -5, "5 was changed to -5");

    // list_print(l);

    list_destroy(&l);
}

void test_list_toString() {
    printf("/***********************************************\n");
    printf("TEST: TO STRING\n");
    printf("/***********************************************\n\n");

    List* l = NULL;

    char str[200];

    verify(list_toString(l, str) == false, "Should return 'false' because the list is NULL");

    l = list_create();

    verify(list_toString(l, str) == false, "Should return 'false' because the list is empty");

    fillList(l, 5);

    verify(list_toString(l, str) == true, "Should return 'true' because the list was converted to string");

    verify(strcmp(str, "[1, 2, 3, 4, 5]") == 0, "The generate string should be equals [1, 2, 3, 4, 5]");

    list_destroy(&l);
}
