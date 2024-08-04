#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include<ctype.h>
#define MAX_STR_LEN 15 // Maximum length of each string
#define MAX_NUM_STRINGS 127145 // Maximum number of strings to read

char *dictionarydata[MAX_NUM_STRINGS];
int readStringsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1; // Error opening the file
    }

    int numStrings = 0;
    char buffer[MAX_STR_LEN];

    while (numStrings < MAX_NUM_STRINGS && fgets(buffer, sizeof(buffer), file) != NULL) {
        // Remove newline character if present
        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
            
        }

        dictionarydata[numStrings] = strdup(buffer);
        for(int i=0;i<strlen(dictionarydata[numStrings]);i++){
        	dictionarydata[numStrings][i]=dictionarydata[numStrings][i]-32;
		}
        if (dictionarydata[numStrings] == NULL) {
            perror("Error allocating memory");
            return -1; // Error allocating memory
        }

        numStrings++;
    }

    fclose(file);
    return numStrings; // Return the number of strings read
}
bool isMappingValid(char *current, char c, int index) {
    for (int i = 0; i < index; i++) {
        if (current[i] == c) {
            return false; // Already assigned, not valid
        }
    }
    return true; // Valid assignment
}

int counter = 0;
char mapping[10]; // Array to store character mappings for each digit
bool isPresentInDictionary(char *word) {
	//printf("%s\n",word);
    for (int i = 0; i < MAX_NUM_STRINGS; i++) {
        if (dictionarydata[i] != NULL && strcmp(dictionarydata[i], word) == 0) {
            return true; // Word found in dictionary
        }
    }
    return false; // Word not found in dictionary
}
int foundcounter=0;
void generateWord(char *mapping, char *digits, char *originalNumbers){
	int origLength = strlen(originalNumbers);
	int index = strlen(mapping);
	char word[origLength];
	for(int i=0;i<index;i++){
		for(int j=0;j<origLength;j++){
			if(originalNumbers[j]==digits[i]){
				word[j]=mapping[i];
			}
		}
	}
	word[origLength]='\0';
	if(isPresentInDictionary(word))
	{
		foundcounter++;
		printf("%s\n",word);
	}
}
void generateMappingsRecursive(char *digits, char *current, int index, int numDigits, bool used[26],char * originalNumbers) {
    if (index == numDigits) {
    	char tempMapping[numDigits];
        current[index] = '\0'; // Null-terminate the current mapping
        //printf(" (");
        for (int i = 0; i < numDigits; i++) {
            int digit = digits[i] - '0';
            tempMapping[i] = mapping[digit];
        }
        generateWord(tempMapping,digits,originalNumbers);
        //printf(") , ");
        counter++;
        return;
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        if (isMappingValid(current, c, index) && !used[c - 'A']) {
            current[digits[index] - '0'] = c;
            used[c - 'A'] = true;
            mapping[digits[index] - '0'] = c; // Store the mapping
            generateMappingsRecursive(digits, current, index + 1, numDigits, used,originalNumbers);
            used[c - 'A'] = false; // Backtrack
        }
    }
}

void generateAllPossibleMappings(char *digits,char * originalNumbers) {
    int numDigits = strlen(digits);
    char current[10]; // Adjust the size as needed for the maximum number of digits
    bool used[26] = {false}; // Array to track used characters

    generateMappingsRecursive(digits, current, 0, numDigits, used,originalNumbers);
}

int main() {
	
	int numStrings;

    // Replace "input.txt" with your file name
    numStrings = readStringsFromFile("dictionary");

    if (numStrings == -1) {
        printf("Failed to read strings from file.\n");
        return 1;
    }

    printf("Read %d strings from file:\n", numStrings);

    
	char originalNumbers[] = "0110";
	//this manual digits this will be removed by some logic to extract unique digits from originalNumbers Array
	
	char digits[] = "01"; // Replace with your input digits
    generateAllPossibleMappings(digits,originalNumbers);
    printf("total possibilities: %d\n", counter);
    printf("total valid combinitions: %d\n", foundcounter);
    for (int i = 0; i < numStrings; i++) {
        //printf("%s\n", dictionarydata[i]);
        free(dictionarydata[i]); // Free allocated memory for each string
    }

	
    return 0;
}

