/* ============================================================================
 * Q26 : Print FIBONACCI numbers using RECURSION
 * Companies : TCS, Infosys, Wipro
 * ============================================================================
 *
 * WHAT IS FIBONACCI?
 *   A famous number pattern. You start with 0 and 1, then every next number is
 *   the SUM of the two before it.
 *
 *     0, 1, 1, 2, 3, 5, 8, 13, 21, ...
 *           ^  ^  ^
 *           0+1 1+1 1+2 ...
 *
 *   So the rule is:  fib(n) = fib(n-1) + fib(n-2)
 *
 * RECURSION REMINDER:
 *   BASE CASES: fib(0) = 0  and  fib(1) = 1  (we just know these, so we STOP).
 *   RECURSIVE CASE: fib(n) = fib(n-1) + fib(n-2)  (function calls itself twice).
 * ============================================================================
 */

#include <stdio.h>

/* Recursive function: returns the n-th Fibonacci number (counting from 0). */
int fib(int n)
{
    /* BASE CASES - the two starting numbers we already know. */
    if (n == 0) return 0;
    if (n == 1) return 1;

    /* RECURSIVE CASE - add the two previous Fibonacci numbers. */
    return fib(n - 1) + fib(n - 2);
}

int main(void)
{
    int count;

    printf("How many Fibonacci numbers do you want? ");
    scanf("%d", &count);

    if (count <= 0) {
        printf("Please enter a number bigger than 0.\n");
        return 0;
    }

    printf("Fibonacci series: ");
    /* Print fib(0), fib(1), fib(2), ... up to the count the user asked for. */
    for (int i = 0; i < count; i++) {
        printf("%d ", fib(i));
    }
    printf("\n");

    return 0;
}

/* ----------------------------------------------------------------------------
 * STEP-BY-STEP for fib(4):
 *   fib(4) = fib(3) + fib(2)
 *   fib(3) = fib(2) + fib(1)
 *   fib(2) = fib(1) + fib(0) = 1 + 0 = 1
 *   fib(1) = 1   (base case)
 *   fib(0) = 0   (base case)
 *   So fib(3) = 1 + 1 = 2, and fib(4) = 2 + 1 = 3.
 *
 * NOTE: this recursive version is simple to understand but slow for big n,
 * because it recomputes the same values many times. That is fine for learning.
 *
 * Compile & run:
 *   gcc q26_recursive_fibonacci.c -o q26
 *   ./q26     (Windows:  q26.exe)
 * --------------------------------------------------------------------------*/
