/***********************************************************************/
/* Name: doubly_linked_lists.c                                         */
/* Purpose: Work out doubly linked lists and search and sort algoritms */
/* Author: D.M.Meijer                                                  */
/***********************************************************************/

// Directives
#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Struct prototype
typedef struct node
{
    int value;
    struct node *next, *prev;
}node;

// Structs
node *list = NULL;
node *sorted = NULL;

// Insert functions
void insert_start(int val);
void insert_end(int val);
void insert_sorted(int val);
// Delete functions
void del_val(int val);
void del_pos(int pos);
void del_all(void);
// Print function
void print_list(void);
// Sorting functions
node *merge_sort(node *head);
node *bubble_sort(node *start);
node *insertion_sort(node *start);
node *selection_sort(node *start);
// Search functions
void linear_search(node *start, int input);
void binary_search(node *start, int input);
// Helper functions
node *merge(node *first, node *second);
node *middle(node *head);
node *middle2(node *start, node *last);
node *swap(node *current, node *next);
node *selection_swap(node *temp, node *min);
void insert_sort(node *new_node);

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
                insert_start(input);
                break;
            case 2:
                input = get_int("Input value: ");
                insert_end(input);
                break;
            case 3:
                input = get_int("Input value: ");
                insert_sorted(input);
                break;
            case 4:
                input = get_int("Delete value: ");
                del_val(input);
                break;
            case 5:
                input = get_int("Delete position: ");
                del_pos(input);
                break;
            case 6:
                print_list();
                break;
            case 7:
                list = merge_sort(list);
                break;
            case 8:
                list = bubble_sort(list);
                break;
            case 9:
                list = insertion_sort(list);
                break;
            case 10:
                list = selection_sort(list);
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
    del_all();
    return 0;
}

// Insert at the start
void insert_start(int val)
{
    node *new = malloc(sizeof(node));
    if (new == NULL)
    {
        printf("No memory available for this node!\n");
        return del_all();
    }
    new->value = val;
    new->next = list;
    new->prev = NULL;

    if (list != NULL)
    {
        list->prev = new;
    }

    list = new;
}

// Insert at the end
void insert_end(int val)
{
    node *new = malloc(sizeof(node));
    if (new == NULL)
    {
        printf("No memory available for this node!\n");
        return del_all();
    }

    new->value = val;

    // If list in empty
    if (list == NULL)
    {
        new->next = list;
        new->prev = NULL;
        list = new;
    }
    // Add to the end of the list
    else
    {
        for (node *current = list; current != NULL; current = current->next)
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

// Insert sorted
void insert_sorted(int val)
{
    node *new = malloc(sizeof(node));
    if (new == NULL)
    {
        printf("No memory available for this node!\n");
        return del_all();
    }

    new->value = val;

    // If list is empty
    if (list == NULL)
    {
        new->next = list;
        new->prev = NULL;
        list = new;
    }
    // Add to the begin of the list
    else if (new->value < list->value)
    {
        new->next = list;
        new->prev = NULL;
        new->next->prev = new;
        list = new;
    }
    else
    {
        for (node *current = list; current != NULL; current = current->next)
        {
            // Add value to end of the list
            if (current->next == NULL)
            {
                current->next = new;
                new->prev = current;
                new->next = NULL;
                break;
            }

            // Add value in the middle of the list
            if (new->value < current->next->value)
            {
                new->next = current->next;
                current->next->prev = new;
                new->prev = current;
                current->next = new;
                break;
            }
        }
    }
}

// Delete by value
void del_val(int val)
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

        if (current->value == val)
        {
            // Delete first
            if (list == current)
            {
                list = current->next;
                list->prev = NULL;
                free(current);
                first_node = true;
            }
            // Delete last
            else if (current->next == NULL)
            {
                prev->next = NULL;
                free(current);
                break;
            }
            // Delete inbetween
            else
            {
                prev->next = current->next;
                current->next->prev = current->prev;
                free(current);
                current = prev;
            }
        }
        prev = current;
    }
}

