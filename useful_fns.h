#include <stdio.h>

// Gets a line of text from the user, stores it in s, and returns the length of the line
int getline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void readFile(char s[], char path[], int max_prog_length) {
    FILE *filePointer = NULL;
    int thisCharacter;
    int i = 0;

    filePointer = fopen(path, "r");

    // read a single char in for each loop iteration
    while ((thisCharacter = fgetc(filePointer)) != EOF && i < max_prog_length) {
        s[i] = thisCharacter;
        i++;
    }

    // close the file
    fclose(filePointer);
    // set the pointer to null to reset it and free the memory
    filePointer = NULL;

    return;
}