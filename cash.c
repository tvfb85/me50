#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // initialize cents variable
    int cents;

    // Ask user for change required and re-prompt if invalid amount is given
    do
    {
        float dollars = get_float("Changed owed: ");

        // convert dollars to cents
        cents = round(dollars * 100);
    }
    while (cents <= 0);

    // initialize coins variable to keep track of number of coins
    int coins = 0;

    // Add total quarters needed and re-assign cents to the remaining
    coins += cents / 25;
    cents = cents % 25;

    // Add total dimes needed and re-assign cents to the remaining
    coins += cents / 10;
    cents = cents % 10;

    // Add total nickels needed and re-assign cents to the remaining
    coins += cents / 5;
    cents = cents % 5;

    // Add total pennies needed and re-assign cents to the remaining
    coins += cents / 1;

    // Print total number of coins needed to make change
    printf("%i\n", coins);
}