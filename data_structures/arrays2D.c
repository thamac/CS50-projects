/****************************************************************************/
/* Name: arrays2D.c                                                         */
/* Purpose: Work out multi-dimensional arrays and search and sort algoritms */
/* Author: D.M.Meijer                                                       */
/****************************************************************************/

// Directives
#include <cs50.h>
#include <stdio.h>

// Constants
const int M = 2;
const int N = 10;

// Replace functions
void replace_index(int arr[M][N], int input, int index_row, int index_column);
void replace_val(int arr[M][N], int input, int new_val);
// Print function
void print_arr(int arr[M][N]);
// Sorting functions
void merge_sort(int arr[][N], int l, int r, int input);
void bubblesort(int arr[], int n);
void bubble_sort_row(int arr[][N], int input);
void bubble_sort_all(int arr[M][N]);
void insertion_sort_all(int arr[M][N]);
void insertion_sort_row(int arr[][N], int input);
void selection_sort_all(int arr[M][N]);
void selection_sort_row(int arr[][N], int input);
// Search functions
void linear_search(int arr[M][N], int input);
void binary_search(int arr[M][N], int l, int r, int input);
// Helper functions
void merge(int arr[][N], int l, int m, int r, int input);
void swap(int *xp, int *yp);

int main(void)
{
    // Initialize multi-dimensional array to use in functions
    int arr[M][N] = {{5, 7, 2, 1, 4, 0, 9, 3, 8, 6}, {6, 8, 9, 0, 1, 4, 2, 3, 7, 5}};

    // Variables for while loop and switch
    int end = 1;
    int option;
    int input;
    int new_val;
    int index_row;
    int index_column;

    while (end != 0)
    {
        option = get_int("What do you want to do:\n0 for ending program\n1 replace value on index\n2 replace value\n3 print array\n4 merge sort array\n5 merge sort by row\n6 bubble sort by selected row\n7 bubble sort rowwise\n8 insertion sort all rows\n9 insertion sort by selected row\n10 selection sort all rows\n11 selection sort by selected row\n12 linear search\n13 Binary search\nOption: ");
        switch(option)
        {
            case 0:
                end = 0;
                break;
            case 1:
                input = get_int("What is the new value? ");
                index_row = get_int("At which row is this index ");
                index_column = get_int("At which index should we place this new value? ");
                replace_index(arr, input, index_row, index_column);
                break;
            case 2:
                input = get_int("Which value do you want to replace? ");
                new_val = get_int("What should the new value be? ");
                replace_val(arr, input, new_val);
                break;
            case 3:
                print_arr(arr);
                break;
            case 4:
                for (int i = 0; i < M; i++)
                {
                    merge_sort(arr, 0, N - 1, i);
                }
                break;
            case 5:
                input = get_int("Which row do you want to sort? ");
                merge_sort(arr, 0, N - 1, input);
                break;
            case 6:
                input = get_int("Which row do you want to sort? ");
                bubble_sort_row(arr, input);
                break;
            case 7:
                bubble_sort_all(arr);
                break;
            case 8:
                insertion_sort_all(arr);
                break;
            case 9:
                input = get_int("Which row do you want to sort? ");
                insertion_sort_row(arr, input);
                break;
            case 10:
                selection_sort_all(arr);
                break;
            case 11:
                input = get_int("Which row do you want to sort? ");
                selection_sort_row(arr, input);
                break;
            case 12:
                input = get_int("Which number do you want to find? ");
                linear_search(arr, input);
                break;
            case 13:
                input = get_int("Which number do you want to find? ");
                binary_search(arr, 0, N - 1, input);
                break;
        }
    }
}

// Change value at certain index
void replace_index(int arr[M][N], int input, int index_row, int index_column)
{
    index_row -= 1;
    index_column -= 1;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == index_row && j == index_column)
            {
                arr[i][j] = input;
            }
        }
    }
}

// Change value at certain value
void replace_val(int arr[M][N], int input, int new_val)
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (arr[i][j] == input)
            {
                arr[i][j] = new_val;
            }
        }
    }
}

