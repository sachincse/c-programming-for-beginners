/* ============================================================================
 * Q23 : Count the SET BITS in a number
 * Companies : TCS, Infosys, Wipro
 * ============================================================================
 *
 * ELI5:
 * -----
 * Remember every number is really a row of 0s and 1s (binary).
 * A "set bit" just means a digit that is 1 (it is switched ON).
 * "Count set bits" = count how many 1s are in the binary form.
 *
 * Example: 13 in binary is 1101
 *          The 1s are:      1 1 . 1   -> there are THREE 1s.
 *          So 13 has 3 set bits.
 *
 * THE TRICK:
 *   Same idea as decimal->binary: divide by 2 and look at the leftover.
 *   Every time the leftover is 1, we found a set bit, so add 1 to our count.
 *
 * (There is also a famous faster trick called "Brian Kernighan's algorithm" -
 *  it is shown at the bottom as a bonus.)
 * ============================================================================
 */

#include <stdio.h>

int main(void)
{
    int number;

    printf("Enter a number (0 or bigger): ");
    scanf("%d", &number);

    if (number < 0) {
        printf("Please enter 0 or a positive number for this beginner version.\n");
        return 0;
    }

    int count = 0;   /* how many 1s we have found */

    /* Look at each binary digit by repeatedly dividing by 2. */
    while (number > 0) {
        if (number % 2 == 1) {   /* leftover 1 means this bit is ON */
            count = count + 1;
        }
        number = number / 2;
    }

    printf("Number of set bits (1s) = %d\n", count);
    return 0;
}

/* ----------------------------------------------------------------------------
 * BONUS - the clever fast version (Brian Kernighan's trick):
 *
 *   int count = 0;
 *   while (number > 0) {
 *       number = number & (number - 1);  // this erases the lowest 1 each time
 *       count++;
 *   }
 *
 * It loops only as many times as there are 1s, so it is faster for big numbers.
 *
 * Compile & run:
 *   gcc q23_count_set_bits.c -o q23
 *   ./q23     (Windows:  q23.exe)
 * Try 13  ->  answer is 3
 * --------------------------------------------------------------------------*/
