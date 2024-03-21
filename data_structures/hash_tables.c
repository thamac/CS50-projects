/***************************************************************/
/* Name: hash_tables.c                                         */
/* Purpose: Work out hash tables and search and sort algoritms */
/* Author: D.M.Meijer                                          */
/***************************************************************/

// Directives
#include <cs50.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Struct prototype
typedef struct node
{
    int value;
    struct node *next;
}node;

// Temp struct
node *sorted = NULL;

// Marcos
#define MODULES_DIVIDER 10
#define MAX 10

// Hash functions
int hash_division(int key);
int hash_midsquare(int key);
int hash_folding(int key);
int hash_multipli(int key);
// Insert chaining functions
void insert_start_chain(node *arr[], int input);
void insert_end_chain(node *arr[], int input);
void insert_sort_chain(node *arr[], int input);
// Insert probing functions
void insert_linear(int arr[], int input);
void insert_quad(int arr[], int input);
void insert_dh(int arr[], int input);
// Check load factor functions
bool load_factor_chain(node *arr[]);
bool load_factor_prob(int arr[]);
// Delete functions
void del_val_chain(node *arr[], int val);
void del_val_prob(int arr[], int val);
void del_pos_chain(node *arr[], int arr_pos, int node_pos);
void del_pos_prob(int arr[], int input);
void del_all_chain(node *arr[]);
void del_all_prob(int arr[]);
// Print function
void print_chain_table(node *narr[]);
void print_prob_table(int parr[]);
// Sorting functions
void merge_sort_index(node *arr[]);
node *merge_sort(node *start);
void bubble_sort_index(node *arr[]);
node *bubble_sort(node *start);
void insertion_sort_index(node *arr[]);
node *insertion_sort(node *start);
void selection_sort_index(node *arr[]);
node *selection_sort(node *start);
// chain node search functions
void linear_search_chain(node *arr[], int input);
void binary_search_chain(node *arr[], int input);
// hash based search functions
void linear_prob_search(int arr[], int input);
void quad_prob_search(int arr[], int input);
void dh_prob_search(int arr[], int input);
// Helper functions
node *middle(node *head);
node *middle2(node *start, node *last);
node *merge(node *left, node *right);
node *swap_bubble(node *prev, node *px, node *py);
node *swap_selection(node *prev_px, node *px, node *prev_py, node *py);
void sorted_insert(node *newnode);

int main(void)
{
    // Create array for hash table for probing
    int hash_prob[MAX];

    for (int i = 0; i < MAX; i++)
    {
        hash_prob[i] = -1;
    }

    // Create array for hash table for chaining
    node *hash_chain[MAX];

    for (int j = 0; j < MAX; j++)
    {
        hash_chain[j] = NULL;
    }

    // Variables for while loop and switch
    int end = 1;
    int option;
    int input;
    int arr_pos;
    int node_pos;

    while (end != 0)
    {
        option = get_int("What do you want to do:\n0 ending program\n1 insert node at start (chaining)\n2 insert node at end (chaining)\n3 insert node sorted (chaining)\n4 insert linear\n5 insert quadratic linear\n6 insert double hashing\n7 print chain table\n8 print prob table\n9 delete value chained\n10 delete value probing\n11 delete pos chained\n12 delete pos probing\n13 delete all chained\n14 delete all probing\n15 merge sort\n16 bubble sort\n17 insertion sort\n18 selection sort\n19 linear chain search\n20 binary chain search\n21 linear prob search\n22 quad prob search\n23 double hash prob search\nOption: ");

        switch(option)
        {
            case 0:
                end = 0;
                break;
            case 1:
                input = get_int("Add value: ");
                insert_start_chain(hash_chain, input);
                break;
            case 2:
                input = get_int("Add value: ");
                insert_end_chain(hash_chain, input);
                break;
            case 3:
                input = get_int("Add value: ");
                insert_sort_chain(hash_chain, input);
                break;
            case 4:
                input = get_int("Add value: ");
                insert_linear(hash_prob, input);
                break;
            case 5:
                input = get_int("Add value: ");
                insert_quad(hash_prob, input);
                break;
            case 6:
                input = get_int("Add value: ");
                insert_dh(hash_prob, input);
                break;
            case 7:
                print_chain_table(hash_chain);
                break;
            case 8:
                print_prob_table(hash_prob);
                break;
            case 9:
                input = get_int("Delete value: ");
                del_val_chain(hash_chain, input);
                break;
            case 10:
                input = get_int("Delete value: ");
                del_val_prob(hash_prob, input);
                break;
            case 11:
                arr_pos = get_int("Delete pos on index array: ");
                node_pos = get_int("Delete pos on index %d: ", arr_pos);
                del_pos_chain(hash_chain, arr_pos, node_pos);
                break;
            case 12:
                input = get_int("Delete pos on index array: ");
                del_pos_prob(hash_prob, input);
                break;
            case 13:
                del_all_chain(hash_chain);
                break;
            case 14:
                del_all_prob(hash_prob);
                break;
            case 15:
                merge_sort_index(hash_chain);
                break;
            case 16:
                bubble_sort_index(hash_chain);
                break;
            case 17:
                insertion_sort_index(hash_chain);
                break;
            case 18:
                selection_sort_index(hash_chain);
                break;
            case 19:
                input = get_int("Find number: ");
                linear_search_chain(hash_chain, input);
                break;
            case 20:
                input = get_int("Find number: ");
                binary_search_chain(hash_chain, input);
                break;
            case 21:
                input = get_int("Find number: ");
                linear_prob_search(hash_prob, input);
                break;
            case 22:
                input = get_int("Find number: ");
                quad_prob_search(hash_prob, input);
                break;
            case 23:
                input = get_int("Find number: ");
                dh_prob_search(hash_prob, input);
                break;
        }
    }
    del_all_chain(hash_chain);
    
    return 0;
}

