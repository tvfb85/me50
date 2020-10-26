#include "helpers.h"
#include <stdio.h>
#include <math.h>

int pixelavg(RGBTRIPLE image);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            if (sepiaRed > 255)
                sepiaRed = 255;

            if (sepiaGreen > 255)
                sepiaGreen = 255;

            if (sepiaBlue > 255)
                sepiaBlue = 255;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= round(width / 2); j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int redcount = 0;
            int greencount = 0;
            int bluecount = 0;

            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (i + k >= 0 && j + l >= 0 && i + k < height && j + l < height)
                    {
                        redcount += round(temp[i + k][j + l].rgbtRed);
                        greencount += round(temp[i + k][j + l].rgbtGreen);
                        bluecount += round(temp[i + k][j + l].rgbtBlue);
                    }
                }
            }

            int pixelcount;

            if ((i == 0 && j == 0) || (i == height && j == 0) || (i == 0 && j == width) || (i == height && j == width))
            {
                pixelcount = 4;
            }
            else if (i == 0 || j == 0 || i == height || j == width)
            {
                pixelcount = 6;
            }
            else
            {
                pixelcount = 9;
            }

            image[i][j].rgbtRed = redcount / pixelcount;
            image[i][j].rgbtGreen = greencount / pixelcount;
            image[i][j].rgbtBlue = bluecount / pixelcount;
        }
    }

    return;
}