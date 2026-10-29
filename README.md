_This project has been created as part of the 42 curriculum by jlucotte._

# ft_printf

> Because `ft_putnbr()` and `ft_putstr()` aren't enough.

## Description

`ft_printf` is a re-implementation of the libc `printf()` function, packaged as a
static library: `libftprintf.a`.

The goal of the project is to learn how **variadic functions** work in C (functions
that accept a variable number of arguments, using `<stdarg.h>`), and to write code
that is well-structured and easy to extend.

Prototype:

```c
int	ft_printf(const char *format, ...);
```

Like the original, it writes to the standard output and returns the number of
characters printed (or `-1` on write error).

### Supported conversions (mandatory)

| Conversion | Output                                                |
| ---------- | ----------------------------------------------------- |
| `%c`       | a single character                                    |
| `%s`       | a string (C convention, `NULL`-terminated)            |
| `%p`       | a `void *` pointer in hexadecimal (`0x...`)           |
| `%d`       | a signed decimal number (base 10)                     |
| `%i`       | a signed integer in base 10                           |
| `%u`       | an unsigned decimal number (base 10)                  |
| `%x`       | an unsigned number in lowercase hexadecimal (base 16) |
| `%X`       | an unsigned number in uppercase hexadecimal (base 16) |
| `%%`       | a literal percent sign                                |

### Bonus (implemented)

This project implements the full bonus. A conversion follows the syntax:

```
%[flags][width][.precision]conversion
```

| Flag / field   | Effect                                                                                | Applies to    |
| -------------- | ------------------------------------------------------------------------------------- | ------------- |
| `-`            | left-justify the output inside the field width (padding on the right)                 | all           |
| `0`            | pad with zeros instead of spaces (ignored with `-`, and with a precision on integers) | `d i u x X`   |
| _width_        | minimum number of characters printed, padded with spaces by default                   | all           |
| `.`_precision_ | integers: minimum number of digits; strings: maximum number of characters printed     | `d i u x X s` |
| `#`            | prefix `0x` / `0X` for non-zero values                                                | `x X`         |
| ` ` (space)    | print a space before positive numbers                                                 | `d i`         |
| `+`            | always print a sign (`+` or `-`); overrides ` `                                       | `d i`         |

Examples:

```c
ft_printf("[%5d]", 42);     // [   42]
ft_printf("[%-5d]", 42);    // [42   ]
ft_printf("[%05d]", 42);    // [00042]
ft_printf("[%.3d]", 7);     // [007]
ft_printf("[%.2s]", "abc"); // [ab]
ft_printf("[%#x]", 255);    // [0xff]
ft_printf("[%+d]", 42);     // [+42]
ft_printf("[% d]", 42);     // [ 42]
```

> The bonus is only graded if the mandatory part is perfect, so the mandatory
> conversions must keep behaving exactly like the original `printf()`.

## Instructions

### Compilation

```bash
make        # builds libftprintf.a at the root of the repository
make clean  # removes object files
make fclean # removes object files and libftprintf.a
make re     # fclean + all
make bonus  # builds libftprintf.a with the bonus sources (*_bonus.c / *_bonus.h)
```

Bonus files are kept in `_bonus.{c,h}` files as required by the subject; the
mandatory and bonus parts are evaluated separately.

The library is compiled with `cc -Wall -Wextra -Werror` and archived with `ar`
(`libtool` is forbidden).

### Usage

```c
#include "ft_printf.h"

int	main(void)
{
	ft_printf("Hello %s, you are %d years old\n", "world", 42);
	return (0);
}
```

```bash
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o test
./test
```

### Constraints from the subject

- Allowed external functions: `malloc`, `free`, `write`, `va_start`, `va_arg`, `va_copy`, `va_end`.
- Libft is allowed (copied into a `libft/` folder, built by its own Makefile).
- Do **not** implement the buffer management of the original `printf()`.
- Header must be named `ft_printf.h`.
- Code must respect the Norm; no crashes, no memory leaks.

## Algorithm and data structure

### Parsing a conversion

The format string is read character by character. Plain characters are written
as they are. When a `%` is found, the conversion is parsed in a fixed sequence of
stages, each stage consuming only the characters that belong to it before
handing over to the next one:

```
%  →  flags  →  width  →  .precision  →  length  →  conversion
```

| Stage      | Consumes                                                                              | Stops when                                  |
| ---------- | ------------------------------------------------------------------------------------- | ------------------------------------------- |
| flags      | `-` `0` `#` ` ` `+`, in any order, possibly repeated                                  | the character is not a flag                 |
| width      | digits                                                                                | the character is not a digit                |
| .precision | a `.` followed by optional digits (`.` alone means 0)                                 | the character is not a digit                |
| length     | `hh` `h` `ll` `l` `j` `z` `t` `L` (_optional extension, not required by the subject_) | the character is not a length modifier      |
| conversion | one of `c s p d i u x X %`                                                            | always one character: end of the conversion |

Why a staged parser instead of "read until the conversion letter":

- a conversion never ends on a space or at the end of the line: `"%d%s"` has no
  separator, and in `"% d"` the space is itself a flag;
