#include <stdio.h>
#include <cs50.h>

void build_pyramid(int width);

int main(void)
{
    // initialize height variable
    int height;

    // Ask user for height input and re-prompt if input is invalid
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Loop through positive numbers from 1 until input height
    for (int i = 1; i <= height; i++)
    {
        // Calculate spaces for row
        int spaces = height - i;

        // Print a space character for each of the spaces
        for (int j = 0; j < spaces; j++)
        {
            printf(" ");
        }

        // Builds row for left pyramid
        build_pyramid(i);

        // Print the 'gap'
        printf("  ");

        // Builds row for right pyramid
        build_pyramid(i);

        // Finish the row with a new line
        printf("\n");
    }
}

void build_pyramid(int width)
{
    // Print a hash for each of the outer loop's count
    for (int i = 0; i < width; i++)
    {
        printf("#");
    }
}
