/* ============================================================================
 * Q27 : SUM OF DIGITS of a number using RECURSION
 * Companies : TCS, Infosys, Wipro
 * ============================================================================
 *
 * WHAT DOES "SUM OF DIGITS" MEAN?
 *   Just add up every digit in the number.
 *     1234  ->  1 + 2 + 3 + 4  =  10
 *     505   ->  5 + 0 + 5      =  10
 *
 * HOW DO WE GRAB ONE DIGIT AT A TIME?
 *   number % 10   gives the LAST digit.        1234 % 10 = 4
 *   number / 10   removes the last digit.      1234 / 10 = 123
 *   Repeat, and you peel digits off from the right.
 *
 * RECURSION IDEA:
 *   sum(1234) = 4 + sum(123)
 *   sum(123)  = 3 + sum(12)
 *   sum(12)   = 2 + sum(1)
 *   sum(1)    = 1 + sum(0)
 *   sum(0)    = 0           <- BASE CASE, we stop here
 *
 *   In words: (last digit) + (sum of the digits that remain).
 * ============================================================================
 */

#include <stdio.h>

int sumOfDigits(int number)
{
    /* BASE CASE: when nothing is left, the sum is 0. */
    if (number == 0) {
        return 0;
    }

    /* RECURSIVE CASE: last digit + sum of the rest. */
    return (number % 10) + sumOfDigits(number / 10);
}

int main(void)
{
    int number;

    printf("Enter a number: ");
    scanf("%d", &number);

    /* If the number is negative, work with its positive twin so digits add up
     * normally (e.g. -123 -> add digits of 123). */
    if (number < 0) {
        number = -number;
    }

    printf("Sum of digits = %d\n", sumOfDigits(number));
    return 0;
}

/* ----------------------------------------------------------------------------
 * Compile & run:
 *   gcc q27_recursive_sum_of_digits.c -o q27
 *   ./q27     (Windows:  q27.exe)
 * Try 1234  ->  10
 * --------------------------------------------------------------------------*/
