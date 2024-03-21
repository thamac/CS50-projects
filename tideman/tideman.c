#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
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
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int array_length = sizeof(pairs) / sizeof(pairs[0]);

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

void merge_sort(pair arr[], int l, int r);
void merge(pair arr[], int l, int m, int r);
bool dfs(int candidate, bool visited[]);

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
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int k = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[k].winner = i;
                    pairs[k].loser = j;
                    k++;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int start_count = 0;
    merge_sort(pairs, start_count, pair_count);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    bool visited[candidate_count];

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            visited[j] = false;
        }

        locked[pairs[i].winner][pairs[i].loser] = true;

        if (dfs(pairs[i].loser, visited) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool is_winner = true;

    for (int i = 0; i < candidate_count; i++)
    {
        is_winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                is_winner = false;
            }
        }
        if (is_winner == true)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

void merge(pair arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    pair L[n1], R[n2];

    for (i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2)
    {
        if ((preferences[L[i].winner][L[i].loser] - preferences[L[i].loser][L[i].winner]) >=
            (preferences[R[j].winner][R[j].loser] - preferences[R[j].loser][R[j].winner]))
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        k++;
        i++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        k++;
        j++;
    }
}

void merge_sort(pair arr[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;

        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

bool dfs(int candidate, bool visited[])
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[candidate][j] == true)
        {
            if (visited[j] == true)
            {
                return false;
            }
            else
            {
                visited[j] = true;
                if (dfs(j, visited) == false)
                {
                    return false;
                }
            }
        }
    }
    return true;
}
