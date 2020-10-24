#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void bubble_sort(pair arr[], int size);
bool creates_cyle(int winner, int loser);
bool winner_exists(int count, string winners[]);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    bubble_sort(pairs, pair_count);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!creates_cyle(pairs[i].winner, pairs[i].loser))
        {
            printf("didnt create cycle");
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    printf("locked first pair: %s\n", locked[0][1] ? "true" : "false");
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int count = 0;
    string winners[MAX];

    for (int i = 0; i < candidate_count; i++)
    {
        // bool has_arrow_pointer = false;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                // has_arrow_pointer = true;
                if (!winner_exists(count, winners))
                {
                    winners[count] = candidates[i];
                    count++;
                }
            }
        }

        // for (int k = 0; k < candidate_count; k++)
        // {
        //     if (!has_arrow_pointer && locked[i][k] == true)
        //     {
        //         printf("%s\n", candidates[i]);
        //     }
        // }
    }

   for (int k = 0; k < count; k++)
    {
        printf("%s\n", winners[k]);
    }
    return;
}

bool creates_cyle(int winner, int loser)
{
    printf("winner: %i, loser: %i\n", winner, loser);
    printf("locked loser winner %i\n", locked[loser][winner]);
    if (locked[loser][winner] == true)
    {
        printf("shouldnt get here1");
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        printf("looping, locked i winner %i\n", locked[i][winner]);
        if (locked[i][winner] == true)
        {
            printf("shouldnt get here");
            return creates_cyle(i, loser);
        }
    }
    return false;
}


void bubble_sort(pair arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        printf("SORTING pairs, winner: %i, loser: %i\n", arr[i].winner, arr[i].loser);
        int diff = preferences[arr[i].winner][arr[i].loser] - preferences[arr[i].loser][arr[i].winner];

        printf("the next pair winner votes: %i, the next pair loser votes: %i\n", preferences[arr[i + 1].winner][arr[i + 1].loser], preferences[arr[i + 1].loser][arr[i + 1].winner]);
        int diff1 = preferences[arr[i + 1].winner][arr[i + 1].loser] - preferences[arr[i + 1].loser][arr[i + 1].winner];

        printf("diff: %i, %i\n", diff, diff1);
        if (diff < diff1)
        {
            printf("sorting!! %i, %i\n", arr[i].winner, arr[i - 1].winner);
            pair temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
    }

	if (size - 1 > 1) {
		bubble_sort(arr, size - 1);
	}
}

bool winner_exists(int count, string winners[])
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(winners[i], candidates[i]) == 0)
        {
            return true;
        }
    }
    return false;
}