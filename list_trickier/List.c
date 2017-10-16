#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "List.h"

// here is our node struct. 
struct node
{
	struct node* next;
	char data[5];
};


// create a node
struct node* create_node(char* value)
{
	
	// allocate heap memory to store 
	struct node* new_node = malloc(sizeof(struct node));

	if(new_node == NULL)
	{
		printf("%s: error: failed to allocate memory for new node.\n", __func__);
		return NULL;
	}


	// need to initialise our structs variables (just like any other variables!)
	new_node->next = NULL;
	strcpy(new_node->data, value);


	// since the node is in allocated memory, we can return a pointer to it safely
	return new_node;
}


// add a node to the end of the list
struct node* append_node(struct node* head, char* value)
{
	// empty list case
	if(head == NULL){
		head = create_node(value);
	
	// list is not empty...
	} else {
		
		// need to iterate to end of list
		struct node* curr = head;
		while(curr->next != NULL){
			curr = curr->next;
		}

		// now add node to end (our curr should be pointing to the last node)
		curr->next = create_node(value);
	}

	return head;
}


// clean up and free a single node
int destroy_node(struct node* node)
{
	if(node == NULL)
	{
		printf("%s: error: node pointer was NULL.\n", __func__);
		return -1;
	}

	free(node);
	return 0;
}


// clean up and destroy a list (this will clean/destroy each node in the list)
int destroy_list(struct node* list)
{
	if(list == NULL)
	{
		printf("%s: error: list pointer was NULL.\n", __func__);
		return -1;
	}

	// create a pointer to the head of our list ( that we can use to iterate through )
	
	struct node* curr = list;
    struct node* prev = NULL;

	while( curr != NULL)
	{	
		prev = curr;
		curr = curr->next;
		destroy_node(prev);
	}

	return 0;
}


void print_list(struct node* head)
{
	struct node* current = head;

	while(current != NULL){
		printf("[%s]->", current->data);
		current = current->next;
	}
	printf("[X]\n");
}
