#include <stdio.h>

// Function to calculate factorial of a non-negative integer
unsigned long long factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    
    return result;
}

// Function to calculate n! / (n - r)!
unsigned long long calculateExpression(int n, int r) {
    if (n < r) {
        return 0; // Invalid input
    }
    
    unsigned long long numerator = factorial(n);
 
    unsigned long long denominator = factorial(n - r);
       printf("Result: %llu\n", numerator);
    printf("Result: %llu\n", denominator);
    
    if (denominator == 0) {
        return 0; // Division by zero
    }
    
    return numerator / denominator;
}

int main() {
    int n = 26; // Replace with the desired value of n
    int r = 2;  // Replace with the desired value of r
    
    unsigned long long result = calculateExpression(n, r);
    
    printf("Result: %llu\n", result);
    
    return 0;
}
