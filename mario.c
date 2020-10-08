#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Ask user for input
    int height = get_int("What's the height?\n");

    // Re-prompt the user until a valid number is given
    while (height < 1 || height > 8)
    {
        printf("Try again, %i is invalid\n", height);
        height = get_int("What's the height?\n");
    }

    // Loop through positive numbers from 1 until input height
    for (int i = 1; i <= height; i++)
    {
        // Calculate remaining spaces for row
        int spaces = height - i;

        for (int k = 0; k < spaces; k++)
        {
            printf(" ");
        }

        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}