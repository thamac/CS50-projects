/**************************************************/
/* Name: stacks.c                                 */
/* Purpose: Work out stacks and operations on it  */
/* Author: D.M.Meijer                             */
/**************************************************/

// Directives
#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Macros
#define CAPACITY 10
#define EMPTY 0

// STRUCT PROTOTYPES
typedef struct _VALUE
{
    int VALUE;
}
VALUE;

typedef struct _arr_stack
{
    VALUE array[CAPACITY];
    int top;
}
arr_stack;

typedef struct _sll_stack
{
    VALUE val;
    struct _sll_stack *next;
}
sll_stack;

// FUNCTION PROTOTYPES
// Create stack functions
arr_stack *create_arr_stack(arr_stack *s);
VALUE *create_VALUE(VALUE *val);
// Enqueue functions
void push_arr(arr_stack *s, VALUE *data);
sll_stack *push_sll(sll_stack *s, VALUE *data);
// Dequeue functions
void pop_arr(arr_stack *s);
void pop_sll(sll_stack *s);
// Check top element functions
void arr_top(arr_stack *s);
void sll_top(sll_stack *s);
// Check if stack is empty functions
bool arr_is_empty(arr_stack *s);
bool sll_is_empty(sll_stack *s);
// Check the size of the stack functions
int arr_size(arr_stack *s);
int sll_size(sll_stack *s);
// Print functions
void print_arr(arr_stack *s);
void print_sll_stack(sll_stack *s);
void print_sll(sll_stack *s, int counter);
// Clear memory and pointers functions
arr_stack *clr_mem_arr(arr_stack *s);
sll_stack *clr_mem_sll(sll_stack *s);
VALUE *clr_mem_val(VALUE *val, arr_stack *as, sll_stack *ls);

// setup main function
int main(void)
{
    // Initialize structs
    arr_stack *arr_s = NULL;
    sll_stack *sll_s = NULL;
    VALUE *v = NULL;

    // Create an array stack inside main
    arr_s = create_arr_stack(arr_s);

    // Create VALUE v to add data to the stacks
    v = create_VALUE(v);

    // Variables for main function
    int end = 1;
    int data;
    int option;

    // Main loop to keep the program alive
    while (end != 0)
    {
        // Option to select the switch case
        option = get_int("What do you want to do:\n 0 End program\n 1 enqueue array\n 2 enqueue linked list\n 3 pop array\n 4 pop linked list\n 5 top element array\n 6 top element linked list\n 7 check if array stack is empty\n 8 check if linked list stack is empty\n 9 check size of array stack\n10 check size of linked list stack\n11 print array stack\n12 print linked list stack\n13 clear memory for array stack\n14 clear memory for linked list stack\n15 clear memory for VALUE\nOption: ");

        switch (option)
        {
            case 0:
                end = 0;
                break;
            case 1:
                data = get_int("Input value: ");
                v->VALUE = data;
                push_arr(arr_s, v);
                break;
            case 2:
                data = get_int("Input value: ");
                v->VALUE = data;
                sll_s = push_sll(sll_s, v);
                break;
            case 3:
                pop_arr(arr_s);
                break;
            case 4:
                pop_sll(sll_s);
                break;
            case 5:
                arr_top(arr_s);
                break;
            case 6:
                sll_top(sll_s);
                break;
            case 7:
                if (arr_is_empty(arr_s))
                    printf("The array stack is empty!\n");
                else
                    printf("The array stack is not empty!\n");
                break;
            case 8:
                if (sll_is_empty(sll_s))
                    printf("The linked list stack is empty!\n");
                else
                    printf("The linked list stack is not empty!\n");
                break;
            case 9:
                data = arr_size(arr_s);
                printf("The size of the array stack is %d\n", data);
                break;
            case 10:
                data = sll_size(sll_s);
                printf("The size of the linked list stack is %d\n", data);
                break;
            case 11:
                print_arr(arr_s);
                break;
            case 12:
                print_sll_stack(sll_s);
                break;
            case 13:
                arr_s = clr_mem_arr(arr_s);
                break;
            case 14:
                sll_s = clr_mem_sll(sll_s);
                break;
            case 15:
                v = clr_mem_val(v, arr_s, sll_s);
                break;
        }
    }

    arr_s = clr_mem_arr(arr_s);
    sll_s = clr_mem_sll(sll_s);
    v = clr_mem_val(v, arr_s, sll_s);

    return 0;
}

