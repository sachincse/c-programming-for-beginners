# ⭐ Bonus — Negative Numbers in Binary (Two's Complement) — Full Explainer

> **Companies:** TCS, Infosys, Wipro (very common follow-up to "decimal → binary")
> Read [Q21](Q21_decimal_to_binary.md) first so you're comfortable with binary. 🧱

---

## 1. What is the problem asking?

> "We know how to write **positive** numbers in binary. But binary only has `0`
> and `1` — **there is no minus sign!** So how does a computer store **-5**?"

The answer is a clever, world-standard trick called **two's complement**.

---

## 2. First, the big idea: fixed-size boxes 📦

A computer doesn't store endless digits. It uses a **fixed number of bits**.
Here we use **8 bits** (8 boxes), which can hold values from **-128 to +127**.

```
8 boxes:  [ _ ][ _ ][ _ ][ _ ][ _ ][ _ ][ _ ][ _ ]
           ↑
     leftmost box = the SIGN BIT  (0 = positive, 1 = negative)
```

---

## 3. The rule for a negative number (3 steps)

To write a negative number like **-5** in 8-bit two's complement:

```
STEP 1:  Write +5 in normal 8-bit binary   →  0000 0101
STEP 2:  FLIP every bit (0↔1)              →  1111 1010   (this is "one's complement")
STEP 3:  ADD 1 to the result               →  1111 1011   ← this is -5 ✅
```

For **positive numbers and zero**, you do nothing special — just write the
normal binary (`+5 = 0000 0101`, `0 = 0000 0000`).

> 🔍 **Why does this strange trick work?** Because with it, normal binary
> addition "just works" across positive and negative numbers, and `x + (-x)`
> naturally wraps around to `0`. That's why every computer on Earth uses it.

---

## 4. Picture it (diagram)

```mermaid
flowchart TD
    A([Start: read number, use 8 bits]) --> B{number &gt;= 0?}
    B -- yes --> C["just write normal 8-bit binary"] --> Z([End])
    B -- no --> D["STEP 1: write +|number| in 8-bit binary"]
    D --> E["STEP 2: flip every bit (one's complement)"]
    E --> F["STEP 3: add 1 (with carry)"]
    F --> G["result = two's complement of the negative number"]
    G --> Z
```

---

## 5. Let's build the code step by step

> 🧵 We'll thread one example through every step: the user types **`-5`**.

### Step A — read the number and check the range

```c
#define BITS 8

int number;
printf("Enter a number between -128 and 127: ");
scanf("%d", &number);
```
🖥️ **Output after Step A:**
```
Enter a number between -128 and 127: -5
```
`number` now holds **-5**.

### Step B — a helper to print an 8-bit array nicely

```c
void printBits(int bits[]) {
    for (int i = 0; i < BITS; i++) {
        if (i == 4) printf(" ");   // a gap after 4 bits, just for readability
        printf("%d", bits[i]);
    }
    printf("\n");
}
```
🖥️ **Output after Step B:** *nothing yet* — this only **defines** a reusable tool.
Later, if `bits = {1,1,1,1,1,0,1,1}` and we call `printBits(bits)`, it prints:
```
1111 1011
```

### Step C — positive/zero case: write normal binary

```c
int n = number;
for (int i = BITS - 1; i >= 0; i--) {  // fill from the rightmost box
    bits[i] = n % 2;
    n = n / 2;
}
```
🖥️ **State after Step C:** for our example `number = -5`, this branch is **skipped**
(it only runs for 0 or positive numbers). *If instead `number = 5`, it would fill*
`bits = 0000 0101`.

### Step D — negative case, STEP 1: binary of the positive twin

```c
int magnitude = -number;        // e.g. -5 → 5
int n = magnitude;
for (int i = BITS - 1; i >= 0; i--) {
    bits[i] = n % 2;
    n = n / 2;
}
```
🖥️ **State after Step D (number = -5):** `magnitude = 5`, and
```
bits = 0000 0101
```

