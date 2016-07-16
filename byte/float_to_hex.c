#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3) {
        printf("Usage: %s <hex value>\n", argv[0]);
        return 1;
    }

    float as_float = strtof(argv[1], NULL);
    double as_double = strtod(argv[1], NULL);

    unsigned char *as_bytes = (unsigned char *)&as_float;
    unsigned char *as_dbytes = (unsigned char *)&as_double;

    printf("Float max       : %f\n", DBL_MAX);
    printf("Float value     : %f\n", as_float);
    printf("Hex float value : 0x%X\n", as_float);
    printf("Double value    : %f\n", as_double);
    printf("Hex double value: 0x%lX\n", *(unsigned long*) &as_double);

    printf("Hex bytes       : 0x");
    int i;
    for (i=0; i<sizeof(float); i++) {
        printf("%2.2X", *(as_bytes++));
    }
    printf("\n");

    printf("Hex double bytes: ");
    for (i=0; i<sizeof(double); i++) {
        printf("0x%2.2X ", *(as_dbytes++));
    }
    printf("\n");
    return 0;
}
