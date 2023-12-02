// Stack.c: Source file for stack implementation using linked-list in C

#include "Stack.h" // Include header file

// Initialize a stack
void stack_init(Stack *stack)
{
    stack->size = 0;
    stack->top = NULL;
}

// Check if a stack is full
bool stack_full(Stack *stack)
{
    return 0;
}

// Check if a stack is empty
bool stack_empty(Stack *stack)
{
    return (stack->size == 0 || stack->top == NULL);
}

// Push an element to a stack
bool push_stack(Stack *stack, ELEMENT_TYPE element)
{
    if (!stack_full(stack)) // If the stack is not full
    {
        StackNode *ptr = (StackNode *)malloc(sizeof(StackNode));
        ptr->data = element;
        ptr->next = stack->top;
        stack->top = ptr;
        stack->size++;
    }
    else              // If the stack is full
        return false; // Return false to indicate failure
}

// Pop an element from a stack
bool pop_stack(ELEMENT_TYPE *element, Stack *stack)
{
    if (!stack_empty(stack)) // If the stack is not empty
    {
        StackNode *ptr = NULL;
        *element = stack->top->data;
        stack->size--;
        ptr = stack->top;
        stack->top = stack->top->next;
        free(ptr);
    }
    else              // If the stack is empty
        return false; // Return false to indicate failure
}

// Get the top element of a stack
bool stack_top(Stack *stack, ELEMENT_TYPE *element)
{
    if (!stack_empty(stack)) // If the stack is not empty
    {
        *element = stack->top->data;
    }
    else              // If the stack is empty
        return false; // Return false to indicate failure
}

// Traverse a stack and apply a function to each element
void traverse_stack(Stack *stack, void (*func)(ELEMENT_TYPE))
{
    StackNode *ptr = stack->top;
    while (ptr)
    {
        func(ptr->data);
        ptr= ptr->next;
    }
}

// Get the size of a stack
u32 size_stack(Stack *stack)
{
    return stack->size;
}

// Clear a stack
void clear_stack(Stack *stack)
{
    StackNode *ptr = NULL;
    while (stack->top)
    {
        ptr = stack->top;
        stack->top = stack->top->next;
        stack->size--;
        free(ptr);
    }
}
