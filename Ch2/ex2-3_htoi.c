#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int htoi(char s[]);
void strip_0x(char s[]);

int main(int argc, char **argv) // is there a limit to how big argv is??
{
    // Takes one argument: the hex number to be converted
    int hex_converted;

    hex_converted = htoi(argv[1]);
    if (hex_converted != -1)
        printf("The hex number %s is %d in base 10.\n", argv[1], hex_converted);
    return 0;
}

int htoi(char s[]) {
    int i;
    int converted = 0;
    int len;

    strip_0x(s);
    len = strlen(s);

    for (i = 0; i < len; i++) {
        if (isdigit(s[i])) {
            // using (len-1) - i bc 0th element should get multip by 16 ** (len-1), etc.
            converted += pow(16, (len-1) - i) * (s[i] - '0');
        } else {
            s[i] = toupper(s[i]); // so that I don't have to deal with lower and upper separately
            if ('A' <= s[i] && s[i] <= 'F') {
                converted += pow(16, (len-1) - i) * ((s[i] - 'A') + 10);
            } else {
                printf("Error: %c is not a valid hexadecimal digit.\n", s[i]);
                return -1;
            }
        }
    }

    return converted;
}

// maybe this isn't a super efficient way to go about things, but makes code easier to read than 
// trying to build in conditional ignoring of 0x above imo
void strip_0x(char s[]) {
    int i;

    // checks if the string starts with 0x or 0X, and if it does strips that from the string
    if (s[0] == '0' && toupper(s[1]) == 'X') {
        for (i = 2; s[i] != '\0'; i++) {
            s[i - 2] = s[i];
        }
        s[i - 2] = '\0';
        return;
    } else {
        return;
    }
}