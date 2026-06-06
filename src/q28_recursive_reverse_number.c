/* ============================================================================
 * Q28 : REVERSE A NUMBER using RECURSION
 * Companies : TCS, Infosys, Wipro
 * ============================================================================
 *
 * WHAT DOES "REVERSE A NUMBER" MEAN?
 *   Write the digits backwards.
 *     1234  ->  4321
 *     560   ->  65   (the leading 0 just disappears, like a normal number)
 *
 * SAME DIGIT TOOLS AS BEFORE:
 *   number % 10  -> last digit
 *   number / 10  -> drop the last digit
 *
 * THE IDEA (using a "carry along" helper):
 *   We carry a second box called "rev" that slowly builds the answer.
 *   Each step:
 *     - take the last digit of "number"
 *     - glue it onto the RIGHT side of "rev" by doing rev*10 + lastDigit
 *     - then shrink "number" by removing that digit
 *   When "number" becomes 0, "rev" holds the fully reversed number.
 *
 *   Walkthrough for 1234 (rev starts at 0):
 *     number=1234, rev=0    -> rev = 0*10 + 4   = 4
 *     number=123,  rev=4    -> rev = 4*10 + 3   = 43
 *     number=12,   rev=43   -> rev = 43*10 + 2  = 432
 *     number=1,    rev=432  -> rev = 432*10 + 1 = 4321
 *     number=0              -> STOP, answer = 4321
 * ============================================================================
 */

#include <stdio.h>

/* "rev" carries the answer-so-far. We start by calling reverseNumber(number, 0). */
int reverseNumber(int number, int rev)
{
    /* BASE CASE: nothing left to reverse, so the answer is whatever we built. */
    if (number == 0) {
        return rev;
    }

    /* RECURSIVE CASE: glue the last digit onto rev, then continue with the rest. */
    int lastDigit = number % 10;
    return reverseNumber(number / 10, rev * 10 + lastDigit);
}

int main(void)
{
    int number;

    printf("Enter a number: ");
    scanf("%d", &number);

    /* Remember if it was negative, then work with the positive twin. */
    int isNegative = 0;
    if (number < 0) {
        isNegative = 1;
        number = -number;
    }

    int result = reverseNumber(number, 0);

    if (isNegative) {
        result = -result;   /* put the minus sign back, e.g. -1234 -> -4321 */
    }

    printf("Reversed number = %d\n", result);
    return 0;
}

/* ----------------------------------------------------------------------------
 * Compile & run:
 *   gcc q28_recursive_reverse_number.c -o q28
 *   ./q28     (Windows:  q28.exe)
 * Try 1234  ->  4321
 * --------------------------------------------------------------------------*/
