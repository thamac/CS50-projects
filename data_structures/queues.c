/**************************************************/
/* Name: queues.c                                 */
/* Purpose: Work out queues and operations on it  */
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
// VALUE struct
typedef struct _VALUE
{
    int VALUE;
}
VALUE;

// Array queue struct
typedef struct _arr_queue
{
    VALUE array[CAPACITY];
    int front;
    int size;
}
arr_queue;

// doubly linked list queue struct
typedef struct _dll_queue
{
    VALUE val;
    struct _dll_queue *prev;
    struct _dll_queue *next;
}
dll_queue;

// Initialize structs globally
arr_queue *arr_q = NULL;
dll_queue *dll_q = NULL;
VALUE *v = NULL;

// FUNCTION PROTOTYPES
// Create queue functions
void create_arr_queue(void);
void create_VALUE(void);
// Enqueue functions
void enqueue_arr(VALUE *data);
void enqueue_dll(VALUE *data);
// Dequeue functions
void dequeue_arr(void);
void dequeue_dll(void);
// Peek functions
void peek_arr(void);
void peek_dll(void);
// Rear functions
void rear_arr(void);
void rear_dll(void);
// Is full funcion
bool arr_is_full(void);
// Is empty function
bool arr_is_empty(void);
bool dll_is_null(void);
// Clear memory
arr_queue *clr_mem_arr(void);
dll_queue *clr_mem_dll(void);
VALUE *clr_mem_val(void);
void clr_mem_end(void);
// Print functions
void print_arr(void);
void print_dll(void);

int main(void)
{
    create_arr_queue();

    int end = 1;
    int data;
    int option;

    while(end != 0)
    {
        option = get_int("What do you want to do:\n0 for ending program\n1 enqueue arr_queue\n2 dequeue arr_queue\n3 peak arr_queue\n4 rear arr_queue\n5 check if arr_queue is full\n6 check if arr_queue is empty\n7 print arr_queue\n8 enqueue dll_queue\n9 dequeue dll_queue\n10 peak arr_queue\n11 rear arr_queue\n12 check if dll_queue is empty\n17 print dll_queue\n18 clear array memory\n19 clear linked list memory\n20 clear VALUE memory\nOption: ");

        switch(option)
        {
            case 0:
                end = 0;
                break;
            case 1:
                data = get_int("Input value: ");
                if (v == NULL)
                    printf("No VALUE initialized!\n");
                else
                    v->VALUE = data;
                enqueue_arr(v);
                break;
            case 2:
                dequeue_arr();
                break;
            case 3:
                peek_arr();
                break;
            case 4:
                rear_arr();
                break;
            case 5:
                if (arr_is_full())
                    printf("All the %d elements are full of the array queue\n", arr_q->size);
                else
                    printf("There are stil %d elements free of the array queue\n", CAPACITY - arr_q->size);
                break;
            case 6:
                if (arr_is_empty())
                    printf("The array queue is empty\n");
                else
                    printf("There are %d elements in line of the array queue\n", arr_q->size);
                break;
            case 7:
                print_arr();
                break;
            case 8:
                data = get_int("Input value: ");
                if (v == NULL)
                    printf("No VALUE initialized!\n");
                else
                    v->VALUE = data;
                enqueue_dll(v);
                break;
            case 9:
                dequeue_dll();
                break;
            case 10:
                peek_dll();
                break;
            case 11:
                rear_dll();
                break;
            case 12:
                if (dll_is_null())
                    printf("The linked list queue is empty\n");
                else
                    printf("The linked list queue is not empty\n");
                break;
            case 17:
                print_dll();
                break;
            case 18:
                arr_q = clr_mem_arr();
                break;
            case 19:
                dll_q = clr_mem_dll();
                break;
            case 20:
                v = clr_mem_val();
                break;
        }
    }

    clr_mem_end();

    return 0;
}

// Create array queue
void create_arr_queue(void)
{
    // Check if the array queue exists
    if (arr_q != NULL)
        printf("The array queue already exists!\n");
    else
    {
        // Allocate memory and initialize the array queue
        arr_q = malloc(sizeof(arr_queue));
        if (arr_q == NULL)
        {
            printf("Error: memory was not allocated for array queue\n");
            return;
        }

        // Initialize linked lists struct variables
        arr_q->front = EMPTY;
        arr_q->size = EMPTY;
    }
    create_VALUE();
}

