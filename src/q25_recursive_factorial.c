/* ============================================================================
 * Q25 : Find FACTORIAL using RECURSION
 * Companies : TCS, Infosys, Wipro
 * ============================================================================
 *
 * WHAT IS A FACTORIAL?
 *   Written with a "!" sign. It means multiply all whole numbers from 1 up to n.
 *     5! = 5 * 4 * 3 * 2 * 1 = 120
 *     3! = 3 * 2 * 1 = 6
 *     0! = 1   (a special math rule)
 *
 * WHAT IS RECURSION? (ELI5)
 *   Recursion is when a function CALLS ITSELF to solve a smaller piece of the
 *   same problem. Imagine standing between two mirrors - you see a smaller you,
 *   inside an even smaller you, again and again.
 *
 *   Every recursion needs TWO things or it never stops:
 *     1) BASE CASE  - the simplest version where we already know the answer
 *                     and we STOP. (here: 0! = 1 and 1! = 1)
 *     2) RECURSIVE CASE - the function calls itself with a SMALLER number,
 *                     getting closer to the base case each time.
 *
 *   The big idea: n! = n * (n-1)!
 *     5! = 5 * 4!
 *     4! = 4 * 3!  ... and so on, until 1! which we just know is 1.
 * ============================================================================
 */

#include <stdio.h>

/* This function calls ITSELF - that is what makes it recursive. */
long long factorial(int n)
{
    /* BASE CASE: when we reach 0 or 1, stop and return 1. */
    if (n == 0 || n == 1) {
        return 1;
    }

    /* RECURSIVE CASE: n! = n * (n-1)!  -> ask the function for (n-1)! */
    return n * factorial(n - 1);
}

int main(void)
{
    int n;

    printf("Enter a number (0 or bigger): ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Factorial is only defined for 0 and positive numbers.\n");
        return 0;
    }

    printf("%d! = %lld\n", n, factorial(n));
    return 0;
}

/* ----------------------------------------------------------------------------
 * STEP-BY-STEP for factorial(4):
 *   factorial(4) = 4 * factorial(3)
 *   factorial(3) = 3 * factorial(2)
 *   factorial(2) = 2 * factorial(1)
 *   factorial(1) = 1            <- BASE CASE, recursion stops here
 *   Now the answers travel back up:
 *   factorial(2) = 2 * 1 = 2
 *   factorial(3) = 3 * 2 = 6
 *   factorial(4) = 4 * 6 = 24
 *
 * Compile & run:
 *   gcc q25_recursive_factorial.c -o q25
 *   ./q25     (Windows:  q25.exe)
 * --------------------------------------------------------------------------*/
