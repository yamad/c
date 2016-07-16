#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *f;

    if (argc < 3) {
        printf("Usage: %s <file path> <byte count> [<offset>]\n", argv[0]);
        exit(1);
    }

    char *fname = argv[1];
    if (fname == NULL) fname = "";

    size_t nbytes = (size_t) strtol(argv[2], NULL, 0);
    size_t offset = 0;
    if (argc > 3) {
        offset = (size_t) strtol(argv[3], NULL, 0);
    }

    f = fopen(fname, "r");
    if (f == NULL) {
        fprintf(stderr, "Can't open file\n");
        exit(1);
    }

    unsigned char *buf = malloc(nbytes);
    if (buf == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    fseek(f, offset, SEEK_SET);
    if (0 == fread(buf, nbytes, 1, f)) {
        printf("Read error\n");
        exit(1);
    }

    int i;
    for (i=0; i<nbytes; i++) {
        if (i != 0 && i % 8 == 0)
            printf("\n");
        printf("0x%.2hX,", *buf++);
    }
    printf("\n");
    return 0;
}
