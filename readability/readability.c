#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int calculate_grade(string s);
int count_letters(string s);
int count_words(string s);
int count_sentences(string s);
void print_result(int x);

int main(void)
{
    string text = get_string("Text: ");

    print_result(calculate_grade(text));
}

// calculate the grade for the text
int calculate_grade(string s)
{
    int total_letters = count_letters(s);
    int total_words = count_words(s);
    int total_sentences = count_sentences(s);

    float calc_words = (100.0 / total_words);
    float L = calc_words * total_letters;
    float S = total_sentences * calc_words;
    int rounded_grade = round(0.0588 * L - 0.296 * S - 15.8);

    return rounded_grade;
}

// calculate the total letters without spaces, comma's or perionds
int count_letters(string s)
{
    int letters = 0;

    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (isalpha(s[i]))
        {
            letters++;
        }
    }
    return letters;
}

// calculate the total of words by counting the empty spaces + 1
int count_words(string s)
{
    int words = 0;

    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (isspace(s[i]))
        {
            words++;
        }
    }
    words += 1;
    return words;
}

// calculate the total sentences by checking for periods, exclamation points or question marks
int count_sentences(string s)
{
    int sentences = 0;

    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}

// print result in the terminal
void print_result(int x)
{
    if (x < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (x > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", x);
    }
}
