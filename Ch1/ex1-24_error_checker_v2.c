// NB: throughout we will often use "bracket" as an umbrella to refer to bracket, brace, and parenth.

#include <stdio.h>
#include "../useful_fns.h"

#define MAXPROGLENGTH 10000
#define BSLIMIT 50

void reportErrors(char fileContents[], int verbose);
char brackInverse(char brack);
int getUnmatchedPos(char brack);

// Maybe add a verbose option that can toggle whether or not to print out the logs of where brackets are found/matched?
int main(int argc, char **argv)
{
    int verbose = 0;

    if (argc != 3) {
        printf("Error: You should have two arguments - the first is the file name of the program to check, and the second is either 'v' for verbose for 'r' for regular");
        return -1;
    }
    if (argv[2][0] == 'v')
        verbose = 1;
    
    char fileContents[MAXPROGLENGTH];
    readFile(fileContents, argv[1], MAXPROGLENGTH);
    if (verbose) printf("Program: \n%s\n ***END OF PROGRAM***\n\n", fileContents);
    reportErrors(fileContents, verbose);
    
    return 0;
}

void reportErrors(char s[], int verbose)
{
    int i;
    int unmatched[6] = {0,0,0,0,0,0}; // ['{', '}', '(', ')', '[, ']']
    char brack_stack[BSLIMIT]; // We allow up to BSLIMIT nested brackets/braces/parenth.
    int stack_pos = 0; // should always point to the current bracket we are inside
    int in_sing_string = 0; // 'single quote' string vs "double quote" string
    int in_dbl_string = 0;
    int in_sl_comment = 0; // single line comment
    int in_ml_comment = 0; /* (potentially) multiline comment */
    int ignore = 0; // each iteration we ignore the character if it is in a string or a comment
    int all_matched;
    int line_number = 1;

    brack_stack[0] = '\0'; // to start off with, we are not in any bracket

    // count up all unmatched brackets etc
    for (i = 0; s[i] != EOF && s[i] != '\0'; ++i) {
        ignore = in_sing_string || in_dbl_string || in_sl_comment || in_ml_comment;

        switch (s[i]) {
            case '{':
            case '(':
            case '[':
                if (!ignore) {
                    stack_pos += 1;
                    brack_stack[stack_pos] = s[i];
                    if (verbose) printf("Open %c on line %d \n", s[i], line_number);
                }                
                break;

            // If we've closed the bracket we're currently in, great! If not, not great...
            case '}':
            case ')':
            case ']':
                if (!ignore) {
                    if (brack_stack[stack_pos] == brackInverse(s[i])) {
                        if (verbose) printf("The previous %c has been matched up on line %d\n", brack_stack[stack_pos], line_number);
                        stack_pos -= 1;
                    } else {
                        unmatched[getUnmatchedPos(s[i])] += 1;
                        if (verbose) printf("The %c on line %d is unmatched\n", s[i], line_number);
                    }
                }
                break;

            case '"':
                if (s[i - 1] != '\\' && !in_sl_comment && !in_ml_comment && !in_sing_string)
                    in_dbl_string = !in_dbl_string;
                break;
            
            case '\'':
                if (s[i - 1] != '\\' && !in_sl_comment && !in_ml_comment && !in_dbl_string)
                    in_sing_string = !in_sing_string;
                break;


            // doesn't deal well with weird cases like someone trying to put a multiline comment within a single line comment, but o well
            case '/':
                if (s[i+1] == '*') {
                    in_ml_comment = 1;
                } else if (s[i-1] == '*') {
                    in_ml_comment = 0;
                } else if (s[i+1] == '/') {
                    in_sl_comment = 1;
                }
                break;               

            case '\n':
                //in_string = 0; I don't think this is true - I can have multiline strings?
                in_sl_comment = 0;
                line_number += 1;
                break;
            
            default:
                break;
        }
    }

    // Everything left in the brack stack at the end is unmatched
    for (i = 1; i <= stack_pos; ++i) {
        unmatched[getUnmatchedPos(brack_stack[i])] += 1;
        if (verbose) printf("Brack stack %d: %c\n", i, brack_stack[i]);
    }

    all_matched = 1;
    for (i = 0; i <= 5; ++i) {
        if (unmatched[i] > 0) {
            all_matched = 0;
            break;
        }
    }

    if (all_matched) {
        printf("All parentheses etc matched up. Good job!");
    } else {
        // I could do this with a loop and some function that knows that unmatched[0] is '{', etc, but cba making it just for this one use
        printf("There are %d unmatched open curly braces \n", unmatched[0]);
        printf("There are %d unmatched closed curly braces \n", unmatched[1]);
        printf("There are %d unmatched open parentheses \n", unmatched[2]);
        printf("There are %d unmatched closed parentheses \n", unmatched[3]);
        printf("There are %d unmatched open square brackets \n", unmatched[4]);
        printf("There are %d unmatched closed square brackets \n", unmatched[5]);
    }

    return;
}

char brackInverse(char brack)
{
    // I'm only gonna use this to find the open brack from the close brack
    if (brack == '}') {
        return '{';
    } else if (brack == ')') {
        return '(';
    } else if (brack == ']') {
        return '[';
    } else {
        printf("Error: input was not a correct bracket");
        return ' ';
    }    
}

int getUnmatchedPos(char brack)
{
    // Gives the position in 'unmatched' for a given bracket
    int pos;

    switch (brack) {
        case '{':
            pos = 0;
            break;
        case '}':
            pos = 1;
            break;
        case '(':
            pos = 2;
            break;
        case ')':
            pos = 3;
            break;
        case '[':
            pos = 4;
            break;
        case ']':
            pos = 5;
            break;
        
        default:
            break;
    }

    return pos;
}