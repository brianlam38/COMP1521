#include <stdio.h>
#include <stdlib.h>

#include "List.h"

#define LINE "*******************************\n"

void test_create_destroy(void);
void print_test_append(void);


int main(int argc, char* argv[])
{
    printf("Testing lists...\n");

    print_test_append();

    printf("list tests PASSED.\n");
    return 0;
}

void print_test_append(void)
{
    
    printf(LINE);
    printf("Testing print_list() with append node...\n\n");
    
    struct node* list = NULL;


    list = append_node(list, "hi!");
    list = append_node(list, "I am");
    list = append_node(list, "a");
    list = append_node(list, "test");
    list = append_node(list, "on linked list debugging!");

    // now we should have a populated list
    print_list(list);

    destroy_list(list);
    printf("\nprint_list (append) PASSED.\n");
    printf(LINE);
}
