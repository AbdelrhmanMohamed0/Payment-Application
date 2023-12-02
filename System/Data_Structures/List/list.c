// List.c: Source file for list implementation using linked_list in C

#include "list.h"   // Include header file
#include <stdio.h>  // For input/output functions
#include <stdlib.h> // For exit function
// Initialize the list
void list_init(List *plist)
{
    plist->size = 0;
    plist->current_pos = -1;
    plist->head = NULL;
    plist->current = NULL;
}

// Check if a list is full
bool list_full(List *plist)
{
    return (false);
}

// Check if a list is empty
bool list_empty(List *plist)
{
    return (!plist->size);
}

// insert an element to the list
bool insert_list(List *plist, ELEMENT_TYPE element, int pos)
{
    if ((pos < 0) || (pos > (plist->size + 1)) || list_full(plist))
    {
        return false;
    }
    List_Node *ptr = (List_Node *)malloc(sizeof(List_Node));
    ptr->data = element;
    ptr->next = NULL;
    ptr->previous = NULL;
    if (pos == 0)
    {
        ptr->next = plist->head;
        if (plist->head)
        {
            plist->head->previous = ptr;
        }
        plist->head = ptr;
        plist->current = plist->head;
        plist->current_pos = 0;
        ptr->previous = NULL;
    }
    else
    {
        if (pos <= plist->current_pos)
        {
            while (plist->current_pos != pos)
            {
                plist->current = plist->current->previous;
                ptr->previous = plist->current->previous;
                plist->current->previous = ptr;
                ptr->next = plist->current;
                plist->current_pos--;
            }
            plist->current = ptr;
            plist->current->previous->next = ptr;
        }
        else
        {
            while (plist->current_pos != pos)
            {
                if (!(plist->current->next))
                {
                    ptr->next = NULL;
                    ptr->previous = plist->current;
                    plist->current->next = ptr;
                    plist->current = ptr;
                }
                else
                {
                    if (plist->current_pos == pos - 1)
                    {
                        ptr->next = plist->current->next;
                        plist->current->next = ptr;
                        ptr->previous = plist->current;
                        plist->current = ptr;
                        if (pos != plist->size + 1)
                            plist->current->next->previous = ptr;
                    }
                    else
                    {
                        plist->current = plist->current->next;
                    }
                }
                plist->current_pos++;
            }
        }
    }
    plist->size++;
    return true;
}

// delete an element from the list
bool delete_list(List *plist, ELEMENT_TYPE *element, int pos)
{
    if (pos < 0 || pos >= plist->size || list_empty(plist))
    {
        return false;
    }
    if (pos == 0)
    {
        plist->current = plist->head;
        *element = plist->current->data;
        plist->head = plist->current->next;
        free(plist->current);
        plist->current = plist->head;
        plist->current_pos = 0;
    }
    else
    {
        List_Node *ptr = NULL;
        while (plist->current_pos != pos)
        {
            if (pos <= plist->current_pos)
            {
                plist->current = plist->current->previous;
                plist->current_pos--;
            }
            else
            {
                plist->current = plist->current->next;
                plist->current_pos++;
            }
        }
        *element = plist->current->data;
        ptr = plist->current->previous;
        ptr->next = plist->current->next;
        if (plist->current->next)
            ptr = plist->current->next;
        {
            ptr->previous = plist->current->previous;
        }
        free(plist->current);
        plist->current = ptr;
        plist->current_pos = pos - 1;
    }
    plist->size--;
    return true;
}

// Get element from the list
bool retrieve_list(List *plist, ELEMENT_TYPE *element, int pos)
{
    if (pos < 0 || pos >= plist->size || list_empty(plist))
    {
        return false;
    }
    else
    {
        if (pos >= plist->current_pos)
        {
            while (plist->current_pos != pos)
            {
                plist->current = plist->current->next;
                plist->current_pos++;
            }
            *element = plist->current->data;
        }
        else
        {
            while (plist->current_pos != pos)
            {
                plist->current = plist->current->previous;
                plist->current_pos--;
            }
            *element = plist->current->data;
        }
        return true;
    }
}
// Replace an element from the list at a given position.
bool replace_list(List *plist, ELEMENT_TYPE element, int pos)
{
    if ((pos < 0) || (pos >= plist->size) || list_empty(plist))
    {
        return false;
    }
    List_Node *ptr = plist->current;
    if (pos >= plist->current_pos)
    {
        for (int i = plist->current_pos; i < pos; i++)
        {
            ptr = ptr->next;
        }
        ptr->data = element;
    }
    else
    {
        for (int i = plist->current_pos; i > pos; i--)
        {
            ptr = ptr->previous;
        }
        ptr->data = element;
    }

    return true;
}
// Traverse a list as stack and apply a function to each element
void traverse_list_as_stack(List *plist, void (*func)(ELEMENT_TYPE))
{
    if (!list_empty(plist))
    {
        List_Node *ptr1 = plist->current;
        while (ptr1->next)
        {
            ptr1 = ptr1->next;
        }
        while (ptr1)
        {
            func(ptr1->data);
            ptr1 = ptr1->previous;
        }
    }
}

