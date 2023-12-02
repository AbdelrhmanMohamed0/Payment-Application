// List.h: Header file for List implementation using linked-list in C

#ifndef LIST_H // Include guard to prevent multiple inclusion
#define LIST_H

#include <stdbool.h> // For bool type
#include"../../Payment_System/Server/server.h"
#include "../Global/global.h"
#include"../Stack/Stack.h"
typedef unsigned int u32; // Alias for unsigned int

// Structure for LIST
typedef struct list_node
{
    ELEMENT_TYPE data;
    struct list_node *next;
    struct list_node *previous;
} List_Node;

typedef struct list
{
    List_Node *head, *current;
    int size, current_pos;
} List;


// Function prototypes

// Initialize the list
void list_init(List *plist);

// Check if a list is full
bool list_full(List *plist);

// Check if a list is empty
bool list_empty(List *plist);

// insert an element to the list
bool insert_list(List *plist, ELEMENT_TYPE element, int pos);

// delete an element from the list
bool delete_list(List *plist, ELEMENT_TYPE *element, int pos);

// Get element from the list
bool retrieve_list(List *plist, ELEMENT_TYPE *element, int pos);

// Replace an element from the list
bool replace_list(List *plist, ELEMENT_TYPE element, int pos);

// Traverse the list as queue and apply a function to each element
void traverse_list_as_queue(List *plist, void (*func)(ELEMENT_TYPE));

// Traverse the list as stack and apply a function to each element
void traverse_list_as_stack(List *plist, void (*func)(ELEMENT_TYPE));

// Get the size of the list
u32 size_list(List *plist);

// Clear the list
void clear_list(List *plist);

int search_list_for_accountData(List *plist, char *pan);
Stack *create_stack_from_list(List *plist);
int search_list_for_transactionData(List *plist, char *pan);

#endif
