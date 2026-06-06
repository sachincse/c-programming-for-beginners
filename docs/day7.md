# 📅 Day 7 — Recursion (Q25–Q28)

> Companies that ask these: **TCS, Infosys, Wipro**
> New to recursion? Re-read [section 10 of the Concepts Primer](../00_concepts_primer.md#10-what-is-recursion-day-7s-big-idea). 🪆

| # | Problem | Code file |
|---|---------|-----------|
| Q25 | Factorial (recursive) | [`q25_recursive_factorial.c`](../src/q25_recursive_factorial.c) |
| Q26 | Fibonacci (recursive) | [`q26_recursive_fibonacci.c`](../src/q26_recursive_fibonacci.c) |
| Q27 | Sum of digits (recursive) | [`q27_recursive_sum_of_digits.c`](../src/q27_recursive_sum_of_digits.c) |
| Q28 | Reverse a number (recursive) | [`q28_recursive_reverse_number.c`](../src/q28_recursive_reverse_number.c) |

---

## 🪆 Recursion in one picture

Every recursive function has a **base case** (when to STOP) and a
**recursive case** (call itself on something smaller).

```mermaid
flowchart TD
    A([function called with n]) --> B{base case reached?}
    B -- yes --> C[return the known answer] --> D([STOP])
    B -- no --> E[do a little work] --> F[call itself with a SMALLER input]
    F --> A
```

---

## Q25 — Factorial

`n! = n × (n-1) × … × 1`, and `0! = 1`. Rule: **`n! = n × (n-1)!`**

- **Base case:** `factorial(0) = 1`, `factorial(1) = 1`
- **Recursive case:** `return n * factorial(n - 1)`

```mermaid
flowchart TD
    A["factorial(4)"] --> B["4 * factorial(3)"]
    B --> C["3 * factorial(2)"]
    C --> D["2 * factorial(1)"]
    D --> E["factorial(1) = 1 (BASE)"]
    E --> F["2*1 = 2"]
    F --> G["3*2 = 6"]
    G --> H["4*6 = 24 ✅"]
```

---

## Q26 — Fibonacci

Series: `0, 1, 1, 2, 3, 5, 8, …` Rule: **`fib(n) = fib(n-1) + fib(n-2)`**

- **Base cases:** `fib(0) = 0`, `fib(1) = 1`
- **Recursive case:** `return fib(n-1) + fib(n-2)`

```mermaid
flowchart TD
    A["fib(4)"] --> B["fib(3)"]
    A --> C["fib(2)"]
    B --> D["fib(2)"]
    B --> E["fib(1)=1"]
    C --> F["fib(1)=1"]
    C --> G["fib(0)=0"]
    D --> H["fib(1)=1"]
    D --> I["fib(0)=0"]
```

> ⚠️ Notice `fib(2)` is computed **twice** — this simple version repeats work,
> so it's slow for large `n`. Great for learning, not for big numbers.

---

## Q27 — Sum of Digits

`1234 → 1+2+3+4 = 10`. Rule: **last digit + sum of the rest**.

- Grab last digit: `number % 10`
- Drop last digit: `number / 10`
- **Base case:** `sumOfDigits(0) = 0`
- **Recursive case:** `return (number % 10) + sumOfDigits(number / 10)`

```mermaid
flowchart TD
    A["sum(1234)"] --> B["4 + sum(123)"]
    B --> C["3 + sum(12)"]
    C --> D["2 + sum(1)"]
    D --> E["1 + sum(0)"]
    E --> F["sum(0) = 0 (BASE)"]
    F --> G["1+0=1 → 2+1=3 → 3+3=6 → 4+6=10 ✅"]
```

---

## Q28 — Reverse a Number

`1234 → 4321`. We carry a second box `rev` that builds the answer:
**`rev = rev*10 + lastDigit`**, then continue with the rest.

- **Base case:** when `number == 0`, return `rev`
- **Recursive case:** `return reverseNumber(number/10, rev*10 + number%10)`

```mermaid
flowchart TD
    A["reverse(1234, rev=0)"] --> B["reverse(123, rev=4)"]
    B --> C["reverse(12, rev=43)"]
    C --> D["reverse(1, rev=432)"]
    D --> E["reverse(0, rev=4321)"]
    E --> F["number==0 → return 4321 ✅"]
```

> 💡 Negative numbers: remember the minus sign, reverse the positive part,
> then put the sign back (`-1234 → -4321`). The code does this for you.

---

⬅️ Back to [Day 6 — Numbers & Bits](day6.md) · 🏠 [Home](../README.md)
