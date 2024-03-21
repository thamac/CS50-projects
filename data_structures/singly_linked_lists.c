/***********************************************************************/
/* Name: singly_linked_lists.c                                         */
/* Purpose: Work out singly linked lists and search and sort algoritms */
/* Author: D.M.Meijer                                                  */
/***********************************************************************/

// Directives
#include <stdbool.h>
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

// Struct prototype
typedef struct node
{
    int value;
    struct node *next;
}node;

// Struct
node *list = NULL;
node *sorted = NULL;

// Insert functions
void insert_start_node(int x);
void insert_end_node(int x);
void insert_sorted_node(int x);
// Delete functions
void delete_val(int x);
void delete_pos(int x);
void delete_all(void);
// Print function
void print_lists(void);
// Sorting functions
node *merge_sort(node *start);
node *merge(node *left, node *right);
void bubble_sort(node **head, int count);
void insertion_sort();
void selection_sort(node *head);
// Search functions
void linear_search(node *head, int input);
void binary_search(node *head, int input);
// Helper functions
node* middle(node *head);
node *middle2(node *start, node *last);
node *swap(node *px, node *py);
void sorted_insert(node *newnode);

// Nodes counter
int node_counter = 0;

int main(void)
{
    // Variables for while loop and switch
    int end = 1;
    int input;
    int option;

    while (end != 0)
    {
        option = get_int("What do you want to do:\n0 for ending program\n1 for insert node at the start\n2 for insert node at the end\n3 for insert node sorted\n4 for deleting a value\n5 for deleting a position\n6 print linked list\n7 merge sort\n8 bubble sort\n9 insertion sort\n10 selection sort\n11 linear search\n12 binary search\nOption: ");

        switch(option)
        {
            case 0:
                end = 0;
                break;
            case 1:
                input = get_int("Input value: ");
                insert_start_node(input);
                break;
            case 2:
                input = get_int("Input value: ");
                insert_end_node(input);
                break;
            case 3:
                input = get_int("Input value: ");
                insert_sorted_node(input);
                break;
            case 4:
                input = get_int("Delete value: ");
                delete_val(input);
                break;
            case 5:
                input = get_int("Delete position: ");
                delete_pos(input);
                break;
            case 6:
                print_lists();
                break;
            case 7:
                list = merge_sort(list);
                break;
            case 8:
                bubble_sort(&list, node_counter);
                break;
            case 9:
                insertion_sort();
                break;
            case 10:
                selection_sort(list);
                break;
            case 11:
                input = get_int("Search value: ");
                linear_search(list, input);
                break;
            case 12:
                input = get_int("Search value: ");
                binary_search(list, input);
                break;
        }
    }
    delete_all();
    return 0;
}

// Insert at the start
void insert_start_node(int x)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("No memory available for this node!\n");
        return delete_all();
    }
    n->value = x;

    n->next = list;
    list = n;
    node_counter++;
}

// Insert at the end
void insert_end_node(int x)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("No memory available for this node!");
        return delete_all();
    }
    n->value = x;

    // If list is empty
    if(list == NULL)
    {
        list = n;
        node_counter++;
    }
    else
    {
        for (node* current = list; current != NULL; current = current->next)
        {
            // Add to end of the list
            if (current->next == NULL)
            {
                current->next = n;
                node_counter++;
                break;
            }
        }
    }
}

// Insert sorted
void insert_sorted_node(int x)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("No memory available for this node!");
        return delete_all();
    }
    n->value = x;

    // If list is empty
    if(list == NULL)
    {
        list = n;
        node_counter++;
    }
    // If new value is lower than 1st value
    else if (n->value < list->value)
    {
        n->next = list;
        list = n;
        node_counter++;
    }
    else
    {
        for (node* current = list; current != NULL; current = current->next)
        {
            // Add value to end of the list
            if (current->next == NULL)
            {
                current->next = n;
                node_counter++;
                break;
            }

            // Add value in the middle of the list
            if (n->value < current->next->value)
            {
                n->next = current->next;
                current->next = n;
                node_counter++;
                break;
            }
        }
    }
}

// Delete by value
void delete_val(int x)
{
    bool first_node = false;
    node *prev = NULL;

    for (node *current = list; current != NULL; current = current->next)
    {
        if (first_node)
        {
            current = list;
            first_node = false;
        }

        if (current->value == x)
        {
            // Delete first
            if (list == current)
            {
                list = current->next;
                free(current);
                first_node = true;
                node_counter++;
            }
            // Delete last
            else if (current->next == NULL)
            {
                prev->next = NULL;
                free(current);
                node_counter--;
                break;
            }
            // Delete inbetween
            else
            {
                prev->next = current->next;
                free(current);
                current = prev;
                node_counter--;
            }
        }
        prev = current;
    }
}

