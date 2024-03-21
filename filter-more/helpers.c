#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int sum = 0;
    float total;
    const float devide = 3.0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sum += (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue);
            total = round(sum / devide);
            total = fmin(total, 255.0);
            image[i][j].rgbtRed = total;
            image[i][j].rgbtGreen = total;
            image[i][j].rgbtBlue = total;
            sum = 0;
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
    RGBTRIPLE copy[height][width];

    for (int cp_rows = 0; cp_rows < height; cp_rows++)
    {
        for (int cp_cols = 0; cp_cols < width; cp_cols++)
        {
            copy[cp_rows][cp_cols] = image[cp_rows][cp_cols];
        }
    }

    for (int rows = 0; rows < height; rows++)
    {
        for (int cols = 0; cols < width; cols++)
        {
            float counter = 0.0;
            int red = 0;
            int green = 0;
            int blue = 0;
            for (int i = rows - 1; i <= rows + 1; i++)
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
            image[rows][cols].rgbtRed = round(red / counter);
            image[rows][cols].rgbtGreen = round(green / counter);
            image[rows][cols].rgbtBlue = round(blue / counter);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int cp_row = 0; cp_row < height; cp_row++)
    {
        for (int cp_col = 0; cp_col < width; cp_col++)
        {
            copy[cp_row][cp_col] = image[cp_row][cp_col];
        }
    }

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int Gx_red = 0;
            int Gy_red = 0;
            int Gx_green = 0;
            int Gy_green = 0;
            int Gx_blue = 0;
            int Gy_blue = 0;
            int red = 0;
            int green = 0;
            int blue = 0;
            int index1 = 0;
            int index2 = 0;
            for (int i = row - 1; i <= row + 1; i++)
            {
                index1 = 0;
                for (int j = col - 1; j <= col + 1; j++)
                {
                    if (i >= 0 && i < height && j >= 0 && j < width)
                    {
                        Gx_red += copy[i][j].rgbtRed * Gx[index1][index2];
                        Gy_red += copy[i][j].rgbtRed * Gy[index1][index2];
                        Gx_green += copy[i][j].rgbtGreen * Gx[index1][index2];
                        Gy_green += copy[i][j].rgbtGreen * Gy[index1][index2];
                        Gx_blue += copy[i][j].rgbtBlue * Gx[index1][index2];
                        Gy_blue += copy[i][j].rgbtBlue * Gy[index1][index2];
                    }
                    index1++;
                }
                index2++;
            }
            red = round(sqrt((Gx_red * Gx_red) + (Gy_red * Gy_red)));
            green = round(sqrt((Gx_green * Gx_green) + (Gy_green * Gy_green)));
            blue = round(sqrt((Gx_blue * Gx_blue) + (Gy_blue * Gy_blue)));

            if (red > 255)
            {
                red = 255;
            }

            if (green > 255)
            {
                green = 255;
            }

            if (blue > 255)
            {
                blue = 255;
            }

            image[row][col].rgbtRed = red;
            image[row][col].rgbtGreen = green;
            image[row][col].rgbtBlue = blue;
        }
    }

    return;
}
