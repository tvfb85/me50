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
const unsigned int N = 25;

// Hash table
node *table[N];

// Initialize wordcount variable with default value of 0
int wordcount = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Get hash value for word to be checked
    int index = hash(word);

    // Handle edge case where nothing is yet stored at table index
    if (table[index] == NULL)
    {
        return false;
    }

    // Set a temp node to point at the first node stored at the table index
    // Check each node's word value for a match and return true if found
    // Otherwise reassign the temp node to point at the next node and repeat until temp points at NULL;

    for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }

    // Return false if word is not found in dictionary
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Initialize variable to store ASCII code values
    int total = 0;

    // Loop over each character in word
    for (int i = 0; word[i] != '\0'; i++)
    {
        // Sum lowercase ASCII code values
        total += tolower(word[i]);
    }

    // Return positive index between 0 and 25 (for each alphabetic character)
    return total % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Read file
    FILE *file = fopen(dictionary, "r");

    // Check file exists
    if (file != NULL)
    {
        // Setup word variable with additional space for terminating NUL character
        char word[LENGTH + 1];

        // Read words until end of file
        while (fscanf(file, "%s", word) != EOF)
        {
            // Allocate memory for a new node
            node *n = malloc(sizeof(node));

            // Ensure memory was successfully allocated
            if (n == NULL)
            {
                return false;
            }

            // Copy string into node
            strcpy(n->word, word);

            // Get hash value
            int index = hash(word);

            // Store table index as pointer in node
            n->next = table[index];

            // Store node in table at index of hash value
            table[index] = n;

            // Increment word count
            wordcount++;
        }

        // Close file and return true
        fclose(file);
        return true;
    }

    // Return false if file failed to open
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
    // Keep a count of number of linked lists freed
    int unloaded = 0;

    // Loop over each index in the table
    for (int i = 0; i < N; i++)
    {
        // Create a node to point at the first node at the current table index
        node *cursor = table[i];

        // Loop each node until the cursor node points at NULL
        while (cursor != NULL)
        {
            // Use a temp node to store the cursors current value
            node *tmp = cursor;
            // Resassign cursor to point at the next node
            cursor = cursor->next;
            // Free the temp node
            free(tmp);
        }

        // Increment number of unloaded indexes
        unloaded++;
    }

    // Check memory for all indices has been freed
    if (unloaded == 25)
    {
        return true;
    }

    // Return false if unsuccessful
    return false;
}