- the same character means different things depending on its position: `0` is a
  flag before the width and a digit inside it (`%010d`), `l` is a length
  modifier, not a conversion;
- an invalid format is detected at the first unexpected character instead of
  silently swallowing text.

### Storing the result: one struct per conversion

Everything the parser finds is stored in a single struct, filled by the parser
and then read by the function that prints the conversion.

| Field        | Meaning                                 | Default                 |
| ------------ | --------------------------------------- | ----------------------- |
| `minus`      | `-` flag: left-justify                  | 0                       |
| `zero`       | `0` flag: pad with zeros                | 0                       |
| `hash`       | `#` flag: `0x` / `0X` prefix            | 0                       |
| `space`      | ` ` flag: space before positive numbers | 0                       |
| `plus`       | `+` flag: always print the sign         | 0                       |
| `width`      | minimum field width                     | 0                       |
| `precision`  | precision value                         | **-1** (= no precision) |
| `length`     | length modifier (_optional extension_)  | none                    |
| `conversion` | conversion character                    | —                       |

Why a struct:

- **Fewer arguments.** Every handler receives one pointer to the struct instead of
  up to nine separate values. The Norm also limits a function to 4 parameters, so
  passing every field separately is not possible.
- **Easy to extend.** Adding a feature (a new flag, `*`, a length modifier) means
  adding a field, without changing the prototype of every handler.
- **Clear separation.** The parser only fills the struct; the handlers only read
  it. Each part can be written and tested on its own.
- The struct is **reset before each conversion**, so a flag from one conversion
  never leaks into the next one.
- `precision` defaults to `-1` rather than `0` because `%d` (no precision) and
  `%.0d` (precision 0) behave differently: `ft_printf("%.0d", 0)` prints nothing.

### Dispatching a conversion: a table of function pointers

Once the struct is filled, the conversion character selects the function that
prints it. Instead of a long chain of `if` (`switch` is forbidden by the Norm),
the list of supported conversions is a single string, the `CONVERSION` macro in
`ft_printf.h`, and the handlers are stored in a `static const` array of function
pointers **in the same order** (`handlers.c`):

```c
# define CONVERSION "cspdiuxX%"

static const t_handler	handlers[] = {print_char, print_str, print_ptr,
	print_int, print_int, print_uint, print_hex, print_hex, print_percent};
```

The handler of the conversion `CONVERSION[i]` is `handlers[i]`. To find it,
`ft_strchr` looks for the character in `CONVERSION`, and the position is the
pointer difference:

```c
found = ft_strchr(CONVERSION, c);
return (handlers[found - CONVERSION]);
```

- The parser (`check_n_store_conversion`) uses the same macro to decide if a
  character is a valid conversion, so the list of conversions is written in
  one place only.
- `'\0'` is checked **before** calling `ft_strchr`: `ft_strchr(s, '\0')` returns
  a pointer to the terminator, not `NULL`, so a format ending with `%` would be
  taken as a valid conversion.
- Every handler has the same prototype (it receives a pointer to the `va_list`
  and a pointer to the struct, and returns the number of characters written), so
  they can all live in one table. The function pointer type `t_handler` is
  declared with a `typedef` in `ft_printf.h`.
- The table is `static const`, which the Norm allows (only non-`const`,
  non-`static` global variables are forbidden).
- The `va_list` is passed by address (`va_list *`): when a handler calls
  `va_arg`, the caller's list advances too.

### Adding or removing a conversion

A conversion is defined in **two places**, which must stay in the same order:

1. its letter in the `CONVERSION` macro (`ft_printf.h`);
2. its handler at the same position in the `handlers[]` array (`handlers.c`).

**To add a conversion**, for example `%b` (unsigned number in binary):

1. Write the handler with the `t_handler` prototype, in its own file or in an
   existing one (for example `print_nbr.c`):

   ```c
   int	print_bin(va_list *ap, t_struct *conv)
   {
   	/* read the argument with va_arg(*ap, ...), apply the flags stored
   	   in conv, print, and return the number of characters written
   	   (or -1 on error) */
   }
   ```

2. Declare it in `ft_printf.h`, in the `// printer` section:

   ```c
   int			print_bin(va_list *ap, t_struct *conv);
   ```

3. Add the letter to the macro (here at the end):

   ```c
   # define CONVERSION "cspdiuxX%b"
   ```

4. Add the handler at the **same position** in `handlers[]`:

   ```c
   static const t_handler	handlers[] = {print_char, print_str, print_ptr,
   	print_int, print_int, print_uint, print_hex, print_hex, print_percent,
   	print_bin};
   ```

5. If the handler is in a new file, add it to `SRCS` in the `Makefile`.
6. Run `make re` and test the new conversion, including with the flags,
   width and precision.

If the conversion only needs a new base, `ft_utoa_base` and `get_digits`
(`number_utils.c`) already take the digits as a string, so `%b` can reuse them
with `"01"` (add a `BINARY` macro next to `DECIMAL` and `HEX_LOWER`).

