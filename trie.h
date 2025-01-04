#ifndef TRIE_H
#define TRIE_H

#define ALPHABET_SIZE 26
#define MAX_WORD_LENGTH 100

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
} TrieNode;

TrieNode* createNode();
void insert(TrieNode *root, const char *word);
int search(TrieNode *root, const char *word);
void getSuggestions(TrieNode *root, const char *prefix);
void loadDictionary(TrieNode *root, const char *filename);

#endif 