// Create hash function: division method
int hash_division(int key)
{
    key %= MAX;
    return key;
}

// Create hash function: mid square method
int hash_midsquare(int key)
{
    key *= key;
    int n = key;
    int count = 0;

    // Checks how many numbers hvalue has
    while (n > 0)
    {
        count++;
        n /= MODULES_DIVIDER;
    }

    // Calculates which number returns as the key value
    switch(count)
    {
        case 4:
            key /= MODULES_DIVIDER;
            key %= MODULES_DIVIDER;
            break;
        case 3:
            key /= MODULES_DIVIDER;
            key %= MODULES_DIVIDER;
            break;
        case 2:
            key %= MODULES_DIVIDER;
            break;
    }
    return key;
}

// Create hash function: folding method
int hash_folding(int key)
{
    int count = 0;
    int n = key;
    int k1 = 0, k2 = 0, k3 = 0;

    // Checks how many numbers hvalue has
    while (n > 0)
    {
        count++;
        n /= MODULES_DIVIDER;
    }

    // Calculates which number returns as the key value
    switch(count)
    {
        case 2:
            k1 = key % MODULES_DIVIDER;
            k2 = key / MODULES_DIVIDER;
            key = k1 + k2;
            break;
        case 3:
            k1 = key % MODULES_DIVIDER;
            k2 = key / MODULES_DIVIDER;
            k3 = k2 / MODULES_DIVIDER;
            k2 %= MODULES_DIVIDER;
            key = k1 + k2 + k3;
            break;
    }
    return key;
}

// Create hash function: multiplication method
int hash_multipli(int key)
{
    double A = 0.2654435761;
    key = floor(MAX * fmod((key * A), 1));
    return key;
}

// INSERT NODE WITH SEPERATE CHAINING
// Insert node at the start function
void insert_start_chain(node *arr[], int input)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("Malloc failed!\n");
        return del_all_chain(arr);
    }

    // Use the multiplication method to generate the key
    int key = hash_division(input);

    n->value = input;
    // Add to start of array index
    n->next = arr[key];
    arr[key] = n;
}

// Insert node at the end function
void insert_end_chain(node *arr[], int input)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("Malloc failed!\n");
        return del_all_chain(arr);
    }

    // Use the multiplication method to generate the key
    int key = hash_division(input);

    n->value = input;

    // If array index is empty
    if (arr[key] == NULL)
    {
        arr[key] = n;
    }
    // Add to the end of the array index
    else
    {
        for (node *current = arr[key]; current != NULL; current = current->next)
        {
            if (current->next == NULL)
            {
                current->next = n;
                break;
            }
        }
    }
}

