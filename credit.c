#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int length = 0;
    long number;
    long n;
    string result;

    // do
    // {
    //     length = 0;
    number = get_long("Number: ");
    // }
    // while (length < 13 || length > 16);

    n = number;

    while (n) {
        n /= 10;
        length++;
    }

    int checksum = 0;
    int lastNumber;
    long remainingNumber = number;

    int firstNum;
    int secondNum;

    for (int i = 1; i <= length; i++)
    {
        lastNumber = remainingNumber % 10;
        if (i == length)
        {
            firstNum = lastNumber;
        }
        if (i == length - 1)
        {
            secondNum = lastNumber;
        }


        if (i % 2 == 0)
        {
            int doubled =  lastNumber * 2;

            if (doubled > 9)
            {
                int n1 = doubled % 10;
                int n2 = doubled / 10;
                checksum += (n1 + n2);
            }
            else {
                checksum += doubled;
            }
        }
        else
        {
            checksum += lastNumber;
        }

        remainingNumber /= 10;
    }

    if (checksum % 10 == 0)
    {
        if (firstNum == 4 && (length == 13 || length == 16))
        {
            result = "VISA\n";
        }
        else if (firstNum == 3 && (secondNum == 4 || secondNum == 7) && length == 15)
        {
            result = "AMEX\n";
        }
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
    else {
        result = "INVALID\n";
    }

    printf("%s", result);
}