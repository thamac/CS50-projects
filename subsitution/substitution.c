#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                   'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

bool check_amount_of_chars(string c);
bool check_if_character(string c);
bool check_doubles(string c);
char upper_lower(char c, char d);
string rotate(string s, string t, string u);

int main(int argc, string argv[])
{
    if (argc != 2 || !check_amount_of_chars(argv[1]) || !check_if_character(argv[1]) || !check_doubles(argv[1]))
    {
        printf("Usage: %s\n", argv[0]);
        return 1;
    }
    string plaintext = get_string("plaintext:  ");
    string ciphertext = plaintext;

    printf("ciphertext: %s\n", rotate(plaintext, argv[1], ciphertext));
    return 0;
}

// checks if the command-line input is 26 characters
bool check_amount_of_chars(string c)
{
    if (strlen(c) != 26)
    {
        return false;
    }
    return true;
}

// checks if the command-line input is only alphabetical
bool check_if_character(string c)
{
    for (int i = 0, len = strlen(c); i < len; i++)
    {
        if (!isalpha(c[i]))
        {
            return false;
        }
    }
    return true;
}

// checks if the command-line input characters occur only once
bool check_doubles(string c)
{
    int len = strlen(c);

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (i != j)
            {
                if (c[i] == c[j])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

// checks for upper- and lowercase ,whitespace, digits and punctiuations
char upper_lower(char c, char d)
{
    if (!isalpha(c))
    {
        return c;
    }
    else if (isupper(c))
    {
        d = toupper(d);
    }
    else if (islower(c))
    {
        d = tolower(d);
    }
    return c = d;
}

string rotate(string s, string t, string u)
{
    char temp;

    for (int i = 0, len = strlen(s); i < len; i++)
    {
        for (int j = 0, len_alpha = sizeof(alphabet); j < len_alpha; j++)
        {
            if (tolower(s[i]) == alphabet[j])
            {
                temp = t[j];
            }
        }
        u[i] = upper_lower(s[i], temp);
    }
    return u;
}
