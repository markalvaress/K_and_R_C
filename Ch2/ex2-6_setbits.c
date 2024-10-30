#include <stdio.h>
#include <stdlib.h>
unsigned setbits(unsigned x, int p, int n, unsigned y);

int main(int argc, char **argv)
{
    unsigned x, y, x_modif;
    int p, n;

    x = strtoul(argv[1], NULL, 10);
    p = strtol(argv[2], NULL, 10);
    n = strtol(argv[3], NULL, 10);
    y = strtoul(argv[4], NULL, 10);

    x_modif = setbits(x, p, n, y);
    printf("%u", x_modif);
    
    return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    // I want to switch off bits between positions p & p+1-n
    x = x & (~0 << (p+1) | ~(~0 << (p-n))); // the RHS looks like 110000 | 000011 = 110011

    // now turn off all bits before n and then shift all bits in y left by (p+1-n)
    y = (y & ~(~0 << n)) << (p+1-n);

    // grand finale: x or y
    x = x | y;

    return x;
}