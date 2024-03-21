#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Usage: %s\n", argv[0]);
        return 1;
    }

    int key = atoi(argv[1]);

    string plaintext = get_string("plaintext:  ");
    string ciphertext = plaintext;

    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        ciphertext[i] = rotate(plaintext[i], key);
    }

    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

bool only_digits(string s)
{
    bool digits;

    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (isdigit(s[i]))
        {
            digits = true;
        }
        else
        {
            digits = false;
        }
    }
    return digits;
}

char rotate(char c, int n)
{
    if (islower(c))
    {
        c = c - 'a' + n;
        if (c > 25)
        {
            c %= 26;
        }
        c = c + 'a';
    }
    else if (isupper(c))
    {
        c = c - 'A' + n;
        if (c > 25)
        {
            c %= 26;
        }
        c = c + 'A';
    }
    return c;
}
