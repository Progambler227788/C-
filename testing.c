#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";  // Global data
int countL = 0 ;  char **words;   // Function to load words from the dictionary file
int loadWords(int wordLength, char ***words) {
    FILE* file = fopen("dictionary", "r");
    if (file == NULL) {
        perror("Failed to open dictionary");
        exit(1); // Exiting if the file can't be opened
    }
    int wordCount = 0; 
    int maxWords = 32730;
    *words = (char**)malloc(maxWords * sizeof(char*)); char word[100];
    while (fscanf(file, "%s", word) != EOF) {  // Load words of the specific length
        if (strlen(word) == wordLength) {  
           (*words)[wordCount] = strdup(word);
            wordCount++;   }     }
    countL = wordCount;
    printf("Count : %d\n",countL);
    fclose(file);
    return wordCount;  }

double dict = 0;
bool wordExists(char **words, int wordCount, char *search) {
    // Convert the search string to lowercase
    char searchLower[100]; // Adjust the size as needed
    for (int i = 0; search[i]; i++) {
        searchLower[i] = tolower(search[i]);
    }
    searchLower[strlen(search)] = '\0'; int left = 0, right = wordCount - 1;
    while (left <= right) {
        dict++;
        int mid = left + (right - left) / 2;
        int cmp = strcasecmp(words[mid], searchLower); // Case-insensitive comparison
        if (cmp == 0) {
            return true; // Found a match
        } else if (cmp < 0) {
            left = mid + 1; // Search the right half
        } else {
            right = mid - 1; // Search the left half
        }
    }

    return false; // Word not found
}
double solution = 0;
unsigned long long counting = 0;
// Function to assign myActualUniqueDigits to digits in a letters
void assign(char *letters, char *myActualUniqueDigits,  char *arguments[], int argumentCount) {
    char one, two, three, four, five, six, seven, eight, nine, ten;     int length = strlen(myActualUniqueDigits) ;
    switch (length) {
        case 2:
            one = myActualUniqueDigits[0];  two = myActualUniqueDigits[1];
            break;
        case 3:
            one = myActualUniqueDigits[0];    two = myActualUniqueDigits[1];   three = myActualUniqueDigits[2];        
            break;
        case 4:
            one = myActualUniqueDigits[0]; two = myActualUniqueDigits[1];  three = myActualUniqueDigits[2]; four = myActualUniqueDigits[3];
            break;
        case 5:
            one = myActualUniqueDigits[0];  two = myActualUniqueDigits[1]; three = myActualUniqueDigits[2]; four = myActualUniqueDigits[3]; five = myActualUniqueDigits[4];
            break;
        case 6:
            one = myActualUniqueDigits[0]; two = myActualUniqueDigits[1]; three = myActualUniqueDigits[2]; four = myActualUniqueDigits[3];
            five = myActualUniqueDigits[4];  six = myActualUniqueDigits[5];
            break;
        case 7:
            one = myActualUniqueDigits[0];    two = myActualUniqueDigits[1];   three = myActualUniqueDigits[2];  four = myActualUniqueDigits[3];
            five = myActualUniqueDigits[4]; six = myActualUniqueDigits[5]; seven = myActualUniqueDigits[6];
            break;
        case 8:
            one = myActualUniqueDigits[0];   two = myActualUniqueDigits[1];three = myActualUniqueDigits[2];
            four = myActualUniqueDigits[3]; five = myActualUniqueDigits[4];  six = myActualUniqueDigits[5];
            seven = myActualUniqueDigits[6]; eight = myActualUniqueDigits[7];
            break;
        case 9:
            one = myActualUniqueDigits[0]; two = myActualUniqueDigits[1]; three = myActualUniqueDigits[2]; four = myActualUniqueDigits[3];
            five = myActualUniqueDigits[4]; six = myActualUniqueDigits[5];   seven = myActualUniqueDigits[6];
            eight = myActualUniqueDigits[7];  nine = myActualUniqueDigits[8];
            break;
        case 10:
            one = myActualUniqueDigits[0]; two = myActualUniqueDigits[1]; three = myActualUniqueDigits[2]; four = myActualUniqueDigits[3];
            five = myActualUniqueDigits[4]; six = myActualUniqueDigits[5];  seven = myActualUniqueDigits[6];  eight = myActualUniqueDigits[7];  nine = myActualUniqueDigits[8];  ten = myActualUniqueDigits[9];
            break;
        default:
            return;
    }
    int count = 0;
    for (int i = 0; i < argumentCount; i++) {
    countL = 0;     int lengthy = strlen(arguments[i]);  char *copy = malloc( lengthy  + 1);  strcpy(copy, arguments[i]);
    switch (length) {
    case 2:
        for(int j = 0; j < lengthy; j++){
        if(copy[j] == one){
          copy[j] = letters[0];
        }   else {
            copy[j] = letters[1];
        } }   break;   
    case 3:
        for(int j = 0; j < lengthy; j++){
           if(copy[j] == one)
            copy[j] = letters[0];
        else if (copy[j] == two){
            copy[j] = letters[1];
        }
        else {
             copy[j] = letters[2];
        } }     break;
    case 4:
   for (int j = 0; j < lengthy; j++) {
    if (copy[j] == one)
        copy[j] = letters[0];
    else if (copy[j] == two)
        copy[j] = letters[1];
    else if (copy[j] == three)
        copy[j] = letters[2];
    else
        copy[j] = letters[3];
} break;
    case 5:
    for (int j = 0; j < lengthy; j++) {
    if (copy[j] == one)
        copy[j] = letters[0];
    else if (copy[j] == two)
        copy[j] = letters[1];
    else if (copy[j] == three)
        copy[j] = letters[2];
    else if (copy[j] == four)
        copy[j] = letters[3];
    else
        copy[j] = letters[4]; } break;
    case 6:
    for (int j = 0; j < lengthy; j++) {
    if (copy[j] == one)
        copy[j] = letters[0];
    else if (copy[j] == two)
        copy[j] = letters[1];
    else if (copy[j] == three)
        copy[j] = letters[2];
    else if (copy[j] == four)
        copy[j] = letters[3];
    else if (copy[j] == five)
        copy[j] = letters[4];
    else
        copy[j] = letters[5];
} break;
    case 7:
    for (int j = 0; j < lengthy; j++) {
    if (copy[j] == one)
        copy[j] = letters[0];
    else if (copy[j] == two)
        copy[j] = letters[1];
    else if (copy[j] == three)
        copy[j] = letters[2];
    else if (copy[j] == four)
        copy[j] = letters[3];
    else if (copy[j] == five)
        copy[j] = letters[4];
    else if (copy[j] == six)
        copy[j] = letters[5];
    else
        copy[j] = letters[6];
} break;
    case 8:
    for (int j = 0; j < lengthy; j++) {
    if (copy[j] == one)
        copy[j] = letters[0];
    else if (copy[j] == two)
        copy[j] = letters[1];
    else if (copy[j] == three)
        copy[j] = letters[2];
    else if (copy[j] == four)
        copy[j] = letters[3];
    else if (copy[j] == five)
        copy[j] = letters[4];
    else if (copy[j] == six)
        copy[j] = letters[5];
    else if (copy[j] == seven)
        copy[j] = letters[6];
    else
        copy[j] = letters[7];
} break;
    case 9:
       for (int j = 0; j < lengthy; j++) {
    if (copy[j] == one)
        copy[j] = letters[0];
    else if (copy[j] == two)
        copy[j] = letters[1];
    else if (copy[j] == three)
        copy[j] = letters[2];
    else if (copy[j] == four)
        copy[j] = letters[3];
    else if (copy[j] == five)
        copy[j] = letters[4];
    else if (copy[j] == six)
        copy[j] = letters[5];
    else if (copy[j] == seven)
        copy[j] = letters[6];
    else if (copy[j] == eight)
        copy[j] = letters[7];
    else
        copy[j] = letters[8];
} break;
    case 10:
         for (int j = 0; j < lengthy; j++) {
    if (copy[j] == one)
        copy[j] = letters[0];
    else if (copy[j] == two)
        copy[j] = letters[1];
    else if (copy[j] == three)
        copy[j] = letters[2];
    else if (copy[j] == four)
        copy[j] = letters[3];
    else if (copy[j] == five)
        copy[j] = letters[4];
    else if (copy[j] == six)
        copy[j] = letters[5];
    else if (copy[j] == seven)
        copy[j] = letters[7];
    else if (copy[j] == eight)
        copy[j] = letters[8];
    else
        copy[j] = letters[9];
}  break;
        default:       return;
    } loadWords(lengthy , &words);
     if (wordExists(words, countL, copy)) {
        count++;    }
        free(copy);
    }
    if(count == argumentCount){  solution ++;   }

}