// Insert node sorted function
void insert_sort_chain(node *arr[], int input)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("Malloc failed!\n");
        return del_all_chain(arr);
    }

    // Use the multiplication method to generate the key
    int key = hash_division(input);

    n->value = input;

    // If array index is empty
    if (arr[key] == NULL)
    {
        arr[key] = n;
    }
    // If new value is lower than the 1st value
    else if (n->value < arr[key]->value)
    {
        n->next = arr[key];
        arr[key] = n;
    }
    else
    {
        for (node *current = arr[key]; current != NULL; current = current->next)
        {
            // Add value to the end of the list
            if (current->next == NULL)
            {
                current->next = n;
                break;
            }
            // Add value inbetween other nodes
            else if (n->value < current->next->value)
            {
                n->next = current->next;
                current->next = n;
                break;
            }
        }
    }
}

// INSERT NODE WITH OPEN ADRESSING
// Insert node with linear probing
void insert_linear(int arr[], int input)
{
    // Use the devision method to generate the key
    int key = hash_division(input);

    // Checks if the array index is empty else checks the next array index
    while (arr[key] != -1)
    {
        key = (key + 1) % MAX;
    }

    arr[key] = input;
}

// Insert node with quadratic probing
void insert_quad(int arr[], int input)
{
    // Use the devision method to generate the key
    int key = hash_division(input);

    // Integers to calculate the quadratic step
    int quad = 1;
    int old_quad = 0;

    // Checks if the array index is empty else calculates the next array index
    while (arr[key] != -1)
    {
        quad *= quad;
        key = key + quad - old_quad;
        old_quad = quad;
        quad++;
    }
    arr[key] = input;
}

// Insert node with double hashing
void insert_dh(int arr[], int input)
{
    // Use the devision method to generate the key
    int key = hash_division(input);
    // Variables for the double hashing
    int collision = 0;
    int modulus_h2 = 8;
    int new_key;
    int h1 = input;
    int h2 = input % modulus_h2;

    // Checks if the array index is empty else calculates the next array index
    while (arr[key] != -1)
    {
        new_key = (h1 + collision * (collision + h2 % modulus_h2)) % MAX;
        key = new_key;
        collision++;
    }
    arr[key] = input;
}

// calculate load factor of hashtable
bool load_factor_chain(node *arr[])
{
    float elements = 0.0;

    for (int i = 0; i < MAX; i++)
    {
        if (arr[i] != NULL)
        {
            elements++;
        }
    }

    float factor = elements / MAX;
    float MAX_factor = 0.75;

    if (factor >= MAX_factor)
    {
        return true;
        printf("Load factor exceeds 0.75");
    }
    return false;
    printf("Load factor does not exceeds 0.75");
}

bool load_factor_prob(int arr[])
{
    float elements = 0.0;

    for (int i = 0; i < MAX; i++)
    {
        if (arr[i] != -1)
        {
            elements++;
        }
    }

    float factor = elements / MAX;
    float MAX_factor = 0.75;

    if (factor >= MAX_factor)
    {
        return true;
        printf("Load factor exceeds 0.75");
    }
    return false;
    printf("Load factor does not exceeds 0.75");
}

// Delete node by value function chained
void del_val_chain(node *arr[], int val)
{
    for (int i = 0; i < MAX; i++)
    {
        if (arr[i] != NULL)
        {
            bool first_node = false;
            node *prev = NULL;

            for (node *current = arr[i]; current != NULL; current = current->next)
            {
                // Check if the first node is deleted if so reset the current to arr[i]
                if (first_node)
                {
                    current = arr[i];
                    first_node = false;
                }

                if (current->value == val)
                {
                    // Delete first node and set first_node to true
                    if (arr[i] == current)
                    {
                        arr[i] = current->next;
                        free(current);
                        first_node = true;
                    }
                    // Delete last node
                    else if (current->next == NULL)
                    {
                        prev->next = NULL;
                        free(current);
                        break;
                    }
                    // Delete inbetween value
                    else
                    {
                        prev->next = current->next;
                        free(current);
                        current = prev;
                    }
                }
                prev = current;
            }
        }
    }
}

