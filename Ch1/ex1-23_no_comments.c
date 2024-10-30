#include <stdio.h>
#include "../useful_fns.h"
#define MAXPROGLENGTH 10000 // to avoid overflow

void remove_comments(char s[], int max_prog_length);

int main()
{
    char prog[MAXPROGLENGTH];
    readFile(prog, "ex1-22_fold.c", MAXPROGLENGTH);

    remove_comments(prog, MAXPROGLENGTH);
    printf("%s", prog);

    return 0;
}

void remove_comments(char s[], int max_prog_length)
{
    int i;
    int j = 0;
    int in_string = 0;
    int in_sl_comment = 0; // single line comment
    int in_ml_comment = 0; /* (potentially) multiline comment */

    for (i = 0; i < max_prog_length - 1 && s[i] != EOF; ++i) {
        if (s[i] == '"') {
            in_string = 1 - in_string; // toggles it from 0 to 1 or vice versa
        } else if (s[i] == '/' && s[i + 1] == '/' && !in_string) {
            i++;
            in_sl_comment = 1;
        } else if (s[i] == '/' && s[i + 1] == '*' && !in_string) {
            i++;
            in_ml_comment = 1;
        } else if (s[i] == '*' && s[i + 1] == '/' && !in_string) {
            i++;
            in_ml_comment = 0;
            continue; // don't want to go below and add in the '/' to the resultant string
        } else if (s[i] == '\n') {
            in_sl_comment = 0;
        }

        if (!in_ml_comment & !in_sl_comment) {
            s[j] = s[i];
            j++;
        }
    }

    s[j] = '\0';

    return;
}