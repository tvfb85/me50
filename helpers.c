#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For each pixel in each row and column
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average of the pixel's red, green and blue values, rounded to the nearest whole number
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / (float) 3);

            // Update the pixel's red, green and blue values to be equal
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
    // Loop each row and column's pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Copy the original color values
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Convert original color values to sepia, rounding to the nearest whole number
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // Account for results higher than the maximum value for an 8-bit color value
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Replace the pixel's color values with the calculated sepia values
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
    // Loop each row
    for (int i = 0; i < height; i++)
    {
        // Loop each column from the left up until the center of the image
        for (int j = 0; j < round(width / 2); j++)
        {
            // Temporarily store the original pixel on the left side of the image
            RGBTRIPLE temp = image[i][j];

            // Swap the original pixel to the corresponding pixel on the right of the image
            image[i][j] = image[i][(width - j) - 1];

            // Set the pixel on the right to the original pixel stored in temp
            image[i][(width - j) - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // Create a copy of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Loop each row's pixels
    for (int i = 0; i < height; i++)
    {
        // Loop each column's pixels
        for (int j = 0; j < width; j++)
        {

            // Initialize variables to hold sum of color values from surrounding pixels
            int redcount = 0;
            int greencount = 0;
            int bluecount = 0;

            // Loop surrounding pixels starting from top left
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    // As the surrounding pixels are looped, check the pixel is not out-of-bounds (less than 0 or greater than the height or width of the image)
                    if (i + k >= 0 && j + l >= 0 && i + k < height && j + l < height)
                    {
                        // Update counts with surrounding pixel's color values
                        redcount += temp[i + k][j + l].rgbtRed;
                        greencount += temp[i + k][j + l].rgbtGreen;
                        bluecount += temp[i + k][j + l].rgbtBlue;
                    }
                }
            }

            // Initialize variable for holding count of pixels involved in calculation (original pixel + surrounding pixels)
            int pixelcount;

            // If pixel is a corner, there are four pixels
            if ((i == 0 && j == 0) || (i == (height - 1) && j == 0) || (i == 0 && j == (width - 1)) || (i == (height - 1) && j == (width - 1)))
            {
                pixelcount = 4;
            }
            // If the pixel is an edge (and not a corner), there are six pixels
            else if (i == 0 || j == 0 || i == (height - 1) || j == (width - 1))
            {
                pixelcount = 6;
            }
            // For all other 'middle' pixels, there are nine pixels involved
            else
            {
                pixelcount = 9;
            }

            // Use the pixelcount to calculate averages for each color, rounded to the nearest whole number, and update original pixel's values
            image[i][j].rgbtRed = round(redcount / (float) pixelcount);
            image[i][j].rgbtGreen = round(greencount / (float) pixelcount);
            image[i][j].rgbtBlue = round(bluecount / (float) pixelcount);
        }
    }

    return;
}