// Delete by position
void del_pos(int pos)
{
    node *current = list;
    node *prev = NULL;

    for (int i = 0; i < pos; i++)
    {
        if (i + 1 == pos)
        {
            // Delete first
            if (current == list)
            {
                list = current->next;
                list->prev = NULL;
                free(current);
                return;
            }
            // Delete last
            else if (current->next == NULL)
            {
                prev->next = NULL;
                free(current);
                return;
            }
            // Delete inbetween
            else
            {
                prev->next = current->next;
                current->next->prev = current->prev;
                free(current);
                return;
            }
        }
        prev = current;
        current = current->next;
    }
}

// Delete list
void del_all(void)
{
    node *current = list;
    node *next;

    while(current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

// Print list
void print_list(void)
{
    node *current = list;

    while (current != NULL)
    {
        printf("Value is %i prev adress is %p and next adress is %p\n", current->value, current->prev, current->next);
        current = current->next;
    }
}

// SORTING FUNCTIONS
// Merge sort
node *merge_sort(node *head)
{
    node *second;

    if (!head || !head->next)
    {
        return head;
    }

    second = middle(head);

    head = merge_sort(head);
    second = merge_sort(second);

    return merge(head, second);
}

// Bubble sort
node *bubble_sort(node *start)
{
    bool swapped;
    node *current;
    node *lcurrent = NULL;

    if (start == NULL)
    {
        return start;
    }

    do
    {
        swapped = false;
        current = start;

        while (current->next != lcurrent)
        {
            if (current->value > current->next->value)
            {
                start = swap(current, current->next);
                swapped = true;
            }
            else
            {
                current = current->next;
            }
        }
        lcurrent = current;
    }
    while (swapped);
    return start;
}

// Insertion sort
node *insertion_sort(node *start)
{
    node *current = start;

    while (current != NULL)
    {
        node *next = current->next;
        insert_sort(current);
        current = next;
    }
    return sorted;
}

// Selection sort
node *selection_sort(node *start)
{
    node *temp = start;

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
        if (min != temp)
        {

            temp = selection_swap(temp, min);
        }
        temp = temp->next;
    }

    for (node *current = start; current != NULL; current = current->prev)
    {
        temp = current;
    }

    return temp;
}

// ACCESS FUNCTIONS
// Linear search
void linear_search(node *start, int input)
{
    node *current = start;

    while (current != NULL)
    {
        if (current->value == input)
        {
            printf("Value %i is found in the linked list.\n", current->value);
            return;
        }
        current = current->next;
    }
    printf("Value %i is not found in the linked list.\n", input);
}

// Binary search
void binary_search(node *start, int input)
{
    node *last = NULL;

    do
    {
        node *mid = middle2(start, last);

        if (mid == NULL)
        {
            printf("Value %i is not found in the linked list.\n", input);
        }

        if (mid->value == input)
        {
            printf("Value %i is found in the linked list.\n", mid->value);
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
    while (last == NULL || last!= start);
    printf("Value %i is not found in the linked list.\n", input);
}

// HELPER FUNCTIONS
// Helper function for merge sort
node *merge(node *first, node *second)
{
    if (!first)
    {
        return second;
    }

    if (!second)
    {
        return first;
    }

    if (first->value < second->value)
    {
        first->next = merge(first->next, second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = merge(first, second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

// Tortoise and the hare function for merge sort
node *middle(node *head)
{
    node *fast = head;
    node *slow = head;
    node *temp;

    while (fast->next != NULL && fast->next->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    temp = slow->next;
    slow->next = NULL;

    return temp;
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

// Swap function for bubble sort
node *swap(node *current, node *next)
{
    node *prev = current->prev;

    if (next->next == NULL)
    {
        if (prev == NULL)
        {
            next->prev = prev;
            current->next = next->next;
            next->next = current;
            current->prev = next;
            list = next;
        }
        else
        {
            prev->next = next;
            next->prev = prev;
            current->next = next->next;
            next->next = current;
            current->prev = next;
        }
    }
    else
    {
        if (prev == NULL)
        {
            next->prev = prev;
            current->next = next->next;
            next->next->prev = current->next->prev;
            current->prev = next;
            next->next = current;
            current->next->prev = current;
            list = next;
        }
        else
        {
            current->next = next->next;
            next->prev = prev;
            prev->next = next;
            next->next = current;
            current->prev = next;
            current->next->prev = current;
        }
    }
    return list;
}

// Swap function for selection sort
node *selection_swap(node *temp, node *min)
{
    node *temp_begin = temp->prev;
    node *temp_end = temp->next;
    node *min_begin = min->prev;
    node *min_end = min->next;

    // 2 nodes next to each other
    if (temp_end == min)
    {
        // Both nodes connected to NULL
        if (temp_begin == NULL && min_end == NULL)
        {
            min->prev = temp_begin;
            temp->next = min_end;
            temp->prev = min;
            min->next = temp;
        }
        // First node is connect to NULL
        else if (temp_begin == NULL)
        {
            min_end->prev = temp;
            min->prev = temp_begin;
            temp->next = min_end;
            temp->prev = min;
            min->next = temp;
        }
        // Second node is connect to NULL
        else if (min_end == NULL)
        {
            temp_begin->next = min;
            min->prev = temp_begin;
            temp->next = min_end;
            temp->prev = min;
            min->next = temp;
        }
        // Neither are connected to NULL
        else
        {
            min_end->prev = temp;
            temp_begin->next = min;
            min->prev = temp_begin;
            temp->next = min_end;
            temp->prev = min;
            min->next = temp;
        }
        return temp;
    }
    // 2 nodes seperated by other nodes
    else
    {
        // Both nodes connected to NULL
        if (temp_begin == NULL && min_end == NULL)
        {
            temp_end->prev = min;
            min_begin->next = temp;
            min->prev = temp_begin;
            temp->next = min_end;
            temp->prev = min_begin;
            min->next = temp_end;
        }
        // First node connected to NULL
        else if (temp_begin == NULL)
        {
            temp_end->prev = min;
            min_begin->next = temp;
            min->prev = temp_begin;
            temp->next = min_end;
            temp->prev = min_begin;
            min->next = temp_end;
            min_end->prev = temp;
        }
        // Second node is connect to NULL
        else if (min_end == NULL)
        {
            temp_end->prev = min;
            min_begin->next = temp;
            min->prev = temp_begin;
            temp->next = min_end;
            temp->prev = min_begin;
            min->next = temp_end;
            temp_begin->next = min;
        }
        // Neither are connected to NULL
        else
        {
            temp_end->prev = min;
            min_begin->next = temp;
            min->prev = temp_begin;
            temp->next = min_end;
            temp->prev = min_begin;
            min->next = temp_end;
            temp_begin->next = min;
            min_end->prev = temp;
        }
    }
    return min;
}

// Helper function for insertion sort
void insert_sort(node *new_node)
{
    // Add to sorted if emtpy
    if (sorted == NULL)
    {
        new_node->next = NULL;
        new_node->prev = NULL;
        sorted = new_node;
    }
    // Add to the begin of the sorted
    else if (new_node->value < sorted->value)
    {
        new_node->prev = sorted->prev;
        new_node->next = sorted;
        sorted->prev = new_node;
        sorted = new_node;
    }
    else
    {
        for (node *current = sorted; current != NULL; current = current->next)
        {
            // Add value to end of the list
            if (current->next == NULL)
            {
                current->next = new_node;
                new_node->prev = current;
                new_node->next = NULL;
                break;
            }

            // Add value in the middle of the list
            if (new_node->value < current->next->value)
            {
                new_node->next = current->next;
                current->next->prev = new_node;
                new_node->prev = current;
                current->next = new_node;
                break;
            }
        }
    }
}
