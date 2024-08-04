#include <stdio.h>
#include <string.h>
unsigned long long count = 0;

void generatePermutations(const char *alphabet, int alphabetSize, char *buffer, int bufferSize, int pos) {
    if (pos == bufferSize) { // If buffer is filled
        buffer[pos] = '\0';
        count++;
        return;
    }
    for (int i = 0; i < alphabetSize; i++) {
        int isAlreadyUsed = 0;
        for (int j = 0; j < pos; j++) {
            if (buffer[j] == alphabet[i]) {
                isAlreadyUsed = 1;
                break;
            }
        }
        if (!isAlreadyUsed) {
            buffer[pos] = alphabet[i];
            generatePermutations(alphabet, alphabetSize, buffer, bufferSize, pos + 1);
        }
    }
}

int main() {
    const char *alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    int permutationLength = 10; // Adjust as needed
    char buffer[permutationLength + 1]; // +1 for the null terminator
    generatePermutations(alphabet, strlen(alphabet), buffer, permutationLength, 0);
    printf("%lu\n", count);
    return 0;
}
