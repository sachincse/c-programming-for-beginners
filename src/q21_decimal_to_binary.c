/* ============================================================================
 * Q21 : Convert a DECIMAL number into BINARY
 * Companies : TCS, Infosys, Wipro
 * ============================================================================
 *
 * ELI5 (Explain Like I'm 5):
 * --------------------------
 * You count using 10 fingers:  0 1 2 3 4 5 6 7 8 9  -> this is "decimal".
 * A computer has only 2 "fingers": OFF and ON, which we write as 0 and 1.
 * Counting with only 0 and 1 is called "binary".
 *
 * So the number 5 (decimal) is written as 101 in binary.
 *
 * THE TRICK (how to turn decimal into binary):
 *   Keep dividing the number by 2 and write down the LEFTOVER (remainder).
 *   The leftovers, read from BOTTOM to TOP, are the binary number.
 *
 *   Example: 13
 *     13 / 2 = 6  leftover 1   <- bottom
 *      6 / 2 = 3  leftover 0
 *      3 / 2 = 1  leftover 1
 *      1 / 2 = 0  leftover 1   <- top
 *   Read leftovers bottom->top : 1101
 *   So 13 in binary is 1101.
 *
 * NOTE about NEGATIVE numbers (like -5):
 *   Negative numbers use a special trick called "two's complement".
 *   That has its own file: negative_to_binary_2s_complement.c
 *   This file handles 0 and positive numbers (the normal Day-6 question).
 * ============================================================================
 */

#include <stdio.h>   /* gives us printf (print to screen) and scanf (read input) */

int main(void)       /* main() is where every C program starts running */
{
    int number;      /* a box named "number" that can hold a whole number */

    printf("Enter a decimal number (0 or bigger): ");
    scanf("%d", &number);   /* read what the user types into the box "number" */

    /* Special case: the number 0 is just "0" in binary. */
    if (number == 0) {
        printf("Binary = 0\n");
        return 0;    /* return 0 means "program finished happily" */
    }

    /* If the user typed a negative number, gently point them to the other file. */
    if (number < 0) {
        printf("This program is for 0 and positive numbers.\n");
        printf("For negative numbers, run negative_to_binary_2s_complement.c\n");
        return 0;
    }

    /* We will collect the leftovers (remainders) in an array (a row of boxes). */
    int bits[32];    /* an int is 32 bits, so 32 boxes is always enough */
    int count = 0;   /* how many leftovers we have collected so far */

    /* Keep dividing by 2 until the number becomes 0. */
    while (number > 0) {
        bits[count] = number % 2;  /* % means "remainder after dividing" (0 or 1) */
        number = number / 2;       /* shrink the number by dividing by 2 */
        count = count + 1;         /* we collected one more leftover */
    }

    /* The leftovers were collected bottom-first, so print them in REVERSE. */
    printf("Binary = ");
    for (int i = count - 1; i >= 0; i--) {
        printf("%d", bits[i]);
    }
    printf("\n");

    return 0;
}

/* ----------------------------------------------------------------------------
 * HOW TO RUN THIS PROGRAM:
 *   1) Open a terminal in this folder.
 *   2) Compile (turn human code into computer code):
 *        gcc q21_decimal_to_binary.c -o q21
 *   3) Run it:
 *        ./q21        (on Windows it may be:  q21.exe  or  .\q21.exe)
 *   4) Type a number like 13 and press Enter.
 * --------------------------------------------------------------------------*/
