# 🍼 The Absolute-Beginner Concepts Primer

> Read this **first** if you have never written code before.
> It explains every idea used in the programs — in plain, everyday words.
> Imagine I'm explaining to a curious 5-year-old. 🧸

---

## 1. What is a computer, really?

A computer is a very fast but very *simple* machine. It only understands two things:

- **OFF** → written as `0`
- **ON**  → written as `1`

That's it. Everything — your photos, games, songs, this page — is secretly a giant pile of `0`s and `1`s.

---

## 2. What is "code"?

**Code** is a list of instructions we write for the computer, like a recipe.
We write it in a language the computer can understand. Here we use **C**.

A tiny C program looks like this:

```c
#include <stdio.h>      // borrow a toolbox that knows how to print

int main(void) {        // the program starts here
    printf("Hello!\n");  // print the word Hello on the screen
    return 0;            // tell the computer "all done, no problems"
}
```

| Piece | What it means (ELI5) |
|-------|----------------------|
| `#include <stdio.h>` | "Bring me the toolbox for reading and printing." |
| `int main(void)` | "This is where the program begins." |
| `{ ... }` | Curly braces hold a group of instructions together, like a lunchbox. |
| `printf("...")` | Print something on the screen. |
| `\n` | A secret code that means "go to a new line" (like pressing Enter). |
| `;` | A full-stop. **Every instruction ends with a semicolon.** |
| `return 0;` | "Finished happily." |

---

## 3. What is a variable?

A **variable** is a labelled box that holds a value.

```c
int age = 5;   // make a box called "age", put the number 5 inside
```

- `int` means the box holds a whole number (1, 2, 3, …). "int" = *integer*.
- `age` is the box's name (you choose it).
- `= 5` puts the number 5 inside.

Other box types you'll see:

| Type | Holds | Example |
|------|-------|---------|
| `int` | a normal whole number | `42` |
| `long` / `long long` | a **really big** whole number | `1000000000000` |

---

## 4. Reading input and printing output

```c
int number;                  // an empty box
printf("Enter a number: ");  // ask the user
scanf("%d", &number);        // put what they type into the box
printf("You typed %d\n", number);  // show it back
```

- `scanf` = "scan in" what the user types.
- `%d` is a placeholder that means "a whole number goes here".
- The `&` in `&number` means "the address of the box" — `scanf` needs to know *where* to put the value. (Just remember: **`scanf` needs an `&`, `printf` does not.**)

---

## 5. Making decisions: `if`

```c
if (number > 0) {
    printf("It is positive\n");
} else {
    printf("It is zero or negative\n");
}
```

Reads like English: *if* the number is bigger than 0, do the first thing, *else* (otherwise) do the second.

Comparisons you'll use: `==` (equal), `!=` (not equal), `<` `>` `<=` `>=`.

> ⚠️ One `=` **stores** a value. Two `==` **compares**. Don't mix them up!

---

## 6. Doing things again and again: loops

A **loop** repeats instructions so you don't copy-paste.

**`while` loop** — "keep going *while* something is true":

```c
while (number > 0) {
    // do something, and eventually make number smaller
}
```

**`for` loop** — "repeat a fixed number of times":

```c
for (int i = 0; i < 5; i++) {
    printf("%d ", i);   // prints 0 1 2 3 4
}
```

- `int i = 0` → start counting at 0
- `i < 5` → keep going while i is less than 5
- `i++` → add 1 to i each time (`i++` is short for `i = i + 1`)

---

## 7. The two magic math tools for digits

These two appear in almost every program here. Learn them once:

| Tool | Name | What it does | Example |
|------|------|--------------|---------|
| `%` | **modulo / remainder** | the leftover after dividing | `13 % 2 = 1`, `1234 % 10 = 4` |
| `/` | **integer division** | divide and throw away the leftover | `13 / 2 = 6`, `1234 / 10 = 123` |

🔑 **Two patterns to memorise:**

- `% 2` and `/ 2` → used to break a number into **binary** (0s and 1s).
- `% 10` and `/ 10` → used to break a number into its **decimal digits**.

```
1234 % 10 = 4   ← grabs the LAST digit
1234 / 10 = 123 ← removes the LAST digit
```

Do those repeatedly and you can peel a number apart digit by digit. 🧅

---

## 8. Binary vs decimal (super important)

We humans count in **decimal** (base 10) using digits `0–9`.
Computers count in **binary** (base 2) using only `0` and `1`.

**Binary place values double each step (right → left):**

```
 place:  128  64  32  16   8   4   2   1
 bits:     0   0   0   0   1   1   0   1   = 8 + 4 + 1 = 13
```

So `13` in decimal = `1101` in binary. Both files **Q21** and **Q22** are just converting between these two worlds.

---

## 9. How does the computer store NEGATIVE numbers? (two's complement)

Binary has no minus sign — only `0`s and `1`s! So computers use a trick called
**two's complement**. To write a negative number (in, say, 8 bits):

1. Write the **positive** version in binary.
2. **Flip** every bit (0↔1). *(this flip is called "one's complement")*
3. **Add 1**.

Example for **-5** using 8 bits:

```
+5            = 0000 0101
flip all bits = 1111 1010   (one's complement)
add 1         = 1111 1011   ← this is -5
```

The **leftmost bit** is the **sign bit**: `0` = positive, `1` = negative.
The full, runnable demo is in [`src/negative_to_binary_2s_complement.c`](src/negative_to_binary_2s_complement.c).

---

## 10. What is recursion? (Day 7's big idea)

**Recursion** is when a function **calls itself** to solve a smaller copy of the
same problem. Think of **Russian nesting dolls** 🪆 — open one and there's a
smaller one inside, again and again, until the tiniest doll that can't open.

Every recursion needs **two parts**, or it never stops:

1. **Base case** — the tiniest doll. The simplest input where we already know
   the answer and we **STOP**. *(e.g. `factorial(1) = 1`)*
2. **Recursive case** — the function calls itself on a **smaller** input,
   getting closer to the base case each time. *(e.g. `n! = n × (n-1)!`)*

> ⚠️ **No base case = infinite recursion = crash.** Always make sure each call
> gets *closer* to the base case.

---

## 11. How to compile and run a C program

C code must be **compiled** (translated into computer language) before it runs.
We use a compiler called **gcc**.

```bash
gcc q21_decimal_to_binary.c -o q21   # 1) compile -> makes a program named q21
./q21                                 # 2) run it   (Windows:  q21.exe  or  .\q21.exe)
```

Don't have gcc? Two easy choices:
- **Online:** paste the code into <https://www.onlinegdb.com> and press Run.
- **Windows install:** install **MinGW-w64** (gives you `gcc`), or use an IDE like
  Code::Blocks / Dev-C++ which include a compiler.

---

🎉 **That's the whole toolkit.** With variables, `if`, loops, `% / 10`, `% / 2`,
and recursion, you can understand *every* program in this repo. Now open
[`docs/day6.md`](docs/day6.md) and follow along!
