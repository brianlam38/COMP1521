#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

struct node* create_node(char* value);
struct node* append_node(struct node* list, char* value);

int sum_nodes(struct node* head); 

int destroy_node(struct node* node);
int destroy_list(struct node* list);

void print_list(struct node* head);

#endif
