#include <stdio.h>
#include "trie.h"

int main() {
    TrieNode *root = createNode();
    if (!root) {
        printf("Error: Failed to create trie root node\n");
        return 1;
    }


    loadDictionary(root, "dictionary.txt");


    while (1) {
        printf("\nMenu:\n");
        printf("1. Search for a word\n");
        printf("2. Get autocomplete suggestions\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Error: Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); 
            continue;
        }

        if (choice == 1) {
            char word[MAX_WORD_LENGTH];
            printf("Enter a word to search: ");
            if (scanf("%s", word) != 1) {
                printf("Error: Invalid input. Please enter a valid word.\n");
                continue;
            }
            printf("Search '%s': %s\n", word, search(root, word) ? "Found" : "Not Found");
        } else if (choice == 2) {
            char prefix[MAX_WORD_LENGTH];
            printf("Enter a prefix for suggestions: ");
            if (scanf("%s", prefix) != 1) {
                printf("Error: Invalid input. Please enter a valid prefix.\n");
                continue;
            }
            getSuggestions(root, prefix);
        } else if (choice == 3) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }


}