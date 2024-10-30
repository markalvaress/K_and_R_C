#include <stdio.h>

// I want to print a histogram of the chars in a string.
// To simplify, let's just say I want all the letters.
int main()
{
    int c, char_freqs[52], i, j; // lower and uppercase

    for (i = 0; i < 52; ++i)
        char_freqs[i] = 0;

    while((c = getchar()) != EOF) {
        if (c >= 'A' && c <= 'Z') {
            ++char_freqs[c-'A'];
        } else if (c >= 'a' && c <= 'z') {
            ++char_freqs[26 + c-'a'];
        }
    }
    
    // Print histogram
    for (i = 0; i < 52; i++) {
        if (i <= 25) {
            putchar(i + 'A');
        } else {
            putchar(i-26 + 'a');
        }
        printf(":\t");

        for (j = 0; j < char_freqs[i]; ++j)
            printf("=");

        printf("\n");
    }

    return 0;
}