#include <cs50.h>
#include <stdio.h>

int getUserInput(void);

void drawPiramid(void);

void drawEmptySpaces(int height, int loopNumber);

void drawHashtags(int loopNumber);

int main(void)
{
    // function call to draw y axis
    drawPiramid();
}

// function to get input from user and returns that input
int getUserInput(void)
{
    // initialze the variable for the number of height
    int height;

    // asks for height input from user, keeps asking for input if input is other than natural number
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // return the value of height
    return height;
}

// function to draw the y axis of the piramid
void drawPiramid(void)
{
    // initialze the variable for the number of height by calling the function getUserInput
    int height = getUserInput();

    // draws the y axis of the piramid
    for (int i = 1; i <= height; i++)
    {
        // function call to draw empty spaces
        drawEmptySpaces(height, i);

        // function call to draw hashtags
        drawHashtags(i);

        // prints the two empty spaces between piramids
        printf("  ");

        // function call to draw hashtags
        drawHashtags(i);

        // prints a newline after to create a new y axes
        printf("\n");
    }
}

// function to draw the hashtags in the x axis
void drawHashtags(int loopNumber)
{
    // draws the hashtags on the x axis
    for (int k = 1; k <= loopNumber; k++)
    {
        printf("#");
    }
}

// function to draw the empty spaces in the x axis
void drawEmptySpaces(int height, int loopNumber)
{
    // draws the empty spaces on the x axis
    for (int j = 1; j <= height - loopNumber; j++)
    {
        printf(" ");
    }
}
