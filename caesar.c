#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Validate argument count
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // Ensure key contains only digits
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: %s key\n", argv[0]);
            return 1;
        }
    }

    // Convert string argument to integer
    int key = atoi(argv[1]);

    // Ensure key is a positive integer
    if (key < 1)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // Ask user for plaintext input
    string plaintext = get_string("plaintext: ");

    // Begin output
    printf("ciphertext: ");

    // Loop over plaintext
    for (int i = 0; i < strlen(plaintext); i++)
    {

        // For all alphabetic characters apply the key, otherwise return the original character
        if (isalpha(plaintext[i]))
        {
            // Use uppercase 'A' in ASCII to find the offset and transition by the key for uppercase letters
            if (isupper(plaintext[i]))
            {
                int index = plaintext[i] - 65;
                printf("%c", ((index + key) % 26) + 65);
            }
            // Use lowercase 'a' in ASCII to find the offset and transition by the key for lowercase letters
            else
            {
                int index = plaintext[i] - 97;
                printf("%c", ((index + key) % 26) + 97);
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }

    // Finish with a newline and return success status code.
    printf("\n");
    return 0;
}