#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int cents;

    do
    {
        float dollars = get_float("Changed owed: ");
        cents = round(dollars * 100);
    }
    while (cents <= 0);

    int coins = 0;

    coins += cents / 25;
    cents = cents % 25;

    coins += cents / 10;
    cents = cents % 10;

    coins += cents / 5;
    cents = cents % 5;

    coins += cents / 1;

    printf("%i\n", coins);
}