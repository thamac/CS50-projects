/**************************************************/
/* Name: tries.c                                  */
/* Purpose: Work out k-ary tries search algoritms */
/* Author: D.M.Meijer                             */
/**************************************************/

// Directives
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macros
#define SIZE_OF_ALPHABET 26
#define MAXCHAR 5
#define DEPTH 0

// Struct prototype
typedef struct node
{
    bool is_word;
    struct node *children[SIZE_OF_ALPHABET];
}node;

// Functions prototypes
// Insert function
void insert(char *input);
// Unload functions
bool unload(void);
void unloader(node *current);
// Delete word function
bool is_empty(node *start);
node *del_word(node *start, char *input_word, int depth);
// Print function
void print(node *start, char *word, int depth);
// Search function
void check_word(char *input);


// Root of trie
node *root;

// Buffer to read words
char words[MAXCHAR];

int main(void)
{
    // File with words
    FILE *infile = fopen("words.txt", "r");
    if (!infile)
    {
        printf("Error opening file!\n");
        return 1;
    }

    // Allocate root of trie
    root = malloc(sizeof(node));

    if(root == NULL)
    {
        return 1;
    }

    root->is_word = false;
    for (int i = 0; i < SIZE_OF_ALPHABET; i++)
    {
        root->children[i] = NULL;
    }

    // Add words to the trie
    while (fscanf(infile, "%s", words) == 1)
    {
        node *cursor = root;

        for (int i = 0, len = strlen(words); i < len; i++)
        {
            int index = tolower(words[i]) - 'a';
            if (cursor->children[index] == NULL)
            {
                // Make node
                node *new = malloc(sizeof(node));
                new->is_word = false;
                for (int j = 0; j < SIZE_OF_ALPHABET; j++)
                {
                    new->children[j] = NULL;
                }
                cursor->children[index] = new;
            }
            // Go to node which we may have just been made
            cursor = cursor->children[index];
        }
        // If we are at the end of the word, mark it as being a word
        cursor->is_word = true;
    }

    fclose(infile);

    int end = 1;
    int option;
    char *input;

    while (end != 0)
    {
        option = get_int("What do you want to do:\n0 for ending program\n1 add word\n2 search for word\n3 delete word\n4 print all words\nOption: ");

        switch(option)
        {
            case 0:
                end = 0;
                break;
            case 1:
                input = get_string("Which word do you want to add: ");
                insert(input);
                break;
            case 2:
                input = get_string("Which word to you want to find: ");
                check_word(input);
                break;
            case 3:
                input = get_string("Which word to you want to delete: ");
                root = del_word(root, input, DEPTH);
                break;
            case 4:
                print(root, words, DEPTH);
                break;
        }
    }

    if (!unload())
    {
        printf("Error freeing memory!\n");
        return 1;
    }

    return 0;
}

// Insert node
void insert(char *input)
{
    node *cursor = root;

    for (int i = 0, len = strlen(input); i < len; i++)
    {
        int index = tolower(input[i]) - 'a';

        if (cursor->children[index] == NULL)
        {
            // Make new node
            node *new = malloc(sizeof(node));
            new->is_word = false;

            for (int j = 0; j < SIZE_OF_ALPHABET; j++)
            {
                new->children[j] = NULL;
            }
            cursor->children[index] = new;
        }
        cursor = cursor->children[index];
    }
    cursor->is_word = true;
}

// delete word 
bool is_empty(node *start)
{
    node *cursor = start;

    for (int i = 0; i < SIZE_OF_ALPHABET; i++)
    {
        if (cursor->children[i])
        {
            return false;
        }
    }
    return true;
}

node *del_word(node *start, char *input_word, int depth)
{
    node *cursor = start;

    if (!cursor)
    {
        return NULL;
    }

    if (depth == strlen(input_word))
    {
        if (cursor->is_word)
        {
            cursor->is_word = false;
        }

        if (is_empty(cursor))
        {
            free(cursor);
            cursor = NULL;
        }
        return cursor;
    }

    int index = input_word[depth] - 'a';
    cursor->children[index] = del_word(cursor->children[index], input_word, depth + 1);

    if (is_empty(cursor) && cursor->is_word == false)
    {
        free(cursor);
        cursor = NULL;
    }

    return cursor;
}

// print tries
void print(node *start, char *word, int depth)
{
    node *cursor = start;

    if (cursor->is_word != false)
    {
        word[depth] = '\0';
        printf("%s\n", word);
    }

    int i;
    for (i = 0; i < SIZE_OF_ALPHABET; i++)
    {
        if (cursor->children[i])
        {
            word[depth] = i + 'a';
            print(cursor->children[i], word, depth + 1);
        }
    }
}

// ACCESS FUNCTIONS
// Search function
void check_word(char *input)
{
    node *cursor = root;

    for (int i = 0, len = strlen(input); i < len; i++)
    {
        int index = input[i] - 'a';

        if (!cursor->children[index])
        {
            printf("Didnt found %s\n", input);
            return;
        }
        cursor = cursor->children[index];
    }
    printf("Found %s\n", input);
}

// Unload trie from memory
bool unload(void)
{

    // The recursive function handles all of the freeing
    unloader(root);

    return true;
}

void unloader(node *current)
{

    // Iterate over all the children to see if they point to anything and go
    // there if they do point
    for (int i = 0; i < SIZE_OF_ALPHABET; i++)
    {
        if (current->children[i] != NULL)
        {
            unloader(current->children[i]);
        }
    }

    // After we check all the children point to null we can get rid of the node
    // and return to the previous iteration of this function.
    free(current);
}
