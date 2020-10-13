#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Ask user for creditcard number
    long number = get_long("Number: ");

    // Keep track of the card number's digits and length
    long digits = number;
    int length = 0;

    // Loop over the digits divding by ten and increment the length variable for each one
    while (digits)
    {
        digits /= 10;
        length++;
    }

    printf("length %i\n", length);

    // Reset digits to full card number for next loop, and keep track of the last digit and the checksum value
    digits = number;
    int lastDigit;
    int checksum = 0;

    // Initialize variables to save the first and second card digits to later check the card type
    int firstDigit;
    int secondDigit;

    // loop over the card number
    for (int i = 1; i <= length; i++)
    {

        // get the last digit of the card
        lastDigit = digits % 10;

        // if the iteration index matches the length of the card, the first digit has been reached and is saved
        if (i == length)
        {
            firstDigit = lastDigit;
        }

        // if the iteration index is one less than the length of the card, the second digit has been reached and is saved
        if (i == length - 1)
        {
            secondDigit = lastDigit;
        }


        // if the remainder of the loop index divided by two is zero (an even number), we need to double the card number and add it to the checksum
        if (i % 2 == 0)
        {
            int doubled =  lastDigit * 2;

            // if the doubled number is double-figures, we add them together before adding to the checksum
            if (doubled > 9)
            {
                int n1 = doubled % 10;
                int n2 = doubled / 10;
                checksum += (n1 + n2);
            }
            else
            {
                checksum += doubled;
            }
        }
        // if the loop index is odd, we do not double the card number
        else
        {
            checksum += lastDigit;
        }

        // update the remaining digits for next iteration
        digits /= 10;
    }

    // initialize variable to save the result
    string result;

    // ensure the checksum is valid
    if (checksum % 10 == 0)
    {

        // check for valid visa card
        if (firstDigit == 4 && (length == 13 || length == 16))
        {
            result = "VISA\n";
        }

        // check for valid american express card
        else if (firstDigit == 3 && (secondDigit == 4 || secondDigit == 7) && length == 15)
        {
            result = "AMEX\n";
        }
        // check for valid mastercard
        else if (firstDigit == 5 && length == 16)
        {
            if (secondDigit == 1 || secondDigit == 2 || secondDigit == 3 || secondDigit == 4 || secondDigit == 5)
            {
                result = "MASTERCARD\n";
            }
            else
            {
                result = "INVALID\n";
            }
        }
        else
        {
            result = "INVALID\n";
        }
    }
    else
    {
        result = "INVALID\n";
    }

    // print the result
    printf("%s", result);
}