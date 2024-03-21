/**************************************************************************/
/* Name: arrays1D.c                                                       */
/* Purpose: Work out one-dimensional arrays and search and sort algoritms */
/* Author: D.M.Meijer                                                     */
/**************************************************************************/

// Directives
#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>

// Macros
#define MAX 10

// Replace functions
void replace_index(int arr[], size_t size, int input, int index);
void replace_value(int arr[], size_t size, int input, int new_val);
// Print function
void print_arr(int arr[], size_t size);
// Sorting functions
void merge_sort(int arr[], int l, int r);
void bubblesort (int arr[], int n);
void insertion_sort(int arr[], int n);
void selection_sort(int arr[], int n);
// Search functions
void linear_search(int arr[], int N, int x);
void binary_search(int arr[], int l, int r, int x);
// Helper functions
void merge(int arr[], int l, int m, int r);
void swap(int *xp, int *yp);

int main(void)
{
    // Initialize one-dimensional array to use in functions
    int arr[MAX] = {5, 7, 2, 1, 4, 0, 9, 3, 8, 6};

    // Variables for while loop and switch
    int end = 1;
    int option;
    int input;
    int new_val;
    int index;

    while (end != 0)
    {

        option = get_int("What do you want to do:\n0 for ending program\n1 replace value on index\n2 replace value\n3 print array\n4 merge sort array\n5 bubblesort array\n6 insertion sort array\n7 selection sort array\n8 linear search\n9 binary search\nOption: ");
        switch(option)
        {
            case 0:
            end = 0;
            break;
            case 1:
            input = get_int("What is the new value? ");
            index = get_int("At which index should we place this new value? ");
            replace_index(arr, MAX, input, index);
            break;
            case 2:
            input = get_int("What value do you want to replace? ");
            new_val = get_int("What is the new value? ");
            replace_value(arr, MAX, input, new_val);
            break;
            case 3:
            print_arr(arr, MAX);
            break;
            case 4:
            merge_sort(arr, 0, MAX - 1);
            break;
            case 5:
            bubblesort(arr, MAX);
            break;
            case 6:
            insertion_sort(arr, MAX);
            break;
            case 7:
            selection_sort(arr, MAX);
            break;
            case 8:
            input = get_int("Which number do you want to find? ");
            linear_search(arr, MAX, input);
            break;
            case 9:
            input = get_int("Which number do you want to find? ");
            binary_search(arr, 0, MAX - 1, input);
            break;
        }
    }
    return 0;
}

// Change value at certain index
void replace_index(int arr[], size_t size, int input, int index)
{
    for (int i = 0; i < size; i++)
    {
        if (i == index)
        {
            arr[i] = input;
        }
    }
}

// Change value at certain value
void replace_value(int arr[], size_t size, int input, int new_val)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == input)
        {
            arr[i] = new_val;
        }
    }
}

// Print the array
void print_arr(int arr[], size_t size)
{
    for (int i = 0; i < size; i++)
    {
        printf("index %i is %i\n", i, arr[i]);
    }
}

// SORTING FUNCTIONS
// Merge sort the array
void merge_sort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Bubble sort the array
void bubblesort (int arr[], int n)
{
    bool swapped;

    for (int i = 0; i < n; i++)
    {
        swapped = false;
        for (int j = 0; j < n; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
        {
            break;
        }
    }
}

// Insertion sort the array
void insertion_sort(int arr[], int n)
{
    int i, key, j;

    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Selection sort the array
void selection_sort(int arr[], int n)
{
    int i, j, min_index;

    for (i = 0; i < n - 1; i++)
    {
        min_index = i;

        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            swap(&arr[min_index], &arr[i]);
        }
    }
}

// ACCESS FUNCTIONS
// Linear search the array
void linear_search(int arr[], int N, int x)
{
    for (int i = 0; i < N; i++)
    {
        if (arr[i] == x)
        {
            printf("Number %i is in index %i.\n", arr[i], i);
        }
    }
    printf("Number %i is not found.\n", x);
}

// Binary search the array
void binary_search(int arr[], int l, int r, int x)
{
    while (l <= r)
    {
        int m = l + (r - l) / 2;

        if (arr[m] == x)
        {
            printf("Number %i is in index %i.\n", arr[m], m);
        }

        if (arr[m] < x)
        {
            l = m + 1;
        }
        else
        {
            r = m - 1;
        }
    }
    printf("Number is not present in the array.");
}

// HELPER FUNCTIONS
// Helper function for merge sort
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }

    for (j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Helper function for bubble and selection sort
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
