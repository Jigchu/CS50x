#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
void mergesort(int start, int end);
void merge(int start, int mid, int end);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

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
    // Check if the name is valid
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i]))
        {
            // If valid updates ranks and returns true
            ranks[rank] = i;
            return true;
        }
    }

    // Else returns false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Iterate through ranks
    for (int i = 0; i < candidate_count; i++)
    {
        // Gets candidate in ranks[i]
        int candidate = ranks[i];

        // Iterate through preferences[i] where i is the candidate
        for (int j = 0; j < candidate_count; j++)
        {
            // Add a vote to preferences[i][j]
            preferences[candidate][j]++;
            // Check if preferences[i][j] where i == j
            // Check if preferences[i][j] where j is higher in rank than i
            for (int k = 0; k <= i; k++)
            {
                // Gets candidate in ranks[k]
                int temp_candidate = ranks[k];

                // If any of the previous conditions are met preference[i][j]--
                if (temp_candidate == j)
                {
                    preferences[candidate][j]--;
                }
            }
        }
    }

    // Return NULL
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Set pair_count var to 0
    pair_count = 0;

    // Initialises a 2d array to check if preferences[i][j] has been visited
    bool visited[candidate_count][candidate_count];

    // Iterates through preferences[i][j]
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Checks if preferences[i][j] has been visited
            if (visited[i][j])
            {
                // If it has been visited skip it
                continue;
            }

            // Else get values for preferences[i][j] and preferences[j][i]
            int val1 = preferences[i][j];
            int val2 = preferences[j][i];

            // Compare val1 and val2 and update pairs array with corresponding info
            if (val1 > val2)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
            }
            else if (val2 > val1)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
            }
            // If they are equal then remove one from pair_count to offset the ++ later in code
            else
            {
                pair_count--;
            }

            // Updates pair_count var
            pair_count++;

            // Marks preferences[i][j] and preferences[j][i] as visited
            visited[i][j] = true;
            visited[j][i] = true;

        }
    }
    // Ends function
    return;
}

// Sort pairs in decreasing order by strength of victory using merge sort
void sort_pairs(void)
{
    // Sorts pair
    mergesort(0, pair_count - 1);

    // Ends function
    return;
}

// Merge sort using recursion
void mergesort(int start, int end)
{
    // Break case
    if (start == end)
    {
        return;
    }

    // Finds middle of list
    int mid = (start + end) / 2;

    mergesort(0, mid);                  // Sorts left part
    mergesort(mid + 1, end);            // Sorts right part

    // Merges left and right part
    merge(start, mid, end);

    // Ends function
    return;
}

// Function to merge items in mergesort
void merge(int start, int mid, int end)
{
    // Initialise auxilery array
    pair aux[end + 1];

    // Initialise pointers
    int i = 0;
    int j = mid + 1;
    int k = 0;

    // Merges items until we reach the end of one list
    while (i <= mid && j <= end)
    {
        // Gets difference in votes for both pairs
        int val1 = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        int val2 = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];

        // Checks for larger difference (prioritises earlier place in array if both vals are same) and places pair in aux in sorted manner
        if (val1 >= val2)
        {
            aux[k] = pairs[i];
            i++;
        }
        else if (val2 > val1)
        {
            aux[k] = pairs[j];
            j++;
        }

        // Increments k by one for next pair in aux
        k++;
    }

    // Once we reach end of one list, assume that the rest of other list is sorted and copy into aux
    for (; i <= mid; i++)
    {
        aux[k] = pairs[i];
        k++;
    }

    for (; j <= end; j++)
    {
        aux[k] = pairs[j];
        k++;
    }

    // Copies sorted vals in aux into pairs
    for (k = 0; k <= end; k++)
    {
        pairs[k] = aux[k];
    }

    // Ends function
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Iterate through pairs
    for (int i = 0; i < pair_count; i++)
    {
        // Saves pair in temporary variable
        pair temp = pairs[i];

        // Initialises stack with the loser of temp as first
        int stack[pair_count];
        stack[0] = temp.loser;

        // Index for stack
        int k = 1;

        // Var to keep of track of presence of cycle
        bool cycle = false;

        // Checking for cycle
        while (stack[0] && !cycle)
        {
            // Assigns last item in stack to curr_edge var
            k--;
            int curr_edge = stack[k];
            stack[k] = '\0';

            // Iterate through locked to find arrows pointing to other edges
            for (int j = 0; j < candidate_count; j++)
            {
                // Checks if there is an arrow
                if (locked[curr_edge][j])
                {
                    // Checks for cycle
                    if (temp.winner == j)
                    {
                        cycle = true;
                        break;
                    }
                    else
                    {
                        // Adds edge pointed at to stack
                        stack[k] = j;
                        k++;
                    }
                }
            }
        }

        // If there is a pair continue else lock
        if (cycle)
        {
            continue;
        }
        else if (!cycle)
        {
            locked[temp.winner][temp.loser] = true;
        }
    }

    // Ends function
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Bool array to check for candidates who have been locked over
    bool pointed[candidate_count];

    // Iterate through locked
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // if locked[i][j] is true update pointed arr
            if (locked[i][j])
            {
                pointed[j] = true;
            }
        }
    }

    // Iterate through pointed
    for (int i = 0; i < candidate_count; i++)
    {
        // Checks for candidate without anything pointing at them
        if (!pointed[i])
        {
            // Prints out candidate
            printf("%s\n", candidates[i]);
        }
    }

    // Ends function
    return;
}