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
void test_list_isEmpty();
void test_list_append();
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
    test_list_isEmpty();
    printf("\n\n");
    // test_list_append();
    printf("\n\n");
    // test_list_insert();
    printf("\n\n");
    // test_list_removeAt();
    printf("\n\n");
    // test_list_remove();
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



void test_list_create_and_destroy() {
    printf("/***********************************************\n");
    printf("TEST: CREATE AND DESTROY\n");
    printf("/***********************************************\n\n");

    List* l = list_create();

    verify(l != NULL, "Should create a new List");

    list_destroy(&l);

    verify(l == NULL, "Should destroy the List");
}