**To remove a conversion**, do the opposite: remove its letter from
`CONVERSION` and its handler at the same position in `handlers[]`. Then remove
the handler, its prototype and its file in the `Makefile` if nothing else uses
them.

> **Warning:** if `CONVERSION` and `handlers[]` do not have the same number of
> entries, `handlers[found - CONVERSION]` can read outside the array (undefined
> behaviour, often a crash). If the order is different, a conversion is printed
> by the wrong handler. Check both every time you change one.

**Length modifiers (optional extension).** A length modifier such as `z` in `%zu`
is not a conversion and has no entry in the table: the parser stores it in the
struct, and `%zu` is dispatched to the same handler as `%u`. Two helpers read the
argument with the type given by the length (`int`, `long`, `long long`, `size_t`,
`intmax_t`, ...) and return it as the widest signed or unsigned type, so the
base-conversion function stays the same for every length.

<!-- TODO: to be completed once the implementation is written:
     - how the number of printed characters is counted and returned (and -1 on write error)
     - how numbers are converted to base 10 / base 16 (one function taking an
       unsigned long long and a digit string; the sign of %d is handled before)
     - how padding, sign/prefix and precision are combined for each conversion
       (order: sign or 0x -> zeros -> digits, with spaces left or right) -->

## Resources

### printf and format strings

- [man 3 printf (man7.org)](https://man7.org/linux/man-pages/man3/printf.3.html) — reference behaviour, return value, conversions and flags.
- [cppreference — printf, fprintf, ...](https://en.cppreference.com/w/c/io/fprintf) — clear table of every conversion and flag, with examples.
- [GNU C Library — Formatted Output](https://www.gnu.org/software/libc/manual/html_node/Formatted-Output.html)
- [GNU C Library — Output Conversion Syntax](https://www.gnu.org/software/libc/manual/html_node/Output-Conversion-Syntax.html) — how `%[flags][width][.precision]conversion` is structured (useful for the bonus).

### Variadic functions (`<stdarg.h>`)

- [man 3 stdarg (man7.org)](https://man7.org/linux/man-pages/man3/stdarg.3.html) — `va_start`, `va_arg`, `va_copy`, `va_end`, all on one page.
- [cppreference — Variadic functions](https://en.cppreference.com/w/c/variadic)
- One page per macro (cppreference):
  - [`va_list`](https://en.cppreference.com/w/c/variadic/va_list) — the type that holds the state of the argument list.
  - [`va_start`](https://en.cppreference.com/w/c/variadic/va_start) — starts reading the arguments after the last named parameter.
  - [`va_arg`](https://en.cppreference.com/w/c/variadic/va_arg) — returns the next argument as the given type.
  - [`va_copy`](https://en.cppreference.com/w/c/variadic/va_copy) — duplicates a `va_list` (to read the arguments twice).
  - [`va_end`](https://en.cppreference.com/w/c/variadic/va_end) — ends reading; one `va_end` per `va_start` / `va_copy`.
- [GNU C Library — Receiving Arguments](https://www.gnu.org/software/libc/manual/html_node/Receiving-Arguments.html) and [Argument Access Macros](https://www.gnu.org/software/libc/manual/html_node/Argument-Macros.html).
- [cppreference — Implicit conversions](https://en.cppreference.com/w/c/language/conversion) — "default argument promotions": a `char` passed through `...` arrives as an `int`.
- [GNU C Library — Variadic Functions](https://www.gnu.org/software/libc/manual/html_node/Variadic-Functions.html) — includes the rules on default argument promotions (why `char` is read as `int`).
- [Wikipedia — Variadic function](https://en.wikipedia.org/wiki/Variadic_function)
- [C11 standard draft N1570](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf) — §7.16 (`<stdarg.h>`) and §7.21.6.1 (`fprintf`), the official specification.

### Numbers and bases

- [Wikipedia — Hexadecimal](https://en.wikipedia.org/wiki/Hexadecimal)
- [Wikipedia — Two's complement](https://en.wikipedia.org/wiki/Two%27s_complement) — how negative numbers are stored (useful for `INT_MIN`, `%u` and `%x` with negative values).

### Building a static library

- [man 1 ar (man7.org)](https://man7.org/linux/man-pages/man1/ar.1.html)
- [Program Library HOWTO — Static Libraries](https://tldp.org/HOWTO/Program-Library-HOWTO/static-libraries.html)
- [GNU make manual](https://www.gnu.org/software/make/manual/make.html)
- [man 2 write (man7.org)](https://man7.org/linux/man-pages/man2/write.2.html)

### Norm, debugging and testing

- [42 Norminette](https://github.com/42School/norminette)
- [Valgrind — Quick Start](https://valgrind.org/docs/manual/quick-start.html) — checking for memory leaks.
- [printfTester (Tripouille)](https://github.com/Tripouille/printfTester)
- [ft_printf_tester (paulo-santana)](https://github.com/paulo-santana/ft_printf_tester)
- [francinette](https://github.com/xicodomingues/francinette)

### Use of AI

AI (Claude) was used to:

- summarise and explain the subject;
- gather the documentation links listed above;
- generate the skeleton of this README.

AI was **not** used to write the source code of the library.