### Step E — STEP 2: flip every bit

```c
for (int i = 0; i < BITS; i++) {
    bits[i] = 1 - bits[i];   // 0 → 1 and 1 → 0
}
```
🖥️ **State after Step E:**
```
bits = 1111 1010   (one's complement of 0000 0101)
```

### Step F — STEP 3: add 1, carrying from the right

```c
int carry = 1;   // the "1" we add
for (int i = BITS - 1; i >= 0 && carry == 1; i--) {
    int sum = bits[i] + carry;
    bits[i] = sum % 2;   // digit stays here
    carry   = sum / 2;   // 1 if it overflows into the next box
}
```
🖥️ **State after Step F:** adding 1 to `1111 1010` gives
```
bits = 1111 1011     ← this is -5 in two's complement ✅
```
And the program then calls `printBits(bits)`, so the **final output** is:
```
So -5 in 8-bit two's complement = 1111 1011
```

---

## 6. The complete program ✅

```c
#include <stdio.h>

#define BITS 8

void printBits(int bits[]) {
    for (int i = 0; i < BITS; i++) {
        if (i == 4) printf(" ");
        printf("%d", bits[i]);
    }
    printf("\n");
}

int main(void) {
    int number;
    printf("Enter a number between -128 and 127: ");
    scanf("%d", &number);

    if (number < -128 || number > 127) {
        printf("Out of range for 8 bits. Use -128 to 127.\n");
        return 0;
    }

    int bits[BITS];

    if (number >= 0) {                       // positive / zero
        int n = number;
        for (int i = BITS - 1; i >= 0; i--) { bits[i] = n % 2; n /= 2; }
        printf("Binary (8-bit) = ");
        printBits(bits);
        return 0;
    }

    int magnitude = -number;                 // negative → 3 steps
    int n = magnitude;
    for (int i = BITS - 1; i >= 0; i--) { bits[i] = n % 2; n /= 2; }
    printf("STEP 1 (+%d binary): ", magnitude); printBits(bits);

    for (int i = 0; i < BITS; i++) bits[i] = 1 - bits[i];   // STEP 2: flip
    printf("STEP 2 (flip bits):  "); printBits(bits);

    int carry = 1;                                          // STEP 3: add 1
    for (int i = BITS - 1; i >= 0 && carry == 1; i--) {
        int sum = bits[i] + carry;
        bits[i] = sum % 2;
        carry   = sum / 2;
    }
    printf("STEP 3 (add 1):      "); printBits(bits);

    printf("\nSo %d in 8-bit two's complement = ", number);
    printBits(bits);
    return 0;
}
```

📄 Runnable file: [`../src/negative_to_binary_2s_complement.c`](../src/negative_to_binary_2s_complement.c)

---

## 7. Dry run 🏃 — let's trace `number = -5`

**STEP 1 — write +5 in 8 bits** (`magnitude = 5`):

| Box index (i) | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|---|---|---|---|---|---|---|---|
| bit | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 1 |

→ `0000 0101`

**STEP 2 — flip every bit** (`1 - bit`):

| Box index (i) | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|---|---|---|---|---|---|---|---|
| bit | 1 | 1 | 1 | 1 | 1 | 0 | 1 | 0 |

→ `1111 1010`

**STEP 3 — add 1** (start from the right, `carry = 1`):

| i (right→left) | bit before | bit + carry | new bit | new carry |
|---|---|---|---|---|
| 7 | 0 | 0 + 1 = 1 | **1** | 0 |
| (carry is now 0 → loop stops) | | | | |

Result: `1111 1011`

✅ **Output:** `So -5 in 8-bit two's complement = 1111 1011`

---

## 7½. More worked examples — every single step 🔬

### Example A — `number = -1`  (expected `1111 1111`)

