#include <stdio.h>

int any(char s1[], char s2[]);

int main(int argc, char **argv)
{
    int i;
    
    i = any(argv[1], argv[2]);
    if (i == -1)
        printf("No matching chars.\n");
    else
        printf("The first string has a matching character with the second string at location %d\n", i);

    return 0;
}

int any(char s1[], char s2[])
{
    // Returns the first location in a string s1 
    // where any character from the string s2 occurs, or -1 for fail
    int first_loc = 10000; // random large number - probably not good to hard code this
    int any_found = 0;
    int i,j;

    for (j = 0; s2[j] != '\0'; j++) {
        for (i = 0; s1[i] != '\0'; i++) {
            if (s1[i] == s2[j] && (!any_found || i <= first_loc)) { // maybe I could do some funky s1[i++] = s2[j] but idk
                first_loc = i;
                any_found = 1;
            }
        }
    }

    if (!any_found) {
        return -1;
    } else {
        return first_loc;
    }
}