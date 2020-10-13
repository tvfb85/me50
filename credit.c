#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Ask user for creditcard number
    long number = get_long("Number: ");

    // Set up variables to check the length of the creditcard number
    long n;
    n = number;
    int length = 0;

    // Loop over the creditcard divding by ten and save a count of the digits
    while (n)
    {
        n /= 10;
        length++;
    }

    // Set up variable to save checksum value
    int checksum = 0;

    // Keep a track of the last number and remaining number for the checksum calculation
    int lastNumber;
    long remainingNumber = number;

    // Initialize variables to save the first and second card digits to later check the card type
    int firstNum;
    int secondNum;

    // loop over the card number
    for (int i = 1; i <= length; i++)
    {

        // get the last number of the card
        lastNumber = remainingNumber % 10;

        // if the iteration index matches the length of the card, the first number is reached and saved
        if (i == length)
        {
            firstNum = lastNumber;
        }

        // if the iteration index is one less than the length of the card, the second number is reached and saved
        if (i == length - 1)
        {
            secondNum = lastNumber;
        }


        // if the remainder of the index modulo 2 is zero, we need to double the card number and save to the checksum
        if (i % 2 == 0)
        {
            int doubled =  lastNumber * 2;

            // if the doubled number is double-figures, we add them together before adding the total to the checksum
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
        // if the remainder of the index modulo 2 isn't zero, we do not multiple the card number
        else
        {
            checksum += lastNumber;
        }

        // update where we are in the loop
        remainingNumber /= 10;
    }

    // initialize variable to save the result
    string result;

    // ensure the checksum is valid
    if (checksum % 10 == 0)
    {

        // check for valid visa card
        if (firstNum == 4 && (length == 13 || length == 16))
        {
            result = "VISA\n";
        }

        // check for valid american express card
        else if (firstNum == 3 && (secondNum == 4 || secondNum == 7) && length == 15)
        {
            result = "AMEX\n";
        }
        // check for valid mastercard
        else if (firstNum == 5 && length == 16)
        {
            if (secondNum == 1 || secondNum == 2 || secondNum == 3 || secondNum == 4 || secondNum == 5)
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