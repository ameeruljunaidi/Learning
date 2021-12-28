#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
  string name;
  int votes;
  bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
  // Check for invalid usage
  if (argc < 2)
  {
    printf("Usage: runoff [candidate ...]\n");
    return 1;
  }

  // Populate array of candidates
  candidate_count = argc - 1;
  if (candidate_count > MAX_CANDIDATES)
  {
    printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
    return 2;
  }
  for (int i = 0; i < candidate_count; i++)
  {
    candidates[i].name = argv[i + 1];
    candidates[i].votes = 0;
    candidates[i].eliminated = false;
  }

  voter_count = get_int("Number of voters: ");
  if (voter_count > MAX_VOTERS)
  {
    printf("Maximum number of voters is %i\n", MAX_VOTERS);
    return 3;
  }

  // Keep querying for votes
  for (int i = 0; i < voter_count; i++)
  {

    // Query for each rank
    for (int j = 0; j < candidate_count; j++)
    {
      string name = get_string("Rank %i: ", j + 1);

      // Record vote, unless it's invalid
      if (!vote(i, j, name))
      {
        printf("Invalid vote.\n");
        return 4;
      }
    }

    printf("\n");
  }

  // Keep holding runoffs until winner exists
  while (true)
  {
    // Calculate votes given remaining candidates
    tabulate();

    // Check if election has been won
    bool won = print_winner();
    if (won)
    {
      break;
    }

    // Eliminate last-place candidates
    int min = find_min();
    bool tie = is_tie(min);

    // If tie, everyone wins
    if (tie)
    {
      for (int i = 0; i < candidate_count; i++)
      {
        if (!candidates[i].eliminated)
        {
          printf("%s\n", candidates[i].name);
        }
      }
      break;
    }

    // Eliminate anyone with minimum number of votes
    eliminate(min);

    // Reset vote counts back to zero
    for (int i = 0; i < candidate_count; i++)
    {
      candidates[i].votes = 0;
    }
  }
  return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
  // Voter: which number of voter is currently voting
  // Rank: which rank is the voter indicating their preference for
  // Name: which candidate are they voting for
  // If name is a match, update the preference
  // Preference[i][j] is voter's i preference at jth rank
  for (int i = 0; i < candidate_count; i++)
  {
    if (strcmp(name, candidates[i].name) == 0)
    {
      preferences[voter][rank] = i;
      return true;
    }
  }
  return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
  // Udpate vote counts for all non-eliminated candidates
  // At each stage, every voter effectively votes for their top preferred candidate
  // When a candidate is eliminated, the voted goes to the second one
  for (int i = 0; i < voter_count; i++)
  {
    int check = 0;
    for (int k = 0; k < candidate_count; k++)
    {
      for (int j = 0; j < candidate_count; j++)
      {
        bool candidate_eliminated = candidates[j].eliminated;
        bool voter_voted_for_candidate = preferences[i][k] == j;
        if (!candidate_eliminated && voter_voted_for_candidate)
        {
          candidates[j].votes++;
          check++;
        }
      }
      if (check > 0)
        break;
    }
  }
  return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
  // If a candidate has the majority, then print
  // but if no candidate has a majority yet, then just skip
  for (int i = 0; i < candidate_count; i++)
  {
    if (candidates[i].votes > voter_count / 2)
    {
      printf("%s\n", candidates[i].name);
      return true;
    }
  }
  return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
  // Only do this for candidate that has not been eliminated yet
  int min_vote = MAX_VOTERS; // Keep track of index of candidate with min vote
  for (int i = 0; i < candidate_count; i++)
  {
    bool candidate_eliminated = candidates[i].eliminated;
    bool less = candidates[i].votes < min_vote;
    if (!candidate_eliminated && less)
      min_vote = candidates[i].votes;
  }
  return min_vote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
  // This accepts the minimum number of votes min as input
  // If all candidates have min amount of votes, then it is a tie
  int candidate_running = 0;
  int tie_check = 0;
  for (int i = 0; i < candidate_count; i++)
  {
    bool candidate_eliminated = candidates[i].eliminated;
    bool candidate_vote_is_min = candidates[i].votes == min;
    if (!candidate_eliminated)
    {
      candidate_running++;
      if (candidate_vote_is_min)
        tie_check++;
    }
  }
  bool all_candidate_min_vote = tie_check == candidate_running;
  if (all_candidate_min_vote)
  {
    return true;
  }
  return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
  for (int i = 0; i < candidate_count; i++)
  {
    if (candidates[i].votes == min)
    {
      candidates[i].eliminated = true;
    }
  }
  return;
}
