//<<<<<<<<< saved version
/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include<stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dictionary.h"

// size of hashtable
#define HASHTABLE 27

//word counter
int counter = 0;

// create nodes for linked list
typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
}
node;

//set the first node to NULL
node* root = NULL;

// create a hashtable with NULL content
node* hashtable[HASHTABLE] = {NULL};

// hash function created by eduardjamin, source github
int hash(const char* word)
{
    // set default position to 0
    int pos = 0;

    // iritate
    for (int i = 0; word[i] != '\0'; i++)
    {
        // look for lower case words
        pos += tolower(word[i]);
    }
    // return mod
    return pos % HASHTABLE;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // temporary variable storing lower case words
    char temp[LENGTH + 1];
    
    //create a new pointer 
    node* p_node;
    
    //keep track on the lenght f the word
    int len = strlen(word);
    
    
    //iritate throught bthe lenght of the word
    for(int i = 0; i < len; i++)
    {   
        temp[i] = tolower(word[i]);
    }
    
    //end with the ending sign
    temp[len] = '\0';
    
    //know the current position 
    int pos = hash(temp);
    
    // if hashtable is empty at that particular position, return false
    if (hashtable[pos] == NULL)
    {
        return false;
    }
    
    // create pointer to compare to word
    p_node = hashtable[pos];
    
    // searching function
    while (p_node != NULL)
    {
        //compare to the word
        if (strcmp(temp, p_node->word) == 0)
        {
            return true;
        }
        
        p_node = p_node->next;
    }
    
    // word has not been found return false
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
  //read the file
    FILE* fp = fopen(dictionary, "r");
    
    //create an array of the size of lenght of the word + ending character
    char word[LENGTH+1];
    
    // check if not NULL
    if (fp == NULL)
    {
        return false;
    }
    
    // iritate throught the dixtionary unless EOF 
    while (fscanf(fp, "%s", word) != EOF)
    {
        // create a  first pointer
        node* new = malloc(sizeof(node));
        
        // copy word into pointer
        strcpy(new->word, word);

        // hash the word
        int hashed = hash(word);

        // if new belongs at head, prepend
        if (hashtable[hashed] == NULL)
        {
            hashtable[hashed] = new;
            new->next = NULL;
        }

        // if not belong to head
        else
        {
            new->next = hashtable[hashed];
            hashtable[hashed] = new;
        }

        // count words
        counter++;
    }

    //exit
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
   //return number of words
    if (counter > 0)
    {
        return counter;
    }
     
    
    else
        return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < HASHTABLE; i++)
    {
        node* pointer = hashtable[i];
        while (pointer != NULL)
        {
            // linked list connection
            node* temp = pointer;
            pointer = pointer->next;
            free(temp);
        }
    }
  
    return true;
    return (EXIT_SUCCESS);
}
//=========

//>>>>>>>>> local version