// Create VALUE v
void create_VALUE(void)
{
    // Check if VALUE v exists
    if (v != NULL)
        printf("VALUE v already exists!\n");
    else
    {
        // Allocate memory for struct VALUE
        v = malloc(sizeof(VALUE));
        if (v == NULL)
        {
            printf("Error: memory was not allocated for VALUE v\n");
            return;
        }
    }
}

// Enqueue: add element to the end of an array queue
void enqueue_arr(VALUE *data)
{
    // Checks if array queue is initialized
    if (arr_q == NULL)
    {
        printf("Error: No array queue initialized!\n");
        return;
    }

    // Checks if there is room in the array queue
    if (arr_q->size > CAPACITY)
        printf("Array queue is full!\n");
    // Adds element to the queue in the correct order
    else
    {
        int index = (arr_q->front + arr_q->size) % CAPACITY;
        arr_q->array[index] = *data;
        arr_q->size++;
        printf("index = %d and size = %d\n", index, arr_q->size);
    }
}

// Enqueue: add element to the end of a linked list queue
void enqueue_dll(VALUE *data)
{
    // Allocate memory for new element
    dll_queue *new = malloc(sizeof(dll_queue));
    if (new == NULL)
    {
        printf("Error: memory was not allocated for array queue\n");
        return;
    }

    // Initialize the value data to the value of the linked list
    new->val = *data;

    // Checks if there are elements in the linked list queue and add new element to the begin
    if (dll_is_null())
    {
        new->next = dll_q;
        new->prev = NULL;
        dll_q = new;
    }
    // Adds the element to the end of the linked list queue
    else
    {
        for (dll_queue *current = dll_q; current != NULL; current = current->next)
        {
            if (current->next == NULL)
            {
                current->next = new;
                new->prev = current;
                new->next = NULL;
            }
        }
    }
}

// Dequeue: remove element from the front of an array queue
void dequeue_arr(void)
{
    // Checks if array queue is initialized
    if (arr_q == NULL)
    {
        printf("Error: no array queue initialized!\n");
        return;
    }

    // Checks if the array queue is empty
    if (arr_is_empty())
        printf("Array queue is already empty!\n");
    // Removes the element that been added first
    else
    {
        arr_q->size--;
        arr_q->front++;
        arr_q->front %= CAPACITY;
    }
}

// Dequeue: remove element from the front of a linked list queue
void dequeue_dll(void)
{
    // Checks if the linked list queue is empty
    if (dll_is_null())
    {
        printf("Linked list queue is already emtpy!\n");
        return;
    }
    // Removes the element that been added first
    else
    {
        dll_queue *temp = dll_q->next;
        // Check if the elements is the only element in the linked list queue
        if (temp != NULL)
            temp->prev = dll_q->prev;
        free(dll_q);
        dll_q = temp;
    }
}

// Peek or front: acquires the data element at the front of the array queue without deleting it
void peek_arr(void)
{
    // Checks if array queue is initialized
    if (arr_q == NULL)
        printf("No queue initialized!\n");
    else
    {
        // Checks if the array queue is empty
        if (arr_is_empty())
            printf("There are no elements in the array queue\n");
        // Prints the value of the first element in the array queue
        else
            printf("The value of the element at the front of the array queue is %d\n", arr_q->array[arr_q->front].VALUE);
    }
}

// Peek or front: acquires the data element at the front of the linked list queue without deleting it
void peek_dll(void)
{
    // Checks if the linked list queue is empty
    if (dll_is_null())
        printf("There are no elements is the linked list queue!\n");
    // Prints the value of the first element in the linked list queue
    else
        printf("The value of the element at the front of the linked list queue is %d\n", dll_q->val.VALUE);
}

// Rear: acquires the data element at the rear of the array queue without deleting it
void rear_arr(void)
{
    // Checks if array queue is initialized
    if (arr_q == NULL)
        printf("No queue initialized!\n");
    else
    {
        // Checks if the array queue is empty
        if (arr_is_empty())
            printf("There are no elements in the array queue\n");
        // Prints the value of the last element in the array queue
        else
        {
            int index = (arr_q->front + arr_q->size - 1) % CAPACITY;
            printf("The value of the element at the rear of the array queue is %d\n", arr_q->array[index].VALUE);
        }
    }
}

