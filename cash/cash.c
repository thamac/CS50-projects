#include <cs50.h>
#include <stdio.h>

int calculateCoins(void);

int getCash(void);

int main(void)
{
    // prints the result from funtion calculateCoins
    printf("%i\n", calculateCoins());
}

// function to calculate the amount of coins from input getCash
int calculateCoins(void)
{
    int cash = getCash();
    int numberOfCoins = 0;

    while (cash > 0)
    {
        if (cash >= 25)
        {
            cash -= 25;
            numberOfCoins++;
        }
        else if (cash >= 10)
        {
            cash -= 10;
            numberOfCoins++;
        }
        else if (cash >= 5)
        {
            cash -= 5;
            numberOfCoins++;
        }
        else if (cash >= 1)
        {
            cash -= 1;
            numberOfCoins++;
        }
    }
    return numberOfCoins;
}

// function to prompt the user to enter an amount
int getCash(void)
{
    int cash;

    do
    {
        cash = get_int("Change owed: ");
    }
    while (cash < 0);

    return cash;
}
