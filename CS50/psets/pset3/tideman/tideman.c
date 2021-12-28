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
} pair;

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
void merge_sort(pair arr[], int l, int m, int r);
void merge_sort_pairs(pair arr[], int l, int r);
void print_pairs(pair arr[], int len);
void print_ranks(int ranks[], int len);
void print_prefrences(int pref[MAX][MAX], int len);
bool circle_created(int cycle_start, int loser);

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

    // Update the preferences
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
  // If name is a match for the name of the candidate
  // Then update the ranks array  to indicate that the voter has the candidate as
  // their rank preference (0 is first preference)
  // ranks[i] represents the user's ith preference
  // Return true if the rank was successfully recorded
  // False if e.g., name is not one of the candidates
  for (int i = 0; i < candidate_count; i++)
  {
    if (strcmp(candidates[i], name) == 0)
    {
      ranks[rank] = i; // Take the index of the candidate rather than the name
      return true;
    }
  }
  return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
  // Function updates the global preference array to add the current voter's preference
  // preferences[i][j] represent the number of voters that prefer candidate i over j
  // Now I have the current user's ranks
  // ranks[i] = int is ith preference and int is candidate's index
  // Need to loop through every ranks at ith element
  // Take the first ranks[0]'s value, let's call this x
  // The the second ranks[1]'s value, let's call this y
  // Add 1 to preferences[x][y]
  // Do this for all ranks at ith element, but gotta skip the first one
  // So increment need to start at 1, not 0
  for (int i = 0; i < candidate_count; i++)
  {
    for (int j = 0; j < candidate_count; j++)
    {
      for (int k = 0; k < candidate_count; k++)
      {
        for (int l = 0; l < candidate_count; l++)
        {
          if (ranks[l] == j && ranks[k] == i)
          {
            if (k < l)
            {
              preferences[i][j]++;
            }
          }
        }
      }
    }
  }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
  // Add all pairs of candidates where one candidate is preferred to the pairs array
  // If it is tied, do not add it to the array
  // update the global variable pair_count to be the numbers of pairs of candidates
  // Pairs should be stored between pairs[0] and pairs[pair_count -1] inclusive
  // Pairs has pairs[i].winner and pairs[i].loser
  // Need to do two loops since it is a 2D array
  // For first one preferences[0][0] should be zero
  // In general if preferences [m][m] where m is equal, should be zero and skipped
  // Then, for preferences[0][1] is how many prefer 0 over 1
  // If preferences[0][1] > preferences[1][0], then add the pair to pairs[0]
  // pairs[0].winner = 0 and pairs[0].loser is 1
  // Add 1 to pair_count counter
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
  // Sort the pairs array in decreasing order of strength of victory
  // Strength of victory is the number of voters who prefer the preferred candidate
  // Order does not matter if multiple pairs have the same strength of victory
  // For every pairs (with pairs_count as increments), get the
  // preferences[winner][loser]
  merge_sort_pairs(pairs, 0, pair_count - 1);
  return;
}

void merge_sort(pair arr[], int l, int m, int r)
{
  // Merges two subarrays of arr[]
  // First subarray is arr[l..m]
  // Second subarray is arr[m+1..r]
  // n1 and n2 are for sizes for the sub arrays
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  // Create temp arrays
  pair left[n1], right[n2];

  // Copy the date to the temp array
  for (i = 0; i < n1; i++)
    left[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    right[j] = arr[m + 1 + j];

  // Merge the temp arrays bay into arr[l...r]
  i = 0; // Initial array of first subarray
  j = 0; // Initial array for second subarray
  k = l; // Initial array for merged subarray
  while (i < n1 && j < n2)
  {
    // Need to compare the strength of victory margin, not the index of the winners and
    // losers
    int left_winner = left[i].winner;
    int left_loser = left[i].loser;
    int right_winner = right[j].winner;
    int right_loser = right[j].loser;
    int left_victor_strength = preferences[left_winner][left_loser];
    int right_victor_strength = preferences[right_winner][right_loser];

    if (left_victor_strength >= right_victor_strength)
    {
      arr[k] = left[i];
      i++;
    }
    else
    {
      arr[k] = right[j];
      j++;
    }
    k++;
  }

  // Sometimes the arrays are not symmetric, one of the conditions above
  // might be untrue before the other
  // Copy the remaining elements of left[], if there are any
  while (i < n1)
  {
    arr[k] = left[i];
    i++;
    k++;
  }

  // Copy the remaining elements of right[], if there are any
  while (j < n2)
  {
    arr[k] = right[j];
    j++;
    k++;
  }
}

void merge_sort_pairs(pair arr[], int l, int r)
{
  // l and r is the left and right index respectively
  // If there is an overlap between left and right index, stop operation
  // This is essentially the base case
  if (l < r)
  {
    // Get the middle index
    int m = l + (r - l) / 2;
    // Sort the left and right halves
    merge_sort_pairs(arr, l, m);
    merge_sort_pairs(arr, m + 1, r);
    merge_sort(arr, l, m, r);
  }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
  // Create the locked graph, adding all the edges in decreasing order of victory
  // to ensure that no cycle is created
  // locked[i][j] means i is locked in over j
  for (int i = 0; i < pair_count; i++)
  {
    if (!circle_created(pairs[i].winner, pairs[i].loser))
    {
      locked[pairs[i].winner][pairs[i].loser] = true;
    }
  }
  return;
}

// Create a function to see if the loser would cause a cycle
bool circle_created(int cycle_start, int loser)
// Example
// [0, 1] -> Locked
// [1, 2] -> Locked
// [2, 0] -> This is where cycle is created
// [2, 3]
{
  // This is base case
  // First stack: cycle_start = 2 and loser = 0 (base case not met);
  // Second stack: cycle_start = 2 and loser = 1 (base case not met);
  // Third stack: cycle_start = 2 and loser = 2 (base case is met)
  if (loser == cycle_start)
  {
    return true;
  }
  for (int i = 0; i < candidate_count; i++)
  {
    // If that loser is already locked as winner at some point in the past
    // First stack: [0, 1] is locked
    // Second stack: [1, 2] is locked
    if (locked[loser][i])
      // First stack: i = 1, which is the loser for next recursion
      // Second stack: i = 2, which is the loser for next recursion
      if (circle_created(cycle_start, i))
        return true;
  }
  return false;
}

int winners[MAX];

// Print the winner of the election
void print_winner(void)
{
  for (int i = 0; i < candidate_count; i++)
  {
    bool check = false;
    for (int j = 0; j < candidate_count; j++)
    {
      // Break inner loop if found a true in the array
      if (locked[j][i] == true)
      {
        check = true;
        break;
      }
    }
    // If check is true, skip this loop
    if (check == true)
    {
      continue;
    }
    else
    {
      printf("%s\n", candidates[i]);
    }
  }
  return;
}

void print_pairs(pair arr[], int len)
{
  for (int i = 0; i < len; i++)
  {
    int winner = arr[i].winner;
    int loser = arr[i].loser;
    int victor_strength = preferences[winner][loser];
    printf("[%i, %i] = %i \n", winner, loser, victor_strength);
  }
}

void print_ranks(int ranks[], int len)
{
  for (int i = 0; i < len; i++)
  {
    printf("%i ", ranks[i]);
  }
  printf("\n");
}

void print_prefrences(int pref[MAX][MAX], int len)
{
  for (int i = 0; i < len; i++)
  {
    for (int j = 0; j < len; j++)
    {
      printf("prefences[%i][%i] = %i ", i, j, pref[i][j]);
    }
  }
}