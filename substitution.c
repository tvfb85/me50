#define _GNU_SOURCE

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool has_duplicates(string key);
void encodetext(string plaintext, string key);

int main(int argc, string argv[])
{
    // Validate argument count
    if (argc != 2)
    {
        printf("Usage: %s KEY\n", argv[0]);
        return 1;
    }

    // Save the key from the argument list
    string key = argv[1];

    // Ensure key contains the correct number of characters
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    // Ensure key contains only alphabetic characters
    for (int i = 0; key[i] != '\0'; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters\n");
            return 1;
        }
    }

    // If key contains only unique characters, ask user for plaintext and output encoded ciphertext
    if (!has_duplicates(key))
    {
        // Ask user for plaintext input
        string plaintext = get_string("plaintext: ");

        // Print encoded ciphertext
        printf("ciphertext: ");

        encodetext(plaintext, key);

        printf("\n");
        return 0;
    }
    else
    {
        // Exit with unsuccessful status code if key contains duplicate characters
        return 1;
    }
}

bool has_duplicates(string key)
{
    // Create dynamic char array to hold key characters to be checked
    char *haystack = malloc(27);
    // Set terminating null character
    haystack[26] = '\0';

    // For each character, search for existing match in haystack array
    for (int i = 0; key[i] != '\0'; i++)
    {
        char needle[2] = { key[i], '\0' };
        string match = strcasestr(haystack, needle);

        // If a matching character is found in the haystack, a duplicate has been found and exit
        if (match)
        {
            printf("Keys must not contain repeated characters\n");
            return true;
        }
        // Otherwise, add character to the haystack for remaining iterations
        else
        {
            haystack[i] = key[i];
        }
    }

    // Avoid memory leak
    free(haystack);
    return false;
}

// Encode each alphabetic character in the plaintext
void encodetext(string plaintext, string key)
{
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        // Do not encode non-alphabetic characters
        if (!isalpha(plaintext[i]))
        {
            printf("%c", plaintext[i]);
        }
        // For uppercase characters, use uppercase 'A' in ASCII to get the offset and find the corresponding letter in the key
        else if (isupper(plaintext[i]))
        {
            int offset = plaintext[i] - 65;
            int encoded = key[offset];
            printf("%c", toupper(encoded));
        }
        // The same for lowercase characters but using lowercase 'a' in ASCII to get the offset
        else
        {
            int offset = plaintext[i] - 97;
            int encoded = key[offset];
            printf("%c", tolower(encoded));
        }
    }
}