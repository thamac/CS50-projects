#include <cs50.h>
#include <stdio.h>

long getInputNumber(void);

int checkCreditCardNumberLength(long in_cardNumber);

bool checkChecksum(long cardNumber);

string checkCompany(int length, long in_cardNumber);

int main(void)
{
    const long cardNumber = getInputNumber();

    if (checkChecksum(cardNumber))
    {
        printf("%s\n", checkCompany(checkCreditCardNumberLength(cardNumber), cardNumber));
    }
    else
    {
        printf("INVALID\n");
    }
}

// function that prompt the user to enter a (creditcard)number
long getInputNumber(void)
{
    const long inputNumber = get_long("Number: ");
    return inputNumber;
}

// function to return the length of numbers on the creditcard
int checkCreditCardNumberLength(long in_cardNumber)
{
    long cardNumber = in_cardNumber;
    int length = 0;

    while (cardNumber > 0)
    {
        cardNumber /= 10;
        length++;
    }
    return length;
}

// function with formula for the checksum
bool checkChecksum(long in_cardNumber)
{
    long cardNumber = in_cardNumber;
    const int length = checkCreditCardNumberLength(cardNumber);
    int checksum1 = 0;
    int checksum2 = 0;
    const int numberTen = 10;
    const int numberTwo = 2;

    for (int i = 1; i <= length; i++)
    {
        if (i % 2 == 0)
        {
            if (((cardNumber % numberTen) * numberTwo) < numberTen)
            {
                checksum1 += (cardNumber % numberTen) * numberTwo;
                cardNumber /= numberTen;
            }
            else
            {
                int temp = (cardNumber % numberTen) * numberTwo;
                for (int j = 1; j <= 2; j++)
                {
                    checksum1 += temp % numberTen;
                    temp /= numberTen;
                }
                cardNumber /= numberTen;
            }
        }
        else
        {
            checksum2 += cardNumber % numberTen;
            cardNumber /= numberTen;
        }
    }

    if ((checksum1 + checksum2) % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// function to check if the number starts with 34 or 37 for AMEX, 51, 52, 53, 54, or 55 for MASTERCARD and 4 for VISA
string checkCompany(int length, long in_cardNumber)
{
    const long visaShortIdentifier = in_cardNumber / 1000000000000;
    const long amexIdentifier = in_cardNumber / 10000000000000;
    const long mastercardIdentifier = in_cardNumber / 100000000000000;
    const long visaLongIdentifier = in_cardNumber / 1000000000000000;

    if (length == 13)
    {
        if (visaShortIdentifier == 4)
        {
            return "VISA";
        }
        else
        {
            return "INVALID";
        }
    }
    else if (length == 15)
    {
        if (amexIdentifier == 34 || amexIdentifier == 37)
        {
            return "AMEX";
        }
        else
        {
            return "INVALID";
        }
    }
    else if (length == 16)
    {
        if (mastercardIdentifier > 50 && mastercardIdentifier < 56)
        {
            return "MASTERCARD";
        }
        else if (visaLongIdentifier == 4)
        {
            return "VISA";
        }
        else
        {
            return "INVALID";
        }
    }
    else
    {
        return "INVALID";
    }
}
