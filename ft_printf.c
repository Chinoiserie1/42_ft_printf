/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 20:23:58 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/27 12:00:00 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	parse_conversion(t_struct *conversion, const char **str)
{
	if (**str != '%')
		return (-1);
	(*str)++;
	while (check_n_store_flags(conversion, **str))
		(*str)++;
	*str = *str + check_n_store_flag_digit(conversion, *str);
	*str = *str + check_n_store_precision(conversion, *str);
	*str = *str + check_n_store_length(conversion, *str);
	*str = *str + check_n_store_conversion(conversion, **str);
	return (0);
}

static int	print_conversion(va_list *ap, t_struct *conversion)
{
	t_handler	handler;

	if (conversion->conversion == 0)
		return (-1);
	handler = get_handler(conversion->conversion);
	if (handler == NULL)
		return (-1);
	return (handler(ap, conversion));
}

// return the number of chars written, or -1 on error
static int	read_n_print(va_list *ap, const char *str)
{
	int			write_count;
	int			result;
	t_struct	conversion;

	write_count = 0;
	while (*str != '\0')
	{
		if (*str != '%')
		{
			result = write(1, str, 1);
			str++;
		}
		else
		{
			init_conversion_struct(&conversion);
			parse_conversion(&conversion, &str);
			result = print_conversion(ap, &conversion);
		}
		if (result == -1)
			return (-1);
		write_count += result;
	}
	return (write_count);
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	int			write_count;

	if (!str)
		return (-1);
	va_start(ap, str);
	write_count = read_n_print(&ap, str);
	va_end(ap);
	return (write_count);
}
