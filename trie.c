#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "trie.h"

TrieNode* createNode() {
    TrieNode *node = (TrieNode*)malloc(sizeof(TrieNode));
    if (!node) {
        printf("Error: Memory allocation failed for TrieNode\n");
        exit(1);
    }
    node->isEndOfWord = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void insert(TrieNode *root, const char *word) {
    if (!root || !word) {
        printf("Error: Invalid input to insert function\n");
        return;
    }

    TrieNode *current = root;
    for (int i = 0; word[i]; i++) {
        char ch = tolower(word[i]); 
        if (ch < 'a' || ch > 'z') {
            continue; 
        }

        int index = ch - 'a';
        if (!current->children[index]) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    current->isEndOfWord = 1;
}

int search(TrieNode *root, const char *word) {
    if (!root || !word) {
        printf("Error: Invalid input to search function\n");
        return 0;
    }

    TrieNode *current = root;
    for (int i = 0; word[i]; i++) {
        char ch = tolower(word[i]); 
        if (ch < 'a' || ch > 'z') {
            continue; 
        }

        int index = ch - 'a';
        if (!current->children[index]) {
            return 0;
        }
        current = current->children[index];
    }
    return current->isEndOfWord;
}

void collectSuggestions(TrieNode *node, char *prefix, int length) {
    if (!node) return;

    if (node->isEndOfWord) {
        prefix[length] = '\0';
        printf("%s\n", prefix);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            prefix[length] = 'a' + i;
            collectSuggestions(node->children[i], prefix, length + 1);
        }
    }
}

void getSuggestions(TrieNode *root, const char *prefix) {
    if (!root || !prefix) {
        printf("Error: Invalid input to getSuggestions function\n");
        return;
    }

    TrieNode *current = root;
    for (int i = 0; prefix[i]; i++) {
        char ch = tolower(prefix[i]); 
        if (ch < 'a' || ch > 'z') {
            printf("No suggestions found for '%s'\n", prefix);
            return;
        }

        int index = ch - 'a';
        if (!current->children[index]) {
            printf("No suggestions found for '%s'\n", prefix);
            return;
        }
        current = current->children[index];
    }

    char buffer[MAX_WORD_LENGTH];
    strcpy(buffer, prefix);
    printf("Suggestions for '%s':\n", prefix);
    collectSuggestions(current, buffer, strlen(prefix));
}

void loadDictionary(TrieNode *root, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file '%s'\n", filename);
        exit(1);
    }

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF) {
        insert(root, word);
    }

    fclose(file);
    printf("Dictionary loaded successfully!\n");
}