// Print the array
void print_arr(int arr[M][N])
{
    for (int i = 0; i < M; i++)
    {
        printf("Row %i: \n", i + 1);

        for (int j = 0; j < N; j++)
        {
            printf("%i ", arr[i][j]);
        }
        printf("\n");
    }
}

// SORTING FUNCTIONS
// Merge sort the array
void merge_sort(int arr[][N], int l, int r, int input)
{

    if (l < r)
    {
        int m = l + (r - l) / 2;

        merge_sort(arr, l, m, input);
        merge_sort(arr, m + 1, r, input);

        merge(arr, l, m, r, input);
    }
}

// Bubble sort by selected row
void bubble_sort_row(int arr[][N], int input)
{
    bool swapped;

    for (int i = 0; i < N; i++)
    {
        swapped = false;
        for (int j = 0; j < N - i - 1; j++)
        {
            if (arr[input][j] > arr[input][j + 1])
            {
                swap(&arr[input][j], &arr[input][j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
        {
            break;
        }
    }
}

// Bubble sort all rows
void bubble_sort_all(int arr[M][N])
{
    bool swapped;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            swapped = false;
            for (int k = 0; k < N - j - 1; k++)
            {
                if (arr[i][k] > arr[i][k + 1])
                {
                    swap(&arr[i][k], &arr[i][k + 1]);
                    swapped = true;
                }
            }
            if (swapped == false)
            {
                break;
            }
        }
    }
}

// Insertion sort all rows
void insertion_sort_all(int arr[M][N])
{
    int i, j, key, k;

    for (i = 0; i < M; i++)
    {
        for (j = 1; j < N; j++)
        {
            key = arr[i][j];
            k = j - 1;

            while (k >= 0 && arr[i][k] > key)
            {
                arr[i][k + 1] = arr[i][k];
                k = k - 1;
            }
            arr[i][k + 1] = key;
        }
    }
}

// Insertion sort by selected row
void insertion_sort_row(int arr[][N], int input)
{
    int i, key, j;

    for (i = 1; i < N; i++)
    {
        key = arr[input][i];
        j = i - 1;

        while (j >= 0 && arr[input][j] > key)
        {
            arr[input][j + 1] = arr[input][j];
            j = j - 1;
        }
        arr[input][j + 1] = key;
    }
}

// Selection sort for all rows
void selection_sort_all(int arr[M][N])
{
    int min_index;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N - 1; j++)
        {
            min_index = j;

            for (int k = j + 1; k < N; k++)
            {
                if (arr[i][k] < arr[i][min_index])
                {
                    min_index = k;
                }
            }
            if (min_index != j)
            {
                swap(&arr[i][min_index], &arr[i][j]);
            }
        }
    }
}

// Selection sort for selected row
void selection_sort_row(int arr[][N], int input)
{
    int min_index;

    for (int i = 0; i < N - 1; i++)
    {
        min_index = i;

        for (int j = i + 1; j < N; j++)
        {
            if (arr[input][j] < arr[input][min_index])
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            swap(&arr[input][min_index], &arr[input][i]);
        }
    }
}

// ACCESS FUNCTIONS
// Linear search the array
void linear_search(int arr[M][N], int input)
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (arr[i][j] == input)
            {
                printf("Number %i is in row%i and column %i.\n", arr[i][j], i, j);
            }
        }
    }
    printf("Number %i is not found.\n", input);
}

// Binary search the array
void binary_search(int arr[M][N], int l, int r, int input)
{
    int left;
    int right;

    for (int i = 0; i < M; i++)
    {
        left = l;
        right = r;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (arr[i][mid] == input)
            {
                printf("Number %i is in index %i.\n", arr[i][mid], mid);
            }

            if (arr[i][mid] < input)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
    }
}

// HELPER FUNCTIONS
// Helper function for merge sort
void merge(int arr[][N], int l, int m, int r, int input)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
    {
        L[i] = arr[input][l + i];
    }

    for (j = 0; j < n2; j++)
    {
        R[j] = arr[input][m + 1 +j];
    }

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[input][k] = L[i];
            i++;
        }
        else
        {
            arr[input][k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[input][k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[input][k] = R[j];
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
