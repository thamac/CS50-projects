// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string replace(string s);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s word\n", argv[0]);
        return 1;
    }

    printf("%s\n", replace(argv[1]));

    return 0;
}

string replace(string s)
{
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        switch (s[i])
        {
            case 'a':
                s[i] = '6';
                break;

            case 'e':
                s[i] = '3';
                break;

            case 'i':
                s[i] = '1';
                break;

            case 'o':
                s[i] = '0';
                break;
        }
    }
    return s;
}
