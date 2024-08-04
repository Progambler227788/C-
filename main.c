#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define HASH_SIZE 100003

typedef struct Node {
    char word[MAX_WORD_LENGTH];
    struct Node* next;
} Node;

Node* hashTable[HASH_SIZE];

unsigned int hash(const char *word) {
    unsigned int hash = 0;
    while (*word) hash = (hash << 5) + *word++;
    return hash % HASH_SIZE;
}

void insert(const char *word) {
    unsigned int h = hash(word);
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    newNode->next = hashTable[h];
    hashTable[h] = newNode;
}

bool isWordInDictionary(const char *word) {
    unsigned int h = hash(word);
    Node *current = hashTable[h];
    while (current) {
        if (strcmp(current->word, word) == 0) return true;
        current = current->next;
    }
    return false;
}

void loadDictionary() {
    FILE *file = fopen("dictionary", "r");
    if (!file) {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }

    char buffer[MAX_WORD_LENGTH];
    long int count = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;
        for (int i = 0; buffer[i]; i++) buffer[i] = toupper(buffer[i]);
        count++;
      //  printf("Loaded: %s\n", buffer); // Debug Statement
        insert(buffer);
    }
    printf("Count: %s\n", count); // Debug Statement
    fclose(file);
}

void checkPermutation(int *mapping, char **input, int inputCount, int *solutions, int *lookUps) {
    char word[MAX_WORD_LENGTH];
    for (int i = 0; i < inputCount; i++) {
        int length = strlen(input[i]);
        for (int j = 0; j < length; j++) {
            word[j] = 'A' + mapping[input[i][j] - '0'];
        }
        word[length] = '\0';
      //  printf("Generated Word: %s\n", word); // Debug Statement
        
        (*lookUps)++;
        if (!isWordInDictionary(word)) {
            return;
        }
    }
    (*solutions)++;
}

void findSolutions(int *mapping, bool *used, int level, int maxLevel, char **input, int inputCount, int *solutions, int *lookUps) {
    if (level == maxLevel) {
        printf("Mapping at level %d: ", level); // Debug Statement
        for(int i = 0; i < maxLevel; i++)
            printf("%d ", mapping[i]);
        printf("\n");
        
        checkPermutation(mapping, input, inputCount, solutions, lookUps);
        return;
    }
    
    for (int i = 0; i < 10; i++) {
        if (!used[i]) {
            used[i] = true;
            mapping[level] = i;
            findSolutions(mapping, used, level + 1, maxLevel, input, inputCount, solutions, lookUps);
            used[i] = false;
        }
    }
}

int uniqueDigits(char **input, int inputCount) {
    bool digits[10] = {false};
    for (int i = 0; i < inputCount; i++) {
        for (int j = 0; j < strlen(input[i]); j++) {
            digits[input[i][j] - '0'] = true;
        }
    }
    
    int count = 0;
    for (int i = 0; i < 10; i++) {
        if (digits[i]) count++;
    }
    
    return count;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <numbers>\n", argv[0]);
        return 1;
    }
    
    printf("Received Inputs: "); // Debug Statement
    for(int i = 1; i < argc; i++)
        printf("%s ", argv[i]);
    printf("\n");

    loadDictionary();

    int mapping[10];
    bool used[10] = {false};

    int solutions = 0;
    int lookUps = 0;

    int actualDigits = uniqueDigits(argv + 1, argc - 1);
    double possiblePermutations = 1;
    for (int i = 0; i < actualDigits; i++) {
        possiblePermutations *= (10 - i);
    }

    clock_t start = clock();
    findSolutions(mapping, used, 0, actualDigits, argv + 1, argc - 1, &solutions, &lookUps);
    clock_t end = clock();
    double cpuTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Found %d solutions, CPU Time = %.6f, Dictionary Look Ups = %d\n", solutions, cpuTime, lookUps);
    printf("Possible Permutations = %.2f, Actual Completed Permutations = %d (%.6f%%)\n", possiblePermutations, lookUps, (100.0 * lookUps) / possiblePermutations);

    // Cleanup dictionary
    for (int i = 0; i < HASH_SIZE; i++) {
        Node *current = hashTable[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}