// Rear: acquires the data element at the rear of the array queue without deleting it
void rear_dll(void)
{
    // Checks if the linked list queue is empty
    if (dll_is_null())
        printf("There are no elements is the linked list queue!\n");
    // Prints the value of the last element in the linked list queue
    for (dll_queue *current = dll_q; current != NULL; current = current->next)
    {
        if (current->next == NULL)
            printf("The value of the element at the rear of the linked list is %d\n", current->val.VALUE);
    }
}

// is_full: checks if the array queue is full
bool arr_is_full(void)
{
    // Checks if array queue is initialize
    if (arr_q == NULL)
        printf("No queue initialized!\n");
    else
        // Returns true if the array queue is full
        if (arr_q->size == CAPACITY)
            return true;

    return false;
}

// is_null: check if the array queue is empty
bool arr_is_empty(void)
{
    // Checks if array queue is initialize
    if (arr_q == NULL)
        printf("No queue initialized!\n");
    else
        // Returns true if the array queue is empty
        if (arr_q->size == EMPTY)
            return true;

    return false;
}

// is_null: check if the linked list queue is empty
bool dll_is_null(void)
{
    // Checks if the linked list is empty and returns true
    if (dll_q == NULL)
        return true;

    return false;
}

// Clear memory and danling pointers for array queue
arr_queue *clr_mem_arr(void)
{
    // Checks if array queue is initialize
    if (arr_q == NULL)
        printf("No array queue initialized!\n");
    // Removes dangling pointers and free the allocated memory
    else
    {
        arr_q->front = EMPTY;
        arr_q->size = EMPTY;
        free(arr_q);
        arr_q = NULL;
    }

    return arr_q;
}

// Clear memory and danling pointers for linked lists queue
dll_queue *clr_mem_dll(void)
{
    // Checks if the linked list queue is empty
    if (!dll_q)
        printf("The linked list are empty!\n");
    else
    {
        // Removes dangling pointers and free the allocated memory
        for (dll_queue *current = dll_q; current != NULL; current = current->next)
        {
            free(current);
        }
        dll_q = NULL;
    }

    return dll_q;
}

// Clear memory and danling pointers for VALUE
VALUE *clr_mem_val(void)
{
    // Check if VALUE v exists
    if (v == NULL)
        printf("No VALUE initialized!\n");
    else if (arr_q != NULL && dll_q)
        printf("Cant clear VALUE: Array queue initialized and Linked list queue is not empty!\n");
    // Checks if array queue is initialize
    else if (arr_q != NULL)
        printf("Cant clear VALUE: Array queue initialized!\n");
    // Checks if the linked list queue is empty
    else if (dll_q)
        printf("Cant clear VALUE: Linked list is not empty!\n");
    // Removes dangling pointers and free allocated memory
    else
    {
        free(v);
        v = NULL;
    }

    return v;
}

// Clear memory and danling pointers for both queues and VALUE
void clr_mem_end(void)
{
    clr_mem_arr();
    clr_mem_dll();
    clr_mem_val();
}

// print array queue
void print_arr(void)
{
    // Checks if array queue is initialize
    if (arr_q == NULL)
        printf("No array queue initialized!\n");
    else
    {
        // Check if the array queue is empty
        if (arr_is_empty())
        {
            printf("Array queue is empty!\n");
            return;
        }

        // Variables to print the elements of the array queue
        int len = arr_q->front + arr_q->size;
        int count = 1;

        // Print the element of the array queue in order
        for (int i = arr_q->front; i < len; i++)
        {
            printf("index %d has value %d on position %d\n", i % CAPACITY, arr_q->array[i % CAPACITY].VALUE, count);
            count++;
        }
    }
}

// print linked list queue
void print_dll(void)
{
    // Check if the linked list queue is empty
    if (dll_q == NULL)
    {
        printf("Linked list queue is empty!\n");
        return;
    }
    // Print the elements of the linked list queue in order
    else
    {
        for (dll_queue *current = dll_q; current != NULL; current = current->next)
        {
            printf("%d\n", current->val.VALUE);
        }
    }
}