// Create array stack
arr_stack *create_arr_stack(arr_stack *s)
{
    // Check if the array stack exists
    if (s != NULL)
        printf("The array stack already exists!\n");
    else
    {
        // Allocate memory for the array stack
        s = malloc(sizeof(arr_stack));
        if (s == NULL)
            printf("Error: memory was not allocated for array stack!\n");

        // Initialize the struct variable
        s->top = EMPTY;
    }
    return s;
}

// Create VALUE v
VALUE *create_VALUE(VALUE *val)
{
    // Check if VALUE v exists
    if (val != NULL)
        printf("VALUE v already exists!\n");
    else
    {
        // Allocate memory for VALUE v
        val = malloc(sizeof(VALUE));
        if (val == NULL)
            printf("Error: memory was not allocated for VALUE v!\n");
    }
    return val;
}

// Push: add new element to the top of the array stack
void push_arr(arr_stack *s, VALUE *data)
{
    // Check if the array stack is initialized
    if (s == NULL)
    {
        printf("Error: No array stack initialized!\n");
        return;
    }

    // Check if there is room in the array stack
    if (s->top == 9)
        printf("Array stack if full!\n");
    // Add the element to the top of the array stack
    else
    {
        int index = s->top + 1;
        s->array[index] = *data;
        s->top++;
        printf("Value %d is indexed at %d and the size of the stack is %d\n", s->array[index].VALUE, index, s->top);
    }
}

// Push: add new element to the top of the linked list stack
sll_stack *push_sll(sll_stack *s, VALUE *data)
{
    // Allocate memory for new element
    sll_stack *new = malloc(sizeof(sll_stack));
    if (new == NULL)
    {
        printf("Error: memory was not allocated for linked list stack\n");
        return s;
    }

    // Initialize the value data to the value of the linked list stack
    new->val = *data;

    // Check is there the linked list stack is empty and add new element to the start
    if (sll_is_empty(s))
    {
        new->next = s;
        s = new;
    }
    else
    {
        // Add the element to the end of the linked list stack
        for (sll_stack *current = s; current != NULL; current = current->next)
        {
            if (current->next == NULL)
            {
                current->next = new;
                new->next = NULL;
            }
        }
    }
    return s;
}

// Pop: remove element from the top of the array stack
void pop_arr(arr_stack *s)
{
    // Check if array stack is initialized
    if (s == NULL)
    {
        printf("Error: no array stack initialized!\n");
        return;
    }

    // Checks if the array stack is empty
    if (arr_is_empty(s))
        printf("Array stack is already empty!\n");
    // Removes the element that has been added last
    else
        s->top--;

}

// Pop: remove element from the top of the linked list stack
void pop_sll(sll_stack *s)
{
    // Check if linked list stack is emtpy
    if (sll_is_empty(s))
    {
        printf("Linked list stack is already emtpy!\n");
        return;
    }
    else
    {
        // Stores the previous linked list
        sll_stack *prev = NULL;

        // Removes the element that has been added last
        for (sll_stack *current = s; current != NULL; current = current->next)
        {
            if (current->next == NULL)
            {
                prev->next = current->next;
                current = prev;
            }
            prev = current;
        }
    }
}

// Top: returns top element of the array stack
void arr_top(arr_stack *s)
{
    // Checks if the array stack is initialized
    if (s == NULL)
        printf("No array stack initialized!\n");
    // Checks if the array stack is empty
    else
    {
        if (arr_is_empty(s))
            printf("There are no elements in the array stack\n");
        // Prints the value of the top element in the array stack
        else
        {
            int index = s->top;
            printf("the value of the element on top of the stack is %d\n", s->array[index].VALUE);
        }
    }
}

// Top: returns top element of the linked list stack
void sll_top(sll_stack *s)
{
    // Checks if the linked list is empty
    if (sll_is_empty(s))
            printf("There are no elements in the linked list stack\n");
    // Prints the value of the top element in the linked list stack
    else
    {
        for (sll_stack *current = s; current != NULL; current = current->next)
        {
            if (current->next == NULL)
                printf("The value of the element on top of the stack is %d\n", current->val.VALUE);
        }
    }
}