// Delete node by value function prob
void del_val_prob(int arr[], int val)
{
    for (int i = 0; i < MAX; i++)
    {
        if (arr[i] == val)
        {
            arr[i] = -1;
        }
    }
}

// Delete node by position function chained
void del_pos_chain(node *arr[], int arr_pos, int node_pos)
{
    int position = 1;
    node *prev;
    node *next;

    for (node *current = arr[arr_pos]; current != NULL; current = current->next)
    {
        if (position == node_pos)
        {
            // Delete the first node
            if (position == 1)
            {
                next = current->next;
                free(current);
                arr[arr_pos] = next;
                return;
            }
            // Delete the last node
            else if (current->next == NULL)
            {
                prev->next = NULL;
                free(current);
                return;
            }
            // Delete inbetween node
            else
            {
                prev->next = current->next;
                free(current);
                return;
            }
        }
        prev = current;
        position++;
    }
}

// Delete node by position function prob
void del_pos_prob(int arr[], int input)
{
    for (int i = 0; i < MAX; i++)
    {
        if (i == input)
        {
            arr[i] = -1;
        }
    }
}

// Delete all nodes function chained
void del_all_chain(node *arr[])
{
    for (int i = 0; i < MAX; i++)
    {
        if (arr[i] != NULL)
        {
            node *current = arr[i];
            node *next;

            while (current != NULL)
            {
                next = current->next;
                free(current);
                current = next;
            }
            arr[i] = NULL;
        }
    }
}

// Delete all values function prob
void del_all_prob(int arr[])
{
    for (int i  = 0; i < MAX; i++)
    {
        if (arr[i] != -1)
        {
            arr[i] = -1;
        }
    }
}

// PRINTING HASH TABLES
// Print hash table for chaining
void print_chain_table(node *arr[])
{
    for (int i = 0; i < MAX; i++)
    {
        if (arr[i] != NULL)
        {
            for (node *current = arr[i]; current != NULL; current = current->next)
            {
                printf("index %d has value %d and ", i, current->value);
                printf("is on memloc %p and next memloc is %p.\n",current, current->next);
            }
        }
    }
}

// Print hash table for probing
void print_prob_table(int arr[])
{
    for (int i = 0; i < MAX; i++)
    {
        if (arr[i] != -1)
        {
            printf("index %d has value %d.\n", i, arr[i]);
        }
    }
}

// SORTING FUNCTIONS FOR SEPERATE CHAINING
// Merge sort per row
void merge_sort_index(node *arr[])
{
    for (int i = 0; i < MAX; i++)
    {
        if (arr[i] != NULL)
        {
            arr[i] = merge_sort(arr[i]);
        }
    }
}

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

// Bubble sort per row
void bubble_sort_index(node *arr[])
{
    for (int i = 0; i < MAX; i++)
    {
        if (arr[i] != NULL)
        {
            arr[i] = bubble_sort(arr[i]);
        }
    }
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
        node *prev = NULL;

        while (current->next != lcurrent)
        {
            if (current->value > current->next->value)
            {
                current = swap_bubble(prev, current, current->next);

                if (prev == NULL)
                {
                    start = current;
                }
                swapped = true;
            }
            prev = current;
            current = current->next;
        }
        lcurrent = current;
    }
    while (swapped);
    return start;
}

// Insertion sort by index
void insertion_sort_index(node *arr[])
{
    for (int i = 0; i < MAX; i++)
    {
        if (arr[i] != NULL)
        {
            arr[i] = insertion_sort(arr[i]);
        }
    }
}

// Insertion sort
node *insertion_sort(node *start)
{
    node *current = start;

    while (current != NULL)
    {
        node *next = current->next;
        sorted_insert(current);
        current = next;
    }

    return sorted;
}

// Selection sort by row
void selection_sort_index(node *arr[])
{
    for (int i = 0; i < MAX; i++)
    {
        if (arr[i] != NULL)
        {
            arr[i] = selection_sort(arr[i]);
        }
    }
}