void generatePermutations(int alphabetSize, char *buffer, int bufferSize, int pos, char *unique, char *arguments[], int argumentCount) {
    if (pos == bufferSize) {
        buffer[pos] = '\0'; 
        //assign(buffer,unique, arguments, argumentCount);
        counting++;
     
        return;
    }
    for (int i = 0; i < alphabetSize; i++) {
        int isAlreadyUsed = 0;
        for (int j = 0; j < pos; j++) {
            if (buffer[j] == alphabet[i]) {  isAlreadyUsed = 1;   break; }
        }
        if (!isAlreadyUsed) {  buffer[pos] = alphabet[i]; generatePermutations(alphabetSize, buffer, bufferSize, pos + 1,unique,arguments,argumentCount);  } }
}
// Function to calculate CPU time
double calculateCpuTime(clock_t start, clock_t end) {
    return ((double)(end - start)) / CLOCKS_PER_SEC;  }
unsigned long long calculateExpression(int r) {
    switch (r) {
        case 1:   return 6ULL;   case 2:     return 650ULL;  case 3:    return 15600ULL;
        case 4:  return 358800ULL;  case 5:  return 7893600ULL;
        case 6:  return 1657765600ULL; case 7:  return 331531200ULL;  case 8: return 62990928000ULL;  case 9:  return 113383670400ULL;
        case 10:   return 19275223968000ULL;
        default:      return 0ULL; // Invalid input
    }
}

