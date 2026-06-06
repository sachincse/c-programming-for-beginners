# 🔢 Q22 — Convert Binary to Decimal (Full Explainer)

> **Companies:** TCS, Infosys, Wipro
> This is the **reverse** of [Q21](Q21_decimal_to_binary.md). 🔁

---

## 1. What is the problem asking?

> "Take a binary number (only 0s and 1s, like **1101**) and turn it back into a
> normal number (like **13**)."

---

## 2. A real-life analogy 🎟️

Binary digits are like **prize tickets of different values**. Reading from the
**right**, each ticket is worth **double** the one before it:

```
ticket value:  ... 16   8   4   2   1
```

For `1101`, you "own" a ticket wherever there's a `1`:

```
 1    1    0    1
 8  + 4  + 0  + 1   =  13
```

Add up the tickets you own → that's your decimal number. 🎉

---

## 3. The logic

> **Each binary digit has a "place value" that doubles (1, 2, 4, 8, …).
> Multiply each digit by its place value and add everything up.**

We read the digits from the **right** using our digit tools:

| Tool | Meaning | Example |
|------|---------|---------|
| `% 10` | grabs the **last** digit | `1101 % 10 = 1` |
| `/ 10` | **removes** the last digit | `1101 / 10 = 110` |

And we keep a `placeValue` that starts at `1` and **doubles** each step.

---

## 4. Picture it (diagram)

```mermaid
flowchart TD
    A([Start: read binary number]) --> B["decimal = 0<br/>placeValue = 1"]
    B --> C{binary &gt; 0?}
    C -- yes --> D["digit = binary % 10"]
    D --> E["decimal = decimal + digit * placeValue"]
    E --> F["placeValue = placeValue * 2<br/>binary = binary / 10"]
    F --> C
    C -- no --> G["print decimal"] --> H([End])
```

---

## 5. Let's build the code step by step

> 🧵 We'll thread one example through every step: the user types **`1101`**.

### Step A — read the binary number

We read it as a `long` (a big whole number) because `1101` is just digits to us.

```c
long binary;
printf("Enter a binary number (only 0s and 1s): ");
scanf("%ld", &binary);
```
🖥️ **Output after Step A:**
```
Enter a binary number (only 0s and 1s): 1101
```
`binary` now holds **1101**.

### Step B — set up the answer and the place value

```c
int decimal = 0;     // the running total starts at 0
int placeValue = 1;  // rightmost place is worth 1
```
🖥️ **State after Step B:** `decimal = 0`, `placeValue = 1`. Nothing prints yet.

### Step C — peel digits from the right and add their value

```c
while (binary > 0) {
    int digit = binary % 10;              // last digit (should be 0 or 1)
    decimal = decimal + digit * placeValue;
    placeValue = placeValue * 2;          // next place is worth double
    binary = binary / 10;                 // drop the digit we used
}
```
🖥️ **State after Step C (binary = 1101):** the loop runs 4 times and builds up
`decimal`:
```
1101 → decimal=1 → decimal=1 → decimal=5 → decimal=13
```
`decimal` is now **13** (and `binary` has shrunk to 0, so the loop ends).

### Step D — (safety) reject anything that isn't 0 or 1

```c
if (digit != 0 && digit != 1) {
    printf("That is not a valid binary number (use only 0 and 1).\n");
    return 1;
}
```
🖥️ **State after Step D:** for `1101` every digit is 0 or 1, so this check never
fires. *(If the user typed `1201`, it would print* `That is not a valid binary
number (use only 0 and 1).` *and stop.)*

### Step E — print the result

```c
printf("Decimal = %d\n", decimal);
```
🖥️ **Output after Step E (the final result):**
```
Decimal = 13
```

---

## 6. The complete program ✅

```c
#include <stdio.h>

int main(void) {
    long binary;

    printf("Enter a binary number (only 0s and 1s): ");
    scanf("%ld", &binary);

    int decimal = 0;     // answer
    int placeValue = 1;  // 1, 2, 4, 8, ...

    while (binary > 0) {
        int digit = binary % 10;          // last digit

        if (digit != 0 && digit != 1) {   // safety check
            printf("That is not a valid binary number (use only 0 and 1).\n");
            return 1;
        }

        decimal = decimal + digit * placeValue;
        placeValue = placeValue * 2;
        binary = binary / 10;
    }

    printf("Decimal = %d\n", decimal);
    return 0;
}
```

📄 Runnable file: [`../src/q22_binary_to_decimal.c`](../src/q22_binary_to_decimal.c)

---

