// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

void free_list(node *list);

// Number of buckets in hash table
const unsigned int N = 131071;

// Hash table
node *table[N];

// Dictionary size
unsigned int dictionary_size = 0;
unsigned int bucket_value;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // get hash bucket
    bucket_value = hash(word);

    // iterate bucket comparing word
    node *list = table[bucket_value];
    for (node *cursor = list; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // hash function based on: https://cp-algorithms-brasil.com/strings/striing.html#:~:text=Para%20a%20convers%C3%A3o%2C%20precisamos%20da,%3Dhash(t))
    int p = 53;
    unsigned int hash_value = 0;
    int p_pow = 1;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash_value = (hash_value + (tolower(word[i]) - 'a' + 1) * p_pow) % N;
        p_pow = (p_pow * p) % N;
    }
    return hash_value;


}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open dictionary words in file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // buffer to dictionary word
    char word[LENGTH + 1];
    // read each dictionary word
    while (fscanf(file, "%s", word) != EOF)
    {
        dictionary_size++;
        // allocate mamory
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            unload();
            return false;
        }
        // build node

        strcpy(n->word, word);
        n->next = NULL;

        bucket_value = hash(word);

        // insert new word to linked list
        node *linkedList = table[bucket_value];
        if (linkedList == NULL)
        {
            linkedList = n;
        }
        else
        {
            n->next = linkedList;
            linkedList = n;
        }
        table[bucket_value] = linkedList;
    }

    // close file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // freeing all dictionary list
    for (int i = 0; i < N; i++)
    {
        node *list = table[i];
        free_list(list);
    }

    return true;
}

// Free 'list' and all links of `list`.
void free_list(node *list)
{
    // handle base case
    if (list == NULL)
    {
        return;
    }

    // free list nodes
    free_list(list->next);

    // free node
    free(list);
}
