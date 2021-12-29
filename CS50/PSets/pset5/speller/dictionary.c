// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
	char word[LENGTH + 1];
	struct node *next;
} node;

// Number of buckets in hash table
// 26 to represent each letter of the english alphabet
const unsigned int N = 26;

// Hash table
node *table[N];

// Keep track of word count
unsigned int word_count = 0;

/**
 * Returns true if word is in dictionary, else false
 *
 * Responsible for going through the dictionary and seeing if that word exists in
 * the dictionary or not
 * This function should be case sensitive
 *
 * Steps given by Brian:
 *  - Hash word to obtain a hash value
 *  - Access linked list at that index in the hash table
 *  - Traverse linked list, looking for the word (use strcasecmp)
 *    strcasecmp compares two strings ignoring case
 * 		- Start with cursor set to first item in linked list
 * 		- Keep moving cursor until you get to NULL, checking each node for the word
 */
bool check(const char *word)
{
	// Implement check function

	// Hash word to obtain hash value
	int index = hash(word);

	// Access linked list at that index in the hash table
	// Traverse linked list with a cursore
	for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
		if (strcasecmp(cursor->word, word) == 0)
			return true;

	return false;
}

/**
 * Hashes word to a number
 *
 * Take a word and return an unique int based on that word
 * Outputs a number corresponding to which bucket to store the word in
 */
unsigned int hash(const char *word)
{
	// Create a hash function
	if (isalpha(*word))
	{
		if (islower(*word))
			return (int)(*word) - 97;
		else
			return (int)(*word) - 65;
	}

	return 0;
}

/**
 * Loads dictionary into memory, returning true if successful, else false
 *
 * Load all the words in the dictionary into a hash table
 * We are going to store all the words in a hash table
 * A hash table is just an array of linked lists
 * A hash function assigns a number of every input
 * * This is where the has function will be used
 * Since we saw that it wasn't use anywhere yet
 *
 * Steps given by Brian:
 * - Open dictionary file
 * 		- Use fopen to open the dictionary file
 * 		- Make sure to check if return value is NULL
 * - Read strings from file one at a time
 * 		- fscanf(file, "%s", word)
 * 		- file the file pointer
 * 		- %s means you want to read in a string
 * 		- word is a character array, something you want to read the word into
 * 		- fscanf will return EOF once it reaches end of file
 * - Create a new node from each word
 * 		- Use malloc
 * 		- Remember to check if NULL
 * 		- Copy word into node using strcpy
 * - Hash word to obtain a hash value
 * 		- Use the hash function
 * 		- Takes a string an return an index
 * - Insert node into hash table at location
 * 		- Be sure to set pointers in the correct order
 * 		- There's a global variable called `table` already
 * 		- The `table` variable is an array of N size where N is 26 to represent each
 * 			letter of the English alphabe
 * 		- Each element of that array is of type node which a string and next attribute
 */
bool load(const char *dictionary)
{
	// Initialize all the pointer in the variable to NULL
	// This should have been done already through the unload function, but just to make sure
	for (int i = 0; i < N; i++)
		// Clear out next
		table[i] = NULL;

	// Open dictionary file
	FILE *loaded = fopen(dictionary, "r");
	if (loaded == NULL)
	{
		printf("Could not open dictionary"); // Print error message
		fclose(loaded);											 // Close the file if NULL
		return false;											 // Return false for unsuccesful
	}

	// Read strings from file one at a time
	// Initialize variable called `word` with max char length of LENGTH + 1
	char word[LENGTH + 1];

	// Loop through file while it is not end of file, perform these instructions
	while (fscanf(loaded, "%s", word) != EOF)
	{
		// Create a new node from each word
		node *n = malloc(sizeof(node)); // Create a pointer and allocate memory
		strcpy(n->word, word);					// Copy word into the word attribute of node
		n->next = NULL;									// Set next attribute/pointer to NULL

		// Hash word to obtain hash value
		int index = hash(word);

		/**
		 * Insert node into hash table at location at table[index]
		 * The type at that index of the table array is a node with a word and next attribute
		 * If the current node has next == NULL, that means that there is nothing there yet
		 * In other words, it would be the first word to go on the table array at that location
		 * If it's the first one, then just change the pointer to point to n (the pointer
		 * to our newly created node)
		 * Else point our next pointer from our newly created node to the first node at the
		 * location at the array
		 * Then point that location in the array to point at our newly created node
		 */
		if (table[index] == NULL)
		{
			// Point to the newly created node
			table[index] = n;
		}
		else
		{
			// Point the next from the newly created node to the first node in the table
			n->next = table[index];

			// Point the location at the table array to the newly created node
			table[index] = n;
		}

		// Add 1 to word count
		word_count++;
	}
	// ! Note that whitespace will be considered a new word
	// Luckily for us, the dictionary file has no whitespace

	fclose(loaded);
	return true;
}

/**
 * Returns number of words in dictionary if loaded, else 0 if not yet loaded
 *
 * Simply return how many words there are in the dictionary
 */
unsigned int size(void)
{
	return word_count;
}

/**
 * Unloads dictionary from memory, returning true if successful, else false
 *
 * Any memory that was allocated in the creation of our data structure now needs
 * to be freed up
 */
bool unload(void)
{
	// Implement unload function
	// Free all malloc'ed word from load function

	for (int i = 0; i < N; i++) // Go through each location in our hash table array
	{
		while (table[i] != NULL) // While the node is not NULL
		{
			node *tmp = table[i]->next; // Create a tmp node to keep track of next nodes
			free(table[i]);							// Free the current node
			table[i] = tmp;							// Reassign pointer to next node from tmp
		}
	}

	// Check if all is NULL
	for (int i = 0; i < N; i++)
		if (table[i] != NULL)
			return false;

	return true;
}