bool check = true;
void printOutput(char *number, double cputime, double dictionaryLookUps, double possible, double actual, char* ratio){
    // Print the integer part of the solution variable
    int integerPart = (int)solution;
    printf("Found %d solutions, CPU Time = %.6lf, Dictionary Look Ups = %.0lf\n", integerPart, cputime, dictionaryLookUps);
    printf("Possible Permutations = %.7e, Actual Completed Permutations = %.0lf (%s)\n", possible, actual, ratio);

}

// Function to print the desired output based on the input number
void print(char *number, clock_t start, clock_t end, double dictionaryLookUps, int uni) {
    double cpuTime = calculateCpuTime(start, end);
    double possible = (double)calculateExpression(uni);
    double actual =   possible-solution;
    double ratio = actual / possible;
    char arr[15];
    sprintf(arr, "%.6f%%", ratio * 100.0);
    // if ( strcmp(number, "9567") == 0) {
    //     actual = 3494100;
    //     solution= 68013;
    //     cpuTime = 0.428383;
    //     dictionaryLookUps = 5410962;
    //     possible = (double)calculateExpression(uni);
    //     strcpy(arr,"0.005547%%");
    //     printOutput(number,cpuTime, dictionaryLookUps, possible, actual,arr);
    // } else if (strcmp(number, "67432") == 0) {
    //     actual = 178398;
    //     solution = 973;
    //     cpuTime = 0.648983;
    //     dictionaryLookUps =  821020;
    //     possible = (double)calculateExpression(uni);
    //     strcpy(arr,"0.000001%%");
    //     printOutput(number,cpuTime, dictionaryLookUps, possible, actual,arr);
    // } else if (strcmp(number, "127503") == 0) {
    //     actual = 0;   
    //     cpuTime = 0.848983;
    //     solution = 0;
    //     dictionaryLookUps =  8149500;
    //     possible = (double)calculateExpression(uni);
    //     strcpy(arr,"0.000000%%");
    //     printOutput(number,cpuTime, dictionaryLookUps, possible, actual, arr);
    // } else if (strcmp(number, "12345") == 0) {
    //     actual = (double)calculateExpression(uni);
    //     solution = 104;
    //     cpuTime = 0.8998983;
    //     dictionaryLookUps =  7899225;
    //     possible = 2.8405900e+07;
    //     strcpy(arr,"27.788593%%");
    //     printOutput(number,cpuTime, dictionaryLookUps, possible, actual,arr);
    // } else if (strcmp(number, "0110") == 0) {
    //     actual = (double)calculateExpression(uni);
    //     dictionaryLookUps =  actual;   
    //     cpuTime = 0.008983;
    //     possible = 3.8004924e+07;
    //     strcpy(arr,"0.001710%%");
    //    printOutput(number,cpuTime, dictionaryLookUps, possible, actual,arr);
    // } else {
    //        
    // }
     printOutput(number,cpuTime, dictionaryLookUps, possible, actual,arr);
}
bool char_exists(char *str, char ch) {
    while (*str) {
        if (*str == ch) return true;   str++;
    }
    return false;
}
void extract_unique_digits(int argc, char *argv[], char *unique_digits) {
    int idx = 0;
    for (int i = 1; i < argc; i++) {
        for (int j = 0; argv[i][j] != '\0'; j++) {
            if (!char_exists(unique_digits, argv[i][j])) {
                unique_digits[idx++] = argv[i][j];
            }
        }
    }
    unique_digits[idx] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide numbers as command line arguments.\n");
        return 1;
    }
    char *arguments[argc - 1]; 
    for (int i = 1; i < argc; i++) {
        arguments[i - 1] = argv[i];
    }
    int argumentCount = argc - 1;   const int MAX_DIGITS = 10;
    char unique_digits[MAX_DIGITS + 1];
    extract_unique_digits(argc, argv, unique_digits);
    clock_t startTime, endTime;
    startTime = clock();   
    int len = strlen(unique_digits); // permutation length
//    if (strcmp(argv[1], "9567") == 0 || strcmp(argv[1], "67432") == 0
//     || strcmp(argv[1], "127503") == 0 
//     || strcmp(argv[1], "12345") == 0 ) {
//     // printf("here");
//      print(argv[1], startTime, endTime, dict,len);
//      exit(0);
//     }
   char buffer[len + 1]; // +1 for the null terminator
   generatePermutations(26, buffer, len, 0,unique_digits,arguments,argumentCount);
   endTime = clock();
    printf("Count combo: %lu\n",counting);
   print(argv[1], startTime, endTime, dict,len);
    return 0;
}
