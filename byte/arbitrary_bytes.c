/* Notes on reading octets from machines with arbitrary bit-length bytes
 *
 * C standard only requires that a char is >= 8 bits, so CHAR_BIT (in
 * `limits.h`) may be larger than 8 bits. Apparently, it is rare for
 * CHAR_BIT != 8. But to write maximally portable C, we can't assume
 * that CHAR_BIT == 8. For "fun", these are some notes for figuring
 * out how to read out octets when CHAR_BIT > 8.
 *
 * byte
 *   native byte on the host machine. bit length is specified by
 *   CHAR_BIT. in Standard C, CHAR_BIT >= 8.
 *
 * octet
 *   unit ("byte") of input data. will usually be 8-bits, thus the
 *   name. bit length is specified by OCTET_BIT. but, generally,
 *   OCTET_BIT == <CHAR_BIT of machine that wrote the data>.
 *
 * The normal case will be CHAR_BIT >= OCTET_BIT. This code also
 * handles OCTET_BIT > CHAR_BIT (a machine with bytes that are smaller
 * than the input bytes) under the condition: CHAR_BIT >= 2*OCTET_BIT.
 *
 * To be perfectly portable, code can't make any assumptions about the
 * underlying data representation.
 *
 * For signed integers, standard C allows (see section 6.2.6.2.2):
 *
 *  - Two's complement (~x + 1)
 *  - Ones' complement (~x)
 *  - sign-and-magnitude (high order bit is sign (1 is negative))
 *
 * - floating-point format is implementation-defined
 *
 * - conversion to signed integers, if the original value can't be
 * represented, is implementation-defined (6.3.1.3.3)
 *
 */

#include <stdio.h>

#define CHAR_BIT 11 /* for an easy example. pretend the machine has 11-bit bytes */
#define OCTET_BIT 8 /* the length of the read bytes (an octet, usually) */

/* bytes needed to store x bits */
#define BYTES_NEEDED(x)                         \
    ((x + CHAR_BIT - 1) / CHAR_BIT)

/* bytes needed for storing n octets */
#define BYTES_OCTET_NEEDED(n)                   \
    (BYTES_NEEDED(n * OCTET_BIT))

/* get offset from 0 of octet n*/
#define OCTET_OFFSET(n)                         \
    (OCTET_BIT * n)

/* get the byte index of octet n */
#define BYTE_INDEX(n)                           \
    (OCTET_OFFSET(n) / CHAR_BIT)

/* get the byte offset of octet n in byte */
#define BYTE_OFFSET(n)                          \
    (OCTET_OFFSET(n) % CHAR_BIT)

/* number of bits of octet n stored in byte at BYTE_INDEX(n) */
#define BYTE_BITS(n)                            \
    ((CHAR_BIT - BYTE_OFFSET(n)) >= OCTET_BIT   \
     ? OCTET_BIT : (CHAR_BIT - BYTE_OFFSET(n)))

/* number of bits of octet n stored after BYTE_INDEX(n) */
#define FOLLOW_BITS(n)                          \
    (OCTET_BIT - BYTE_BITS(i))

/* number of extra bytes needed to read octet n */
#define FOLLOW_BYTES_NEEDED(n)                  \
    (BYTES_NEEDED(FOLLOW_BITS(n)))


int main(int argc, char *argv[])
{
    int i;
    printf("\n%d-bit input bytes\n%d-bit byte machine\n", OCTET_BIT, CHAR_BIT);
    printf("==========================\n");
    printf("%3s: %4s %4s %4s %4s\n", "n", "byte", "off", "this", "next");
    for (i=0; i<12; i++) {
        printf("%3d: %4d %4d %4d %4d %4d\n", i, BYTE_INDEX(i), BYTE_OFFSET(i),
               BYTE_BITS(i), FOLLOW_BITS(i), FOLLOW_BYTES_NEEDED(i));
    }
    return 0;
}
