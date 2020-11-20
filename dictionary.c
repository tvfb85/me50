#define _GNU_SOURCE
// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

unsigned int hash_value;
unsigned int wordcount = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);

    if (table[index] == NULL)
    {
        return false;
    }

    for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int total = 0;

    for(int i = 0; word[i] != '\0'; i++)
    {
        total += tolower(word[i]);
    }

    return total % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    if (file != NULL)
    {
        char word[LENGTH + 1];

        while (fscanf(file, "%s", word) != EOF)
        {
            node *n = malloc(sizeof(node));

            if (n == NULL) {
                return false;
            }

            strcpy(n->word, word);

            int index = hash(word);

            n->next = table[index];

            table[index] = n;

            wordcount++;
        }
        fclose(file);
        return true;
    }
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int unloaded = 0;

    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

        unloaded++;
    }

    if (unloaded == 26) {
        return true;
    }

    return false;
}
