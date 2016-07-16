#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3) {
        printf("Usage: %s <hex value>\n", argv[0]);
        return 1;
    }

    union {
        int i;
        float f;
    } uf;

    uf.i = (int) strtol(argv[1], NULL, 16); /* read in hex */
    printf("Int value       : %d\n", uf.i);
    printf("Float value     : %f\n", uf.f);
    printf("Hex float value : 0x%X\n", uf.i);
    return 0;
}
