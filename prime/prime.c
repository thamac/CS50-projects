#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    int testNumber = number;
    bool prime;

    if (testNumber == 2)
        return true;

    for (int i = 2; i < testNumber; i++)
    {
        if (testNumber % i == 0)
        {
            return false;
        }
        else if (testNumber % i != 0)
        {
            prime = true;
        }
    }
    return prime;
}
