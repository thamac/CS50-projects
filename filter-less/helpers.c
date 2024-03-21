#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float result;
    const float devide = 3.0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            result = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / devide);
            image[i][j].rgbtBlue = result;
            image[i][j].rgbtGreen = result;
            image[i][j].rgbtRed = result;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed;
    float sepiaGreen;
    float sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
            sepiaGreen = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            sepiaBlue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));
            image[i][j].rgbtRed = (int) fmin(sepiaRed, 255.0);
            image[i][j].rgbtGreen = (int) fmin(sepiaGreen, 255.0);
            image[i][j].rgbtBlue = (int) fmin(sepiaBlue, 255.0);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid = width / 2;
    int temp;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < mid; j++)
        {
            temp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = temp;

            temp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = temp;

            temp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create copy of image to make sure the blurring effect wont affecting another pixel
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int row = 0; row < height; row++)
    {
        for (int cols = 0; cols < width; cols++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;
            float counter = 0.0;
            for (int i = row - 1; i <= row + 1; i++)
            {
                for (int j = cols - 1; j <= cols + 1; j++)
                {
                    if (i >= 0 && i < height && j >= 0 && j < width)
                    {
                        red += copy[i][j].rgbtRed;
                        green += copy[i][j].rgbtGreen;
                        blue += copy[i][j].rgbtBlue;
                        counter++;
                    }
                }
            }
            image[row][cols].rgbtRed = round(red / counter);
            image[row][cols].rgbtGreen = round(green / counter);
            image[row][cols].rgbtBlue = round(blue / counter);
        }
    }

    return;
}
