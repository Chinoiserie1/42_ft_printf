/*
** Mandatory part: %c %s %p %d %i %u %x %X %%
** Build: see tests/README or run
**   make && cc -Wall -Wextra -Wno-format tests/main.c -L. -lftprintf -o test_mandatory
*/

#include "tester.h"

static void	test_basic(void)
{
	SECTION("Plain text");
	TEST("");
	TEST("Hello world");
	TEST("Hello\nworld\n");
	TEST("%%");
	TEST("100%% sure %%%%");
}

static void	test_char(void)
{
	SECTION("%c");
	TEST("%c", 'a');
	TEST("%c%c%c", 'a', 'b', 'c');
	TEST("[%c]", ' ');
	TEST("[%c]", '\n');
	TEST("[%c]", 0);
	TEST("%c", 127);
	TEST("start %c end", '4');
}

static void	test_string(void)
{
	char	*null_str;

	null_str = NULL;
	SECTION("%s");
	TEST("%s", "hello");
	TEST("[%s]", "");
	TEST("%s %s", "hello", "world");
	TEST("%s", "a very long string to check that nothing is cut in the middle");
	TEST("%s", null_str);
	TEST("[%s][%s]", "", null_str);
}

static void	test_pointer(void)
{
	int		x;
	void	*null_ptr;

	x = 42;
	null_ptr = NULL;
	SECTION("%p");
	TEST("%p", &x);
	TEST("%p", (void *)1);
	TEST("%p", (void *)0xdeadbeef);
	TEST("%p", (void *)LONG_MAX);
	TEST("%p", (void *)ULONG_MAX);
	TEST("%p", null_ptr);
	TEST("%p %p", &x, null_ptr);
}

static void	test_int(void)
{
	SECTION("%d / %i");
	TEST("%d", 0);
	TEST("%d", 42);
	TEST("%d", -42);
	TEST("%d", 7);
	TEST("%d", -7);
	TEST("%d", INT_MAX);
	TEST("%d", INT_MIN);
	TEST("%i", 0);
	TEST("%i", 123456);
	TEST("%i", -123456);
	TEST("%i", INT_MAX);
	TEST("%i", INT_MIN);
	TEST("%d %i %d", 1, -2, 3);
}

static void	test_unsigned(void)
{
	SECTION("%u");
	TEST("%u", 0);
	TEST("%u", 42);
	TEST("%u", UINT_MAX);
	TEST("%u", -1);
	TEST("%u", INT_MIN);
	TEST("%u", INT_MAX);
}

static void	test_hex(void)
{
	SECTION("%x / %X");
	TEST("%x", 0);
	TEST("%x", 255);
	TEST("%x", 0xabcdef);
	TEST("%x", UINT_MAX);
	TEST("%x", -1);
	TEST("%x", INT_MIN);
	TEST("%X", 0);
	TEST("%X", 255);
	TEST("%X", 0xabcdef);
	TEST("%X", UINT_MAX);
	TEST("%X", -42);
	TEST("%x %X", 3054, 3054);
}

static void	test_mixed(void)
{
	int	x;

	x = 0;
	SECTION("Mixed");
	TEST("%c|%s|%p|%d|%i|%u|%x|%X|%%", 'Z', "str", &x, -1, 2, 3u, 255, 255);
	TEST("Name: %s, age: %d, grade: %c", "Bob", 21, 'A');
	TEST("%d%d%d%d%d", 1, 2, 3, 4, 5);
	TEST("%s%s%s", "a", "", "c");
}

int	main(void)
{
	test_basic();
	test_char();
	test_string();
	test_pointer();
	test_int();
	test_unsigned();
	test_hex();
	test_mixed();
	return (summary());
}
