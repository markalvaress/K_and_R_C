/* an easy way to show that this program is slightly ridiculous is that:
int main)(
}
    return 0;
{    
would be no errors.*/

#include <stdio.h>
#include "../useful_fns.h"

#define MAXPROGLENGTH 10000

void reportErrors(char fileContents[]);

int main()
{
    char fileContents[MAXPROGLENGTH];
    readFile(fileContents, "../../misc/rubbish_program.c", MAXPROGLENGTH);
    printf("Program: \n%s\n\n", fileContents);
    reportErrors(fileContents);
    
    return 0;
}

void reportErrors(char s[])
{
    int i;
    int curly_diff = 0, parenth_diff = 0, brackets_diff = 0; // each of these will be the number of open brackets less the number of close brackets - we want this to be 0
    int in_string = 0;
    int in_sl_comment = 0; // single line comment
    int in_ml_comment = 0; /* (potentially) multiline comment */
    int ignore = 0; // each iteration we ignore the character if it is in a string or a comment

    for (i = 0; s[i] != EOF && s[i] != '\0'; ++i) {
        ignore = in_string || in_sl_comment || in_ml_comment;

        switch (s[i]) {
            case '{':
                curly_diff += !ignore * 1; // since ignore is 1 if True then we multiply by !ignore = 0 to not do anything to curly_diff. This was just so I could write concisely, idk if this is good practice.
                break;
            case '}':
                curly_diff -= !ignore * 1;
                break;
            case '(':
                parenth_diff += !ignore * 1;
                break;
            case ')':
                parenth_diff -= !ignore * 1;
                break;
            case '[':
                brackets_diff += !ignore * 1;
                break;
            case ']':
                brackets_diff -= !ignore * 1;
                break;
            case '"':
                if (s[i - 1] != '\\' && !in_sl_comment && !in_ml_comment)
                    in_string = !in_string;
                break;
            case '\n':
                in_string = 0;
                break;
            
            default:
                break;
        }

    }

    if (curly_diff == 0 && parenth_diff == 0 && brackets_diff == 0) {
        printf("All brackets matched up");
    } else {
        // maybe a nicer way to combine ?
        if (curly_diff > 0) {
            printf("Error: You have %d unmatched open curly braces\n", curly_diff);
        } else if (curly_diff < 0) {
            printf("Error: You have %d unmatched close curly braces\n", -curly_diff);
        }

        if (parenth_diff > 0) {
            printf("Error: You have %d unmatched open parentheses\n", parenth_diff);
        } else if (parenth_diff < 0) {
            printf("Error: You have %d unmatched close parentheses\n", -parenth_diff);
        }
        
        if (brackets_diff > 0) {
            printf("Error: You have %d unmatched open square brackets\n", brackets_diff);
        } else if (brackets_diff < 0) {
            printf("Error: You have %d unmatched close square brackets\n", -brackets_diff);
        }
    }

    return;
}