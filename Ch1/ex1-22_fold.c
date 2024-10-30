#include <stdio.h>
#include "../useful_fns.h" // gives us getline()
#define LINELENGTH 25
#define MAXLINE 1000

void fold(char s[], int line_length);

int main()
{
    char line[MAXLINE];
    int len;

    while ((len = getline(line, MAXLINE)) > 0) { 
        fold(line, LINELENGTH);
        printf("%s", line);
    }
    /* I wonder if my no_comments
    will properly deal with
    multiline comments? */

    return 0;
}

// Fold the line s into lines of length up to line_length, separated by \n.
void fold(char s[], int line_length)
{
    int i;
    int last_newline_pos = 0;
    int last_space_pos = 0;

    for (i = 0; s[i] != EOF && s[i] != '\n'; ++i) {
        if (s[i] == ' ') {
            last_space_pos = i;
        }

        if (i - last_newline_pos == line_length) {
            if (last_newline_pos == last_space_pos) { 
                // if this whole line has no spaces, or the space is after more than line_length letters,
                // look for the next space and stick a new line there
                while (s[i] != ' ') {
                    ++i;
                }
                last_space_pos = i;
            }
            s[last_space_pos] = '\n';
            last_newline_pos = last_space_pos;
        }
    }

    return;
}