// Traverse a list as queue and apply a function to each element
void traverse_list_as_queue(List *plist, void (*func)(ELEMENT_TYPE))
{
    if (!list_empty(plist))
    {
        List_Node *ptr = plist->head;
        while (ptr)
        {
            func(ptr->data);
            ptr = ptr->next;
        }
    }
}

// Get the size of the list
u32 size_list(List *plist)
{
    return (plist->size);
}

// Clear the list

void clear_list(List *plist)
{
    plist->current = plist->head;
    while (plist->head)
    {
        plist->current = plist->head->next;
        free(plist->head);
        plist->head = plist->current;
    }
    plist->size = 0;
    plist->current_pos = -1;
    plist->current = NULL;
}

// A function to search a list from the tail to the head using a stack
int search_list_for_accountData(List *plist, char *pan) {
    // Create a stack from the list
    Stack *s = create_stack_from_list(plist);

    // Check if the stack is empty
    if (stack_empty(s)) {
        return -1;
    }

    // Create a variable to store the position
    int pos = size_list(plist) - 1;

    // Loop through the stack until it is empty or a match is found
    while (!stack_empty(s)) {
        // Pop the top element of the stack
        DataType data;
        pop_stack(&data.accountData,s);

        // Compare the primary account number of the popped element with the given pan
        if (strcmp(data.accountData.primaryAccountNumber, pan) == 0) {
            // A match is found, return the position
            return pos;
        }

        // Decrement the position
        pos--;
    }

    // No match is found, return -1
    return -1;
}
/*
// Function to search for a primary account number in the list and return the position of the struct 
int search_list_for_accountData(List *plist, char *pan) {
    // Check if the list is empty 
    if (list_empty(plist)) {
         return -1; 
         }

// Create a temporary pointer to traverse the list
List_Node *temp = plist->head;

// Create a variable to store the position
int pos = 0;

// Loop through the list until the end or a match is found
while (temp != NULL)
{
    // Compare the primary account number of the current node with the given pan
    if (strcmp(temp->data.accountData.primaryAccountNumber, pan) == 0)
    {
        // A match is found, return the position
        return pos;
    }

    // Move to the next node and increment the position
    temp = temp->next;
    pos++;
}

// No match is found, return -1
return -1;

}
*/

// A function to create a stack from a list
Stack *create_stack_from_list(List *plist) {
    // Check if the list is empty
    if (list_empty(plist)) {
        return NULL;
    }
    static Stack s ;
    // Create a new stack
    stack_init(&s);

    // Create a temporary pointer to traverse the list
    List_Node *temp = plist->head;

    // Loop through the list and push each node to the stack
    while (temp != NULL) {
        push_stack(&s, temp->data);
        temp = temp->next;
    }

    // Return the stack
    return &s;
}

// A function to search a list from the tail to the head using a stack
int search_list_for_transactionData(List *plist, char *pan) {
    // Create a stack from the list
    Stack *s = create_stack_from_list(plist);

    // Check if the stack is empty
    if (stack_empty(s)) {
        return -1;
    }

    // Create a variable to store the position
    int pos = size_list(plist) - 1;

    // Loop through the stack until it is empty or a match is found
    while (!stack_empty(s)) {
        // Pop the top element of the stack
        DataType data;
        pop_stack(&data.transactionData,s);

        // Compare the primary account number of the popped element with the given pan
        if (strcmp(data.transactionData.cardHolderData.primaryAccountNumber, pan) == 0) {
            // A match is found, return the position
            return pos;
        }

        // Decrement the position
        pos--;
    }

    // No match is found, return -1
    return -1;
}
