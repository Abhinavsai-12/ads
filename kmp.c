#include <stdio.h>
#include <string.h>

#define MAX 100

// Function to compute LPS array
void computeLPS(char pattern[], int m, int lps[])
{
    int len = 0;   // length of previous longest prefix suffix
    lps[0] = 0;    // LPS of first element is always 0

    int i = 1;
    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Function to perform KMP search
void KMPSearch(char text[], char pattern[])
{
    int n = strlen(text);
    int m = strlen(pattern);

    int lps[MAX];
    computeLPS(pattern, m, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern

    while (i < n)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main()
{
    char text[MAX], pattern[MAX];

    printf("Enter the text: ");
    scanf("%s", text);

    printf("Enter the pattern: ");
    scanf("%s", pattern);

    KMPSearch(text, pattern);

    return 0;
}
