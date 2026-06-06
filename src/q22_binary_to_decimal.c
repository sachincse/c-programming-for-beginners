/* ============================================================================
 * Q22 : Convert a BINARY number into DECIMAL
 * Companies : TCS, Infosys, Wipro
 * ============================================================================
 *
 * ELI5:
 * -----
 * Binary uses only 0 and 1. Each "1" stands for a value, and the value
 * DOUBLES every time you move one step to the LEFT.
 *
 * Place values (from the right):  ... 16  8  4  2  1
 *                                       ^   ^  ^  ^  ^
 * Example: binary 1101
 *     1   1   0   1
 *     8   4   0   1   <- multiply each digit by its place value
 *   Add them up: 8 + 4 + 0 + 1 = 13
 *   So binary 1101 = decimal 13.
 *
 * THE TRICK in code:
 *   Start with answer = 0.
 *   Look at the binary digits from RIGHT to LEFT.
 *   For each digit, add (digit * placevalue), then double the placevalue.
 * ============================================================================
 */

#include <stdio.h>

int main(void)
{
    /* We read the binary number as a LONG whole number, e.g. 1101.
     * (long can hold more digits than a normal int.) */
    long binary;

    printf("Enter a binary number (only 0s and 1s): ");
    scanf("%ld", &binary);

    int decimal = 0;     /* the answer starts at 0 */
    int placeValue = 1;  /* the rightmost place is worth 1, then 2, 4, 8 ... */

    /* Peel off digits from the RIGHT side, one at a time. */
    while (binary > 0) {
        int digit = binary % 10;   /* last digit: 0 or 1 (for valid binary) */

        /* Safety check: real binary has only 0 and 1. */
        if (digit != 0 && digit != 1) {
            printf("That is not a valid binary number (use only 0 and 1).\n");
            return 1;   /* return non-zero means "something went wrong" */
        }

        decimal = decimal + digit * placeValue; /* add this digit's value */
        placeValue = placeValue * 2;            /* next place is worth double */
        binary = binary / 10;                   /* drop the digit we just used */
    }

    printf("Decimal = %d\n", decimal);
    return 0;
}

/* ----------------------------------------------------------------------------
 * Compile & run:
 *   gcc q22_binary_to_decimal.c -o q22
 *   ./q22        (Windows:  q22.exe)
 * Try typing: 1101   ->  you should get 13
 * --------------------------------------------------------------------------*/
