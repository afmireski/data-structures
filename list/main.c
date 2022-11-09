/***********************************************
| * author: André Felipe Mireski
| * filename: main.c
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <list.h>

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
