#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main(int argc, char **argv)
{
    squeeze(argv[1], argv[2]);
    printf("%s\n", argv[1]);
    return 0;
}

void squeeze(char s1[], char s2[])
{
    // Delete each char in s1 that matches any char in s2
    int i, j, k; // k iterates through s2, i and j iterate through s1 with j <= i
    
    for (k = 0; s2[k] != '\0'; k++) {
        // this inner part is just squeeze for chars
        for (i = j = 0; s1[i] != '\0'; i++) {
            if (s1[i] != s2[k])
                s1[j++] = s1[i];
        }
        s1[j] = '\0';
    }

    return;
}