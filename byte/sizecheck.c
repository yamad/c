#include <stdio.h>
#include <limits.h>

#define PRINT_SIZE(type)                            \
    printf("%-13s: %zu (%ld)\n", #type, sizeof(type), \
           (unsigned long)sizeof(type)*CHAR_BIT);

int main(int argc, char *argv[])
{
    printf("\nType Sizes\n");
    printf("===================\n");
    printf("%-13s: %d\n\n", "CHAR_BIT", CHAR_BIT);

    printf("%-13s: bytes (bits)\n", "type");
    printf("---------------------------\n");
    PRINT_SIZE(short);
    PRINT_SIZE(int);
    PRINT_SIZE(long);
    PRINT_SIZE(long long);
    printf("\n");
    PRINT_SIZE(float);
    PRINT_SIZE(double);
    printf("\n");
    PRINT_SIZE(void *);
    PRINT_SIZE(int *);
    PRINT_SIZE(char *);
    PRINT_SIZE(int (*)(int));
    return 0;
}