| Step | Bits | Note |
|------|------|------|
| STEP 1: +1 in binary | `0000 0001` | the positive twin |
| STEP 2: flip all bits | `1111 1110` | one's complement |
| STEP 3: add 1 | `1111 1111` | rightmost `0`→`1`, no carry |

**Add-1 detail:** rightmost bit `0 + 1 = 1`, carry becomes 0, loop stops.
✅ **Output:** `-1 = 1111 1111`  *(all ones — a classic to memorise)*

---

### Example B — `number = -2`  (expected `1111 1110`)

| Step | Bits | Note |
|------|------|------|
| STEP 1: +2 in binary | `0000 0010` | |
| STEP 2: flip all bits | `1111 1101` | |
| STEP 3: add 1 | `1111 1110` | rightmost `1 + 1 = 0` carry 1; next `0 + 1 = 1` |

**Add-1 detail (right→left):**

| i (right→left) | bit | bit + carry | new bit | new carry |
|---|---|---|---|---|
| 7 | 1 | 1 + 1 = 2 | **0** | 1 |
| 6 | 0 | 0 + 1 = 1 | **1** | 0 → stop |

✅ **Output:** `-2 = 1111 1110`

---

### Example C — `number = -128`  (expected `1000 0000`, the most negative)

| Step | Bits | Note |
|------|------|------|
| STEP 1: +128 in binary | `1000 0000` | |
| STEP 2: flip all bits | `0111 1111` | |
| STEP 3: add 1 | `1000 0000` | the `1` ripples all the way across |

**Add-1 detail — the carry "ripples":**

| i (right→left) | bit | bit + carry | new bit | new carry |
|---|---|---|---|---|
| 7 | 1 | 2 | 0 | 1 |
| 6 | 1 | 2 | 0 | 1 |
| 5 | 1 | 2 | 0 | 1 |
| 4 | 1 | 2 | 0 | 1 |
| 3 | 1 | 2 | 0 | 1 |
| 2 | 1 | 2 | 0 | 1 |
| 1 | 1 | 2 | 0 | 1 |
| 0 | 0 | 1 | 1 | 0 → stop |

✅ **Output:** `-128 = 1000 0000`  *(sign bit 1, everything else 0)*

---

### Example D — `number = +7`  (positive → no special steps)

Positive numbers skip the flip-and-add entirely; just write normal binary:

| Box index (i) | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|---|---|---|---|---|---|---|---|
| bit | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 1 |

✅ **Output:** `+7 = 0000 0111`  *(sign bit 0 = positive)*

---

### 🔁 Sanity check: does `5 + (-5)` give `0`?

Two's complement is designed so normal binary addition "just works":

```
   0000 0101   (+5)
 + 1111 1011   (-5)
 -----------
  10000 0000
```
The leftmost `1` is a **9th** bit — but we only keep **8** boxes, so it falls off
the edge and is thrown away, leaving `0000 0000` = **0**. 🎉 That overflow-wrap is
exactly *why* this representation was chosen.

---

## 8. Hand-check table (memorise a few) 📋

| Number | 8-bit two's complement | Note |
|--------|------------------------|------|
| `+5`   | `0000 0101` | normal binary |
| `0`    | `0000 0000` | all zeros |
| `-1`   | `1111 1111` | all ones |
| `-2`   | `1111 1110` | |
| `-5`   | `1111 1011` | our example |
| `-128` | `1000 0000` | most negative 8-bit value |

> 🧠 **Quick fact:** the leftmost bit is `0` for every positive number and `1`
> for every negative number — that's the **sign bit**.

---

## 9. Common mistakes ⚠️

- **Skipping the "+1" step.** Flipping alone gives *one's* complement, not *two's*.
- **Forgetting the carry** when adding 1 (e.g. `0111 1111 + 1` must ripple to
  `1000 0000`).
- **Going out of range.** With 8 bits you can only represent **-128 … +127**.

---

⬅️ Previous: [Q28 — Recursive Reverse Number](Q28_recursive_reverse_number.md) · 🏠 [Home](../README.md)
