#include <stdio.h>
#define NCOLS 8 // there will be tabstops after this many columns
#define MAXLINE 1000

int getline(char s[], int lim);
int detab(char s[]);

// I want to replace all tabs with the appropriate amount of spaces to get to the next tabstop
int main()
{
    char line[MAXLINE];
    int len;

    while ((len = getline(line, MAXLINE)) > 0) {
        detab(line);
        printf("%s", line);
    }
}

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

int detab(char s[])
{
    // need to keep track of what current tab stop I'm at
    int i, j, k, l; // i will be the position in s[], and j will be the position in t[]
    char t[MAXLINE];

    j = 0;
    for (i = 0; s[i] != EOF && s[i] != '\n'; ++i) {
        if (s[i] == '\t') {
            l = NCOLS*(j/NCOLS + 1); // this is the next tabstop position we want to skip to
            for (k = j; k < l; ++k) { // fill in the space in between with blanks
                t[k] = ' ';
            }
            j = l; // set the next position in t[] to the position we've skipped to
        } else {
            t[j] = s[i];
            ++j;
        }
    }

    if (s[i] = '\n') {
        t[j] = s[i];
        ++j;
    }

    // now overwrite s with t
    for (k = 0; k < j; ++k) { // j accurately counts the length of t, so t goes t[0] to t[j-1]
        s[k] = t[k];
    }

    s[j] = '\0';

    return(0);
}