## 7. Dry run 🏃 — let's trace `binary = 1101`

| Step | `binary` before | `digit = binary % 10` | `placeValue` | `digit * placeValue` | `decimal` after | `binary / 10` |
|------|------|------|------|------|------|------|
| 1 | 1101 | **1** | 1  | 1  | 0 + 1 = **1**  | 110 |
| 2 | 110  | **0** | 2  | 0  | 1 + 0 = **1**  | 11  |
| 3 | 11   | **1** | 4  | 4  | 1 + 4 = **5**  | 1   |
| 4 | 1    | **1** | 8  | 8  | 5 + 8 = **13** | 0   |
| — | 0 | loop stops | — | — | — | — |

✅ **Output:** `Decimal = 13`

---

## 7½. More worked examples — every single iteration 🔬

### Example A — `binary = 101`  (expected `5`)

| Step | `binary` before | `digit = % 10` | `placeValue` | `digit * place` | `decimal` after | `/ 10` |
|------|------|------|------|------|------|------|
| 1 | 101 | **1** | 1 | 1 | 0 + 1 = **1** | 10 |
| 2 | 10  | **0** | 2 | 0 | 1 + 0 = **1** | 1  |
| 3 | 1   | **1** | 4 | 4 | 1 + 4 = **5** | 0  |
| — | 0 | stop | — | — | — | — |

✅ **Output:** `Decimal = 5`  *(check: 4 + 0 + 1 = 5)*

---

### Example B — `binary = 1000`  (expected `8`)

| Step | `binary` before | `digit = % 10` | `placeValue` | `digit * place` | `decimal` after | `/ 10` |
|------|------|------|------|------|------|------|
| 1 | 1000 | **0** | 1 | 0 | 0 + 0 = **0** | 100 |
| 2 | 100  | **0** | 2 | 0 | 0 + 0 = **0** | 10  |
| 3 | 10   | **0** | 4 | 0 | 0 + 0 = **0** | 1   |
| 4 | 1    | **1** | 8 | 8 | 0 + 8 = **8** | 0   |
| — | 0 | stop | — | — | — | — |

✅ **Output:** `Decimal = 8`  *(only the place worth 8 had a 1)*

---

### Example C — `binary = 1111`  (expected `15`)

| Step | `binary` before | `digit` | `placeValue` | `digit * place` | `decimal` after | `/ 10` |
|------|------|------|------|------|------|------|
| 1 | 1111 | 1 | 1 | 1 | 0 + 1 = **1**  | 111 |
| 2 | 111  | 1 | 2 | 2 | 1 + 2 = **3**  | 11  |
| 3 | 11   | 1 | 4 | 4 | 3 + 4 = **7**  | 1   |
| 4 | 1    | 1 | 8 | 8 | 7 + 8 = **15** | 0   |
| — | 0 | stop | — | — | — | — |

✅ **Output:** `Decimal = 15`  *(all four bits ON: 8+4+2+1 = 15, the max for 4 bits)*

---

### Example D — `binary = 10110`  (expected `22`)

| Step | `binary` before | `digit` | `placeValue` | `digit * place` | `decimal` after | `/ 10` |
|------|------|------|------|------|------|------|
| 1 | 10110 | 0 | 1  | 0  | 0 + 0 = **0**  | 1011 |
| 2 | 1011  | 1 | 2  | 2  | 0 + 2 = **2**  | 101  |
| 3 | 101   | 1 | 4  | 4  | 2 + 4 = **6**  | 10   |
| 4 | 10    | 0 | 8  | 0  | 6 + 0 = **6**  | 1    |
| 5 | 1     | 1 | 16 | 16 | 6 + 16 = **22** | 0   |
| — | 0 | stop | — | — | — | — |

✅ **Output:** `Decimal = 22`  *(check: 16 + 0 + 4 + 2 + 0 = 22)*

---

## 8. Common mistakes ⚠️

- **Forgetting to double `placeValue`.** It must go `1 → 2 → 4 → 8 …`, not stay at 1.
- **Doubling at the wrong time.** Use the current place value first, *then* double it
  for the next loop.
- **Typing a digit other than 0/1.** That's not binary — our safety check catches it.

---

## 9. Try it yourself 🎯

| Input (binary) | Expected (decimal) |
|----------------|--------------------|
| 1101 | 13 |
| 101  | 5  |
| 1000 | 8  |
| 1111 | 15 |

⬅️ Previous: [Q21 — Decimal to Binary](Q21_decimal_to_binary.md) · ➡️ Next: [Q23 — Count Set Bits](Q23_count_set_bits.md)