// Selection sort
node *selection_sort(node *start)
{
    node *temp = start;
    node *temp_prev = NULL;

    while (temp)
    {
        node *min = temp;
        node *min_prev = NULL;
        node *r = temp->next;
        node *r_prev = NULL;

        while (r)
        {
            if (min->value > r->value)
            {
                min_prev = r_prev;
                min = r;
            }
            r_prev = r;
            r = r->next;
        }

        if (min != temp)
        {
            temp = swap_selection(temp_prev, temp, min_prev, min);

            if (temp_prev == NULL)
            {
                start = temp;
            }
        }

        temp_prev = temp;
        temp = temp->next;
    }
    return start;
}

// ACCESS FUNCTIONS
// Hash table chained linear search
void linear_search_chain(node *arr[], int input)
{
    for (int i = 0; i < MAX; i++)
    {
        if (arr[i] != NULL)
        {
            for (node *current = arr[i]; current != NULL; current = current->next)
            {
                if (input == current->value)
                {
                    printf("Found %d at index %d\n", input, i);
                    return;
                }
            }
        }
    }
    printf("Number not found!\n");
}

// Hash table chained binary search
void binary_search_chain(node *arr[], int input)
{
    for (int i = 0; i < MAX; i++)
    {
        if (arr[i] != NULL)
        {
            node *start = arr[i];
            node *last = NULL;

            do
            {
                node *mid = middle2(start, last);

                if (mid == NULL)
                {
                    printf("Number is not found\n");
                    return;
                }

                if (mid->value == input)
                {
                    printf("Number %d is found at index %d\n", mid->value, i);
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
        }
    }
    printf("Number is not found\n");
}

// HASH BASED SEARCH
// Hash table linear probing search
void linear_prob_search(int arr[], int input)
{
    int key = hash_division(input);

    for (int i = 0; i < MAX; i++)
    {
        if (arr[key] == input)
        {
            printf("Number %d is found at index %d\n", input, i);
            return;
        }
        else
        {
            key = (key + 1) % MAX;
        }
    }
    printf("Number is not found\n");
}
// Hash table quadratic probing search
void quad_prob_search(int arr[], int input)
{
    int key = hash_division(input);

    int quad = 1;
    int old_quad = 0;

    for (int i = 0; i < MAX; i++)
    {
        if (arr[i] == input)
        {
            printf("Number %d is found at index %d\n", input, i);
            return;
        }
        else
        {
            quad *= quad;
            key = key + quad - old_quad;
            old_quad = quad;
            quad++;
        }
    }
    printf("Number is not found\n");
}

// Hash table double hashing search
void dh_prob_search(int arr[], int input)
{
    int key = hash_division(input);

    int collision = 0;
    int modulus_h2 = 8;
    int new_key;
    int h1 = input;
    int h2 = input % modulus_h2;

    for (int i = 0; i < MAX; i++)
    {
        if (arr[i] == input)
        {
            printf("Number %d is found at index %d\n", input, i);
            return;
        }
        else
        {
            new_key = (h1 + collision * (collision + h2 % modulus_h2)) % MAX;
            key = new_key;
            collision++;
        }
    }
    printf("Number is not found\n");
}

// HELPER FUNCTIONS
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

// Helper function for bubble sort
node *swap_bubble(node *prev, node *px, node *py)
{
    node *temp = px;

    px = py;
    py = temp;

    py->next = px->next;
    px->next = py;

    if (prev != NULL)
    {

        prev->next = px;
    }

    return px;
}

// Helper function for selection sort
node *swap_selection(node *prev_px, node *px, node *prev_py, node *py)
{
    node *temp = py->next;

    // If it is the first node and the 2 nodes are next to each
    if (px->next == py && prev_px == NULL)
    {
        py->next = px;
    }
    // If the 2 nodes are next to each
    else if (px->next == py)
    {
        prev_px->next = py;
        py->next = px;
    }
    // If it is the first and last node
    else if ((prev_px == NULL && py->next == NULL) || prev_px == NULL)
    {
        py->next = px->next;
        prev_py->next = px;
    }
    // Any other option than the above
    else
    {
        prev_px->next = py;
        py->next = px->next;
        prev_py->next = px;
    }

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
