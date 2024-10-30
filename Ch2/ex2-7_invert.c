#include <stdio.h>
#include <stdlib.h>
unsigned invert(unsigned x, int p, int n);

int main(int argc, char **argv)
{
    unsigned x, x_modif;
    int p, n;

    x = strtoul(argv[1], NULL, 10);
    p = strtol(argv[2], NULL, 10);
    n = strtol(argv[3], NULL, 10);

    x_modif = invert(x, p, n);
    printf("%u", x_modif);
    
    return 0;
}

unsigned invert(unsigned x, int p, int n) {
    // surely once I've got the inversion I can just use setbits ...
    return 0;
}