#ifndef TESTER_H
# define TESTER_H

/*
** Small harness: runs printf and ft_printf with the same arguments,
** captures what each one writes to stdout, then compares output and
** return value.
*/

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include "../ft_printf.h"

# define CAP_SIZE 4096
# define GREEN "\033[32m"
# define RED "\033[31m"
# define BOLD "\033[1m"
# define RESET "\033[0m"

static int	g_ok = 0;
static int	g_ko = 0;
static int	g_saved_fd = -1;
static FILE	*g_tmp = NULL;

static void	start_capture(void)
{
	fflush(stdout);
	g_tmp = tmpfile();
	if (!g_tmp)
	{
		perror("tmpfile");
		_exit(1);
	}
	g_saved_fd = dup(STDOUT_FILENO);
	dup2(fileno(g_tmp), STDOUT_FILENO);
}

/* Returns the number of bytes captured (output may contain '\0'). */
static int	end_capture(char *buf)
{
	int	len;

	fflush(stdout);
	dup2(g_saved_fd, STDOUT_FILENO);
	close(g_saved_fd);
	lseek(fileno(g_tmp), 0, SEEK_SET);
	len = (int)read(fileno(g_tmp), buf, CAP_SIZE - 1);
	if (len < 0)
		len = 0;
	buf[len] = '\0';
	fclose(g_tmp);
	return (len);
}

static void	print_visible(const char *s, int len)
{
	int	i;

	putchar('"');
	for (i = 0; i < len; i++)
	{
		if (s[i] == '\0')
			fputs("\\0", stdout);
		else if (s[i] == '\n')
			fputs("\\n", stdout);
		else
			putchar(s[i]);
	}
	putchar('"');
}

static void	report(const char *call, int line, const char *exp, int exp_len,
		int exp_ret, const char *got, int got_len, int got_ret)
{
	int	same;

	same = (exp_ret == got_ret && exp_len == got_len
			&& memcmp(exp, got, exp_len) == 0);
	if (same)
	{
		g_ok++;
		printf(GREEN "[OK]" RESET " l.%-4d %s\n", line, call);
		return ;
	}
	g_ko++;
	printf(RED "[KO]" RESET " l.%-4d %s\n", line, call);
	printf("       expected: ");
	print_visible(exp, exp_len);
	printf(" (ret %d)\n       got:      ", exp_ret);
	print_visible(got, got_len);
	printf(" (ret %d)\n", got_ret);
}

# define TEST(...) do { \
	char	exp_[CAP_SIZE]; \
	char	got_[CAP_SIZE]; \
	int		exp_ret_; \
	int		got_ret_; \
	int		exp_len_; \
	int		got_len_; \
	start_capture(); \
	exp_ret_ = printf(__VA_ARGS__); \
	exp_len_ = end_capture(exp_); \
	start_capture(); \
	got_ret_ = ft_printf(__VA_ARGS__); \
	got_len_ = end_capture(got_); \
	report(#__VA_ARGS__, __LINE__, exp_, exp_len_, exp_ret_, \
		got_, got_len_, got_ret_); \
} while (0)

# define SECTION(name) printf("\n" BOLD "=== %s ===" RESET "\n", name)

static int	summary(void)
{
	printf("\n" BOLD "Result: " GREEN "%d OK" RESET BOLD " / "
		"%s%d KO" RESET "\n", g_ok, g_ko ? RED : GREEN, g_ko);
	return (g_ko != 0);
}

#endif
