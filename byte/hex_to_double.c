#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3) {
        printf("Usage: %s <hex value>\n", argv[0]);
        return 1;
    }

    union {
        long int i;
        double d;
    } ud;

    ud.i = strtol(argv[1], NULL, 16); /* read in hex */
    printf("Int value       : %ld\n", ud.i);
    printf("Float value     : %f\n", ud.d);
    printf("Hex float value : 0x%A\n", ud.d);
    printf("Hex bytes       : 0x%lX\n", ud.i);
    return 0;
}
