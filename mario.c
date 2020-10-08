#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = get_int("What's the height?\n");

    while (height < 1 || height > 8)
    {
        printf("Try again, %i is invalid\n", height);
        height = get_int("What's the height?\n");
    }

    for (int i = 0; i < height; i++)
    {
        int spaces = (height - i) - 1;

        for (int k = 0; k < spaces; k++)
        {
            printf(" ");
        }

        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}