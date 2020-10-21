#define _GNU_SOURCE

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

void encodetext(string plaintext, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s KEY\n", argv[0]);
        return 1;
    }

    string key = argv[1];

    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    for (int i = 0; key[i] != '\0'; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters\n");
            return 1;
        }
    }

    char haystack[27];
    haystack[27] = '\0';

    for (int i = 0; key[i] != '\0'; i++)
    {
        char needle[2] = { key[i], '\0' };
        string match = strcasestr(haystack, needle);

        if (match)
        {
            printf("Keys must not contain repeated characters\n");
            return 1;
        }
        else {
            haystack[i] = key[i];
        }
    }

    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    encodetext(plaintext, key);

    printf("\n");
    return 0;
}

void encodetext(string plaintext, string key)
{
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        if (!isalpha(plaintext[i]))
        {
            printf("%c", plaintext[i]);
        }
        else if (isupper(plaintext[i]))
        {
            int offset = plaintext[i] - 65;
            int encoded = key[offset];
            printf("%c", toupper(encoded));
        }
        else
        {
            int offset = plaintext[i] - 97;
            int encoded = key[offset];
            printf("%c", tolower(encoded));
        }
    }
}