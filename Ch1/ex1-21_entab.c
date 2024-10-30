/* Write a program entab that replaces strings of blanks by the minimum
number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab.*/

#include <stdio.h>
#include "../useful_fns.h" // gives us getline()
#define NCOLS 8 // there will be tabstops after this many columns
#define MAXLINE 1000

void entab(char s[]);
int insert_tabs_spaces(char s[], int j, int n_tabs, int n_spaces);

int main()
{
    char line[MAXLINE];
    int len;

    while ((len = getline(line, MAXLINE)) > 0) { 
        entab(line);
        printf("%s", line);
    }

    return 0;
}

void entab(char s[])
{
    int i, j, streak_len, to_next_tabstop;
    i = j = streak_len = 0;
    int in_streak = 0; // this is meant as a boolean
    int num_tabs, num_spaces;
    int last_tab_position = 0;
    
    for (i = 0; s[i] != EOF && s[i] != '\n'; ++i) {
        if (s[i] == ' ') {
            in_streak = 1;
            ++streak_len;
        } else {
            if (in_streak) {
                /* (j - last_tab_position) gives the current position in the entab'd string relative to the last tab that was placed there, 
                so that we can accurately judge how far it is to next tabstop (on the screen). */
                to_next_tabstop = NCOLS - ((j - last_tab_position)%NCOLS);
                if (streak_len < to_next_tabstop) {
                    num_tabs = 0;
                    num_spaces = streak_len;
                } else {
                    num_tabs = 1; // we need a tab to get to the next tab stop
                    streak_len -= to_next_tabstop; // remaining streak

                    num_tabs += streak_len / NCOLS;
                    num_spaces = streak_len % NCOLS;
                }                

                // j by default gets passed by val (I'd need pointers for by ref) so we explicitly return it.
                j = insert_tabs_spaces(s, j, num_tabs, num_spaces);
                if (num_tabs >= 1) {
                    last_tab_position = j - num_spaces;
                }
                in_streak = 0;
                streak_len = 0;
            }

            s[j] = s[i];
            ++j;
        }
    }

    s[j] = '\n';
    s[j+1] = '\0';

    return;
}

int insert_tabs_spaces(char s[], int j, int n_tabs, int n_spaces)
{
    int start = j;

    for (j = start; j < start + n_tabs; ++j) {
        s[j] = '\t';
    }

    start = j;
    for (j = start; j < start + n_spaces; ++j) {
        s[j] = ' ';
    }

    return j;
}

// int entab(char s[])
// {
//     int i, j, k, l, m, start_of_spaces, end_of_spaces; // this is getting ridiculous now
//     char t[MAXLINE];

//     i = 0; // position in s
//     j = 0; // position in t

//     // loop through all chars in s
//     while (s[i] != EOF && s[i] != '\n') {
//         if (s[i] == ' ') {
//             // we'll move i up as we pass through s, so we anchor this at the position where the spaces start
//             start_of_spaces = i;

//             // count number of consecutive blanks
//             for (k = 0; s[i + k] == ' '; ++k)
//                 ;

//             end_of_spaces = start_of_spaces + k;

//             // basically looping over each NCOLS sized chunk of the string
//             while (i < end_of_spaces) {
//                 // find the next tab stop position in s. This works because i/NCOLS is integer (floor) division
//                 l = NCOLS*(i/NCOLS + 1);
//                 printf("Next tabstop position: %d\n", l);

//                 // check if we need a tab or not
//                 if (l <= end_of_spaces) {
//                     t[j] = '\t';
//                     ++j;
//                     i = l;
//                 } else {
//                     // just fill up with spaces because we haven't reached the next tab stop
//                     for (m = j; m < (end_of_spaces - l) + j; ++m) {
//                         t[m] = ' ';
//                     }

//                     j += end_of_spaces - i;
//                     i = end_of_spaces;
//                 }
//             }             
//         } else {
//             t[j] = s[i];
//             ++j;
//         }
//     }

//     // now overwrite s with t
//     for (k = 0; k < j; ++k) { // j accurately counts the length of t, so t goes t[0] to t[j-1]
//         s[k] = t[k];
//     }

//     s[j] = '\0';

//     return(0);
// }