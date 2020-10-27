#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Find a candidate with a matching name
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Increment vote count for matching candidate
            candidates[i].votes++;
            return true;
        }
    }
    // Return false if no matching candidate is found
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Setup variables to store the highest vote, the number of winners, and array of winners' names
    int highestvote = 0;
    int winnercount = 0;
    string winners[MAX];

    // Loop through candidates and record the highest vote and add the candidate's name to array of winners
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > highestvote)
        {
            highestvote = candidates[i].votes;
            winners[0] = candidates[i].name;
        }
    }

    // Set winner count to 1 to account for the winner with the highest vote
    winnercount++;

    // Loop the candidates again and look for candidates with an equal vote tally
    for (int i = 0; i < candidate_count; i++)
    {
        // If any candidate's vote tally matches the highest votes recorded, add them to the array of winners' names, and increment the count of winners
        if (candidates[i].name != winners[0] && candidates[i].votes == highestvote)
        {
            winners[winnercount] = candidates[i].name;
            winnercount++;
        }
    }

    // Print each winner's name
    for (int i = 0; i < winnercount; i++)
    {
        printf("%s\n", winners[i]);
    }

    return;
}

