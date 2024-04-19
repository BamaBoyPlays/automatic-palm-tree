#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int count;
    struct Trie *children[26];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *tmp = pTrie;

    int len = strlen(word);

    for (int i = 0; i < len -  1; i++) // Loop through for the word leng
    {
        int index = word[i] - 'a';

        if (tmp->children[index] == NULL) // Find if the letters in the word are empty
        {
            tmp->children[index] = malloc(sizeof(struct Trie));
            tmp->children[index]->count = 0;

            for (int j = 0; j < 26; j++)
            {
                tmp->children[index]->children[j] = NULL;
            }

        }
        tmp = tmp->children[index];
    }

    tmp->count = tmp->count + 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie* tmp = pTrie;

    int len = strlen(word);

    for (int i = 0; i < len; i++) // Loop through for the word leng
    {
        int index = word[i] - 'a';

        if (tmp->children[index] == NULL) // Find if the letters in the word are empty
        {
            return 0;
        }

        tmp = tmp->children[index];
    }

    return tmp->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < 26; i++)
    {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }

    free(pTrie);

    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *root = malloc(sizeof(struct Trie));

    root->count = 0;

    for (int i = 0; i < 26; i++)
    {
        root->children[i] = NULL;
    }

    return root;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *inFile = fopen(filename, "r");

    int numWords = 0;

    fscanf(inFile, "%d", &numWords);

    for (int i = 0; i < numWords; i++)
    {
        char tmp[100];

        fscanf(inFile, "%s", tmp);

        pInWords[i] = strdup(tmp);

    }

    fclose(inFile);

    return numWords;
}

int main(void)
{
	char *inWords[256];
    
    //read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i=0;i<numWords;++i)
    {
        printf("%s\n",inWords[i]);
    }
    
    struct Trie *pTrie = createTrie();
    for (int i=0;i<numWords;i++)
    {
        insert(pTrie, inWords[i]);
    }
    // parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i=0;i<5;i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}