// Delete by position
void delete_pos(int x)
{
    int position = 1;
    node *current = list;
    node *prev;
    node *next;

    while (current != NULL)
    {
        if (position == x)
        {
            // Delete first
            if (position == 1)
            {
                next = current->next;
                free(current);
                list = next;
                node_counter--;
                return;
            }
            // Delete last
            else if (position == node_counter)
            {
                prev->next = NULL;
                free(current);
                node_counter--;
                return;
            }
            // Delete inbetween
            else
            {
                prev->next = current->next;
                free(current);
                node_counter--;
                return;
            }
        }
        next = current->next;
        prev = current;
        current = next;
        position++;
    }
}

// Delete list
void delete_all(void)
{
    node *current = list;
    node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
        node_counter--;
    }
}

// Print list
void print_lists(void)
{
    node *ptr = list;
    while (ptr != NULL)
    {
        printf("Value = %i, Ptr = %p\n", ptr->value, ptr->next);
        ptr = ptr->next;
    }
}

// SORTING FUNCTIONS
// Merge sort
node *merge_sort(node *start)
{
    if (start->next == NULL)
    {
        return start;
    }

    node *mid = middle(start);
    node *start_of_right = mid->next;

    mid->next = NULL;

    node *left = merge_sort(start);
    node *right = merge_sort(start_of_right);

    node *new_head = merge(left, right);

    return new_head;
}

// Bubble sort
void bubble_sort(node **head, int count)
{
    node **h;
    int swapped;

    for (int i = 0; i <= count; i++)
    {
        h = head;
        swapped = 0;

        for (int j = 0; j < count - i - 1; j++)
        {
            node *p1 = *h;
            node *p2 = p1->next;

            if (p1->value > p2->value)
            {
                *h = swap(p1, p2);
                swapped = 1;
            }
            h = &(*h)->next;
        }
        if (swapped == 0)
        break;
    }
}

// Insertion sort
void insertion_sort()
{
    node *current = list;

    while (current != NULL)
    {
        node *next = current->next;
        sorted_insert(current);
        current = next;
    }
    list = sorted;
}

// Selection sort
void selection_sort(node *head)
{
    node *temp = head;

    while (temp)
    {
        node *min = temp;
        node *r = temp->next;

        while (r)
        {
            if (min->value > r->value)
            {
                min = r;
            }
            r = r->next;
        }
        int x = temp->value;
        temp->value = min->value;
        min->value = x;
        
        temp = temp->next;
    }
}

// ACCESS FUNCTIONS
// Linear search
void linear_search(node *head, int input)
{
    node *current = head;

    while (current != NULL)
    {
        if (current->value == input)
        {
            printf("Value %i is found.\n", current->value);
            return;
        }
        current = current->next;
    }
    printf("Value %i is not found.\n", input);
    return;
}

// Binary search
void binary_search(node *head, int input)
{
    node *start = head;
    node *last = NULL;

    do
    {
        node *mid = middle2(start, last);

        if (mid == NULL)
        {
            printf("Value %i is not found.\n", input);
            return;
        }

        if (mid->value == input)
        {
            printf("Value %i is found.\n", mid->value);
            return;
        }
        else if (mid->value < input)
        {
            start = mid->next;
        }
        else
        {
            last = mid;
        }
    }
    while (last == NULL || last != start);

    printf("Value %i is not found.\n", input);
    return;
}

// HELPER FUNCTIONS
// Helper function for merge sort
node *merge(node *left, node *right)
{
    node *dummyHead = malloc(sizeof(node));
    node *current = dummyHead;

    while (left != NULL && right != NULL)
    {
        if (left->value <= right->value)
        {
            current->next = left;
            left = left->next;
            current = current->next;
        }
        else if (right->value < left->value)
        {
            current->next = right;
            right = right->next;
            current = current->next;
        }
    }

    while (left != NULL)
    {
        current->next = left;
        left = left->next;
        current = current->next;
    }

    while (right != NULL)
    {
        current->next = right;
        right = right->next;
        current = current->next;
    }
    return dummyHead->next;
}

// Tortoise and the hare function for merge sort
node *middle(node *head)
{
    node *slow = head;
    node *fast = head->next;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = (fast->next)->next;
    }

    return slow;
}

// Tortoise and the hare function for binary search
node *middle2(node *start, node *last)
{
    node *slow = start;
    node *fast = start->next;

    while (fast != last)
    {
        fast = fast->next;
        if (fast != last)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    return slow;
}

// Swap for bubble sort
node *swap(node *px, node *py)
{
    node *temp = py->next;
    py->next = px;
    px->next = temp;
    return py;
}

// Sorted insert for insertion sort
void sorted_insert(node *newnode)
{
    if (sorted == NULL || sorted->value >= newnode->value)
    {
        newnode->next = sorted;
        sorted = newnode;
    }
    else
    {
        node *current = sorted;

        while (current->next != NULL
               && current->next->value < newnode->value)
        {
            current = current->next;
        }
        newnode->next = current->next;
        current->next = newnode;
    }
}