// is_emtpy: returns true if the array stack is empty
bool arr_is_empty(arr_stack *s)
{
    // Checks if the array stack is initialized
    if (s == NULL)
        {
            printf("No array stack initialized!\n");
        }
    else
        // Returns true if the array stack is empty else false
        if (s->top == EMPTY)
            return true;

    return false;
}

// is_emtpy: returns true if the linked list stack is empty
bool sll_is_empty(sll_stack *s)
{
    // Check if the linked list stack is empty and returns true
    if (s == NULL)
        return true;

    return false;
}

// size: returns the size of the array stack
int arr_size(arr_stack *s)
{
    // Check if array stack is initialized
    if (s == NULL)
        printf("No array stack initialized!\n");

    // return the size of the array stack
    return s->top;
}

// size: returns the size of the linked list stack
int sll_size(sll_stack *s)
{
    // Variable to keep the amount of elements in the linked list stack
    int count = 0;

    // Loop to go thru the linked lists
    for (sll_stack *current = s; current != NULL; current = current->next)
    {
        count++;
    }

    return count;
}

// Clear memory and danling pointers for array stack
arr_stack *clr_mem_arr(arr_stack *s)
{
    // Check if the array stack is initialized
    if (s == NULL)
        printf("No array stack initialized!\n");
    // Remove dangling pointers and free allocated memory
    else
    {
        s->top = EMPTY;
        free(s);
        s = NULL;
    }
    return s;
}

// Clear memory and danling pointers for linked lists stack
sll_stack *clr_mem_sll(sll_stack *s)
{
    // Check if the linked list is empyt
    if (!s)
        printf("The linked list stack is empty!\n");
    else
    {
        // Frees the memory of the elements of the linked list stack
        for (sll_stack *current = s, *temp; current != NULL; current = temp)
        {
            temp = current->next;
            free(current);
        }
    }
    return s = NULL;
}

// Clear memory and danling pointers for VALUE
VALUE *clr_mem_val(VALUE *val, arr_stack *as, sll_stack *ls)
{
    // Check if VALUE v exist
    if (val == NULL)
        printf("No VALUE initialized!\n");
    //Check if array stack is initialized and if linked list is empty
    else if (as != NULL && ls)
        printf("Cant clear VALUE: array stack initialized and linked list stack is not empty!\n");
    // Checks if array stack is initilized
    else if (as != NULL)
        printf("Cant clear VALUE: array stack initialized!\n");
    // Check if linked list stack is empty
    else if (ls)
        printf("Cant clear VALUE: linked list stack is not empty!\n");
    // Remove dangling pointer and free allocated memory
    else
    {
        free(val);
        val = NULL;
    }
    return val;
}

// Print array stack
void print_arr(arr_stack *s)
{
    // Check if the array stack is initialized
    if (s == NULL)
        printf("No array stack initialized!\n");
    else
    {
        // Check if the array stack is empty
        if (arr_is_empty(s))
        {
            printf("Array stack is empty!\n");
            return;
        }

        // Variable to print the elements of the stack queue
        int count = 0;

        // Print the element of the array stack in order
        for (int i = s->top; i > 0; i--)
        {
            printf("Index %d has the value %d on position %d\n", i, s->array[i].VALUE, count);
            count++;
        }
    }
}

// Print linked list stack
void print_sll_stack(sll_stack *s)
{
    // Check if the linked list stack is empty
    if (s == NULL)
        printf("Linked list stack is emtpy!\n");
    else
    {
        int count = 1;
        for (sll_stack *current = s; current != NULL; current = current->next)
            count++;
        // Call the recursive function to print the elements in reverse order
        print_sll(s, count);
    }
}

void print_sll(sll_stack *s, int counter)
{
    // Base condition to stop the recursive call
    if (s != NULL)
    {
        counter--;
        // Calls print_sll recursive for the next element in the linked list stack
        print_sll(s->next, counter);

        // Print the linked list stack
        printf("value %d is on position %d\n", s->val.VALUE, counter);
    }
}
