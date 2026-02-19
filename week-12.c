#include <stdio.h>
#include <string.h>

#define MAX 256   // Total ASCII characters

// Function to create bad character table
void badCharTable(char pattern[], int m, int badChar[]) {
    int i;

    // Initialize all values as -1
    for (i = 0; i < MAX; i++)
        badChar[i] = -1;

    // Fill actual values of last occurrence
    for (i = 0; i < m; i++)
        badChar[(int)pattern[i]] = i;
}

// Boyer–Moore search function
void boyerMoore(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);

    int badChar[MAX];
    badCharTable(pattern, m, badChar);

    int shift = 0;  // shift of the pattern

    while (shift <= (n - m)) {
        int j = m - 1;

        // Compare from right to left
        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        // If pattern matches
        if (j < 0) {
            printf("Pattern found at index %d\n", shift);

            // Shift pattern
            shift += (shift + m < n) ?
                     m - badChar[text[shift + m]] : 1;
        }
        else {
            // Shift using bad character rule
            int bcIndex = badChar[text[shift + j]];
            shift += (j - bcIndex > 1) ? j - bcIndex : 1;
        }
    }
}

// Main function
int main() {
    char text[100], pattern[50];

    printf("Enter the text: ");
    gets(text);

    printf("Enter the pattern: ");
    gets(pattern);

    boyerMoore(text, pattern);

    return 0;
}
