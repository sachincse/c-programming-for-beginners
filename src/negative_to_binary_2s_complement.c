/* ============================================================================
 * BONUS : Convert a NEGATIVE number to BINARY using TWO'S COMPLEMENT
 * (This is the "complement" method asked for in the question.)
 * ============================================================================
 *
 * THE PROBLEM:
 *   Binary is just 0s and 1s. There is no place to write a "minus" sign!
 *   So how does a computer remember that a number is NEGATIVE?
 *   Answer: a clever trick called TWO'S COMPLEMENT.
 *
 * THE IDEA (ELI5):
 *   We first decide how many boxes (bits) we have. Here we use 8 boxes (8 bits),
 *   which can hold numbers from -128 to +127.
 *
 *   To write a NEGATIVE number like -5 in two's complement, do 3 steps:
 *     STEP 1: Write +5 in normal 8-bit binary  ->  0000 0101
 *     STEP 2: FLIP every bit (0 becomes 1, 1 becomes 0). This is called the
 *             "one's complement"                ->  1111 1010
 *     STEP 3: ADD 1 to that result             ->  1111 1011
 *     Done!  -5 in 8-bit two's complement is 1111 1011.
 *
 *   Notice the leftmost bit: for negative numbers it is always 1. That bit is
 *   nicknamed the "sign bit" - 0 means positive, 1 means negative.
 *
 *   Positive numbers and 0 are just written normally:
 *     +5  ->  0000 0101
 *      0  ->  0000 0000
 * ============================================================================
 */

#include <stdio.h>

#define BITS 8   /* we work with 8 boxes (8 bits) to keep it easy to read */

/* Helper: print an array of bits with a space in the middle (1111 1011). */
void printBits(int bits[])
{
    for (int i = 0; i < BITS; i++) {
        if (i == 4) printf(" ");   /* a gap after 4 bits, just for the eyes */
        printf("%d", bits[i]);
    }
    printf("\n");
}

int main(void)
{
    int number;

    printf("Enter a number between -128 and 127: ");
    scanf("%d", &number);

    if (number < -128 || number > 127) {
        printf("Out of range for 8 bits. Please use -128 to 127.\n");
        return 0;
    }

    int bits[BITS];   /* bits[0] is the LEFTMOST bit, bits[7] is the rightmost */

    /* ---- CASE 1: zero or positive -> just write the normal binary ---- */
    if (number >= 0) {
        int n = number;
        for (int i = BITS - 1; i >= 0; i--) {  /* fill from the right */
            bits[i] = n % 2;
            n = n / 2;
        }
        printf("\n%d is positive, so binary is just the normal value:\n", number);
        printf("Binary (8-bit) = ");
        printBits(bits);
        return 0;
    }

    /* ---- CASE 2: negative -> use the three two's-complement steps ---- */
    int magnitude = -number;   /* the positive twin, e.g. -5 -> 5 */

    /* STEP 1: write the positive twin in 8-bit binary. */
    int n = magnitude;
    for (int i = BITS - 1; i >= 0; i--) {
        bits[i] = n % 2;
        n = n / 2;
    }
    printf("\nSTEP 1 - write +%d in 8-bit binary:\n   ", magnitude);
    printBits(bits);

    /* STEP 2: flip every bit (one's complement). */
    for (int i = 0; i < BITS; i++) {
        bits[i] = 1 - bits[i];   /* 0 becomes 1, 1 becomes 0 */
    }
    printf("STEP 2 - flip all the bits (one's complement):\n   ");
    printBits(bits);

    /* STEP 3: add 1, starting from the rightmost bit, carrying as needed. */
    int carry = 1;   /* the "1" we want to add */
    for (int i = BITS - 1; i >= 0 && carry == 1; i--) {
        int sum = bits[i] + carry;
        bits[i] = sum % 2;   /* the digit that stays in this box */
        carry   = sum / 2;   /* 1 if it overflowed and carries left, else 0 */
    }
    printf("STEP 3 - add 1 (this gives two's complement):\n   ");
    printBits(bits);

    printf("\nSo %d in 8-bit two's complement binary is: ", number);
    printBits(bits);

    return 0;
}

/* ----------------------------------------------------------------------------
 * QUICK CHECK you can do by hand:
 *   -1  -> 1111 1111   (all ones)
 *   -2  -> 1111 1110
 *   -5  -> 1111 1011
 *  -128 -> 1000 0000   (the most negative 8-bit number)
 *
 * Compile & run:
 *   gcc negative_to_binary_2s_complement.c -o neg
 *   ./neg     (Windows:  neg.exe)
 * Try -5  ->  1111 1011
 * --------------------------------------------------------------------------*/
