/* ============================================================================
 * Q24 : Find x^n (x raised to the power n) WITHOUT using pow()
 * Companies : TCS, Infosys, Wipro
 * ============================================================================
 *
 * ELI5:
 * -----
 * "x to the power n" means: multiply x by itself n times.
 *
 *   2^3  =  2 * 2 * 2  =  8        (the small raised number is "n")
 *   5^2  =  5 * 5      =  25
 *   7^0  =  1          (anything to the power 0 is 1 - a math rule)
 *
 * C has a ready-made tool called pow(), but the interview asks us to do it
 * OURSELVES using a simple loop, so we really understand it.
 *
 * THE TRICK:
 *   Start with answer = 1.
 *   Multiply answer by x, n times in a loop.
 * ============================================================================
 */

#include <stdio.h>

int main(void)
{
    int x;   /* the base number (the big one) */
    int n;   /* the power (the small raised one) */

    printf("Enter base x: ");
    scanf("%d", &x);
    printf("Enter power n (0 or bigger): ");
    scanf("%d", &n);

    if (n < 0) {
        printf("This beginner version handles power 0 and bigger only.\n");
        return 0;
    }

    /* We use "long long" because powers grow VERY fast and can get huge. */
    long long answer = 1;   /* start at 1 (correct answer when n is 0) */

    /* Multiply by x exactly n times. */
    for (int i = 1; i <= n; i++) {
        answer = answer * x;
    }

    printf("%d ^ %d = %lld\n", x, n, answer);
    return 0;
}

/* ----------------------------------------------------------------------------
 * Why start at 1 and not 0?
 *   If we started at 0, then 0 * anything = 0 forever - always wrong.
 *   Starting at 1 is safe because 1 * x = x, and it makes x^0 = 1 automatically
 *   (the loop runs zero times, so answer stays 1).
 *
 * Compile & run:
 *   gcc q24_power_without_pow.c -o q24
 *   ./q24     (Windows:  q24.exe)
 * Try x=2, n=3  ->  8
 * --------------------------------------------------------------------------*/
