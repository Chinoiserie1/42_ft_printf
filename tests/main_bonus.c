/*
** Bonus part: flags '-' '0' '.' width, then '#' ' ' '+'
** Build:
**   make bonus && cc -Wall -Wextra -Wno-format tests/main_bonus.c -L. -lftprintf -o test_bonus
*/

#include "tester.h"

static void	test_width(void)
{
	SECTION("Width");
	TEST("[%5d]", 42);
	TEST("[%5d]", -42);
	TEST("[%1d]", 12345);
	TEST("[%5c]", 'a');
	TEST("[%5s]", "hi");
	TEST("[%2s]", "hello");
	TEST("[%5u]", 7u);
	TEST("[%8x]", 255);
	TEST("[%8X]", 255);
	TEST("[%20p]", (void *)0xdeadbeef);
	TEST("[%10s]", (char *)NULL);
	TEST("[%5c]", 0);
}

static void	test_minus(void)
{
	SECTION("'-' flag");
	TEST("[%-5d]", 42);
	TEST("[%-5d]", -42);
	TEST("[%-5c]", 'a');
	TEST("[%-5s]", "hi");
	TEST("[%-5u]", 7u);
	TEST("[%-8x]", 255);
	TEST("[%-8X]", 255);
	TEST("[%-20p]", (void *)0xdeadbeef);
	TEST("[%-5c]", 0);
	TEST("[%-1d]", 12345);
}

static void	test_zero(void)
{
	SECTION("'0' flag");
	TEST("[%05d]", 42);
	TEST("[%05d]", -42);
	TEST("[%05i]", 0);
	TEST("[%05u]", 42u);
	TEST("[%08x]", 255);
	TEST("[%08X]", 255);
	TEST("[%011d]", INT_MIN);
	TEST("[%-05d]", 42);
}

static void	test_precision_numbers(void)
{
	SECTION("'.' precision on numbers");
	TEST("[%.3d]", 7);
	TEST("[%.3d]", -7);
	TEST("[%.3d]", 12345);
	TEST("[%.0d]", 0);
	TEST("[%.d]", 0);
	TEST("[%.0d]", 5);
	TEST("[%5.0d]", 0);
	TEST("[%.5u]", 42u);
	TEST("[%.0u]", 0u);
	TEST("[%.5x]", 255);
	TEST("[%.0x]", 0);
	TEST("[%.5X]", 255);
	TEST("[%8.3d]", 7);
	TEST("[%8.3d]", -7);
	TEST("[%-8.3d]", 7);
	TEST("[%-8.3d]", -7);
	TEST("[%08.3d]", 7);
	TEST("[%08.3d]", -7);
	TEST("[%08.3x]", 255);
	TEST("[%.11d]", INT_MIN);
}

static void	test_precision_strings(void)
{
	SECTION("'.' precision on strings");
	TEST("[%.3s]", "hello");
	TEST("[%.0s]", "hello");
	TEST("[%.s]", "hello");
	TEST("[%.10s]", "hello");
	TEST("[%10.2s]", "hello");
	TEST("[%-10.2s]", "hello");
	TEST("[%.3s]", "");
}

static void	test_hash(void)
{
	SECTION("'#' flag");
	TEST("[%#x]", 255);
	TEST("[%#X]", 255);
	TEST("[%#x]", 0);
	TEST("[%#X]", 0);
	TEST("[%#10x]", 255);
	TEST("[%#-10x]", 255);
	TEST("[%#010x]", 255);
	TEST("[%#.5x]", 255);
	TEST("[%#10.5X]", 255);
	TEST("[%#x]", UINT_MAX);
}

static void	test_plus_space(void)
{
	SECTION("'+' and ' ' flags");
	TEST("[%+d]", 42);
	TEST("[%+d]", -42);
	TEST("[%+d]", 0);
	TEST("[%+i]", INT_MAX);
	TEST("[% d]", 42);
	TEST("[% d]", -42);
	TEST("[% d]", 0);
	TEST("[% i]", INT_MIN);
	TEST("[%+ d]", 42);
	TEST("[% +d]", 42);
	TEST("[%+5d]", 42);
	TEST("[%+-5d]", 42);
	TEST("[%+05d]", 42);
	TEST("[% 05d]", 42);
	TEST("[%+.3d]", 7);
	TEST("[% .3d]", 7);
	TEST("[%+8.3d]", -7);
	TEST("[%+.0d]", 0);
	TEST("[% .0d]", 0);
}

static void	test_combined(void)
{
	SECTION("Combinations");
	TEST("[%-10s|%5d|%-5c|%#x]", "abc", -12, 'z', 42);
	TEST("[%+d|% d|%05u|%.2s]", 1, 2, 3u, "xyz");
	TEST("[%-#12.6X]", 0xbeef);
	TEST("[%010.5d]", -123);
	TEST("[%-+10.5d]", 123);
}

int	main(void)
{
	test_width();
	test_minus();
	test_zero();
	test_precision_numbers();
	test_precision_strings();
	test_hash();
	test_plus_space();
	test_combined();
	return (summary());
}
