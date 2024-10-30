#include <stdio.h>

#define IN 1
#define OUT 0
#define MAX_WORD_LENGTH 25

// I want to print a histogram of the lengths of words that a user has entered
int main()
{
    int c, wlength, state, length_frequencies[MAX_WORD_LENGTH], i, j;
    wlength = 0;
    state = OUT;
    for (i = 0; i < MAX_WORD_LENGTH; ++i)
        length_frequencies[i] = 0;

    while((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (state = IN)
                ++length_frequencies[wlength]; // add the word length to the frequency array if we've just gotten to the end of the word
            state = OUT;
            wlength = 0;
        } else {
            ++wlength;
            state = IN;
        }
    }
    
    // Print histogram
    for (i = 0; i < MAX_WORD_LENGTH; i++) {
        printf("%d:\t", i);
        for (j = 0; j < length_frequencies[i]; ++j)
            printf("=");

        printf("\n");
    }

    return 0;
}