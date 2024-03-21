// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
} avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities(void);
void swap(string city1, int temp1, string city2, int temp2);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order
void sort_cities(void)
{
    int temp_temp;
    string temp_city;

    int arr_length = sizeof(temps) / sizeof(temps[0]);

    // insertion sort
    for (int i = 0; i < arr_length; i++)
    {
        for (int j = 0; j < arr_length - i; j++)
        {
            if (temps[j].temp < temps[j + 1].temp)
            {
                temp_temp = temps[j].temp;
                temp_city = temps[j].city;

                temps[j].temp = temps[j + 1].temp;
                temps[j].city = temps[j + 1].city;

                temps[j + 1].temp = temp_temp;
                temps[j + 1].city = temp_city;
            }
        }
    }

    // Selecion sort

    // int i = 0;
    // int j = 0;
    // int index = 0;

    // while (i < arr_length)
    // {
    //     j = i;
    //     int highest_temp = 0;
    //     while (j < arr_length)
    //     {
    //         if (highest_temp < temps[j].temp)
    //         {
    //             highest_temp = temps[j].temp;
    //             index = j;
    //         }
    //         j++;
    //     }
    //     temp_temp = temps[i].temp;
    //     temp_city = temps[i].city;

    //     temps[i].temp = temps[index].temp;
    //     temps[i].city = temps[index].city;

    //     temps[index].temp = temp_temp;
    //     temps[index].city = temp_city;
    //     i++;
    // }

    // Bubble sort
    // bool swapped;

    // for (int i = 0; i < arr_length; i++)
    // {
    //     swapped = false;
    //     for (int j = 0; j < arr_length - i - 1; j++)
    //     {
    //         if (temps[j].temp < temps[j + 1].temp)
    //         {
    //             temp_temp = temps[j].temp;
    //             temp_city = temps[j].city;

    //             temps[j].temp = temps[j + 1].temp;
    //             temps[j].city = temps[j + 1].city;

    //             temps[j + 1].temp = temp_temp;
    //             temps[j + 1].city = temp_city;
    //             swapped = true;
    //         }
    //     }
    //     if (swapped == false)
    //     {
    //         break;
    //     }
    // }
}
