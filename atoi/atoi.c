#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);
int recursively(string input, int index);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    int index = strlen(input) - 1;
    string text = input;

    return recursively(text, index);
}


int recursively(string input, int index)
{
    int digits = 0;
    string text = input;

    if (index < 0)
    {
        return digits;
    }

    digits = text[index] - '0';
    index--;

    return recursively(input, index) * 10 + digits;
}
