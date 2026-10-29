/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 11:20:31 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/29 14:29:12 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*get_sign(long nbr, t_struct *conv)
{
	if (nbr < 0)
		return ("-");
	if (conv->plus)
		return ("+");
	if (conv->space)
		return (" ");
	return ("");
}

int	print_int(va_list *ap, t_struct *conv)
{
	long			nbr;
	unsigned long	abs_value;
	char			*digits;
	char			*number;

	nbr = va_arg(*ap, int);
	abs_value = nbr;
	if (nbr < 0)
		abs_value = -nbr;
	digits = get_digits(abs_value, DECIMAL, conv);
	number = build_number(conv, digits, get_sign(nbr, conv));
	return (print_with_width(conv, number));
}

int	print_uint(va_list *ap, t_struct *conv)
{
	unsigned int	nbr;
	char			*digits;
	char			*number;

	nbr = va_arg(*ap, unsigned int);
	digits = get_digits(nbr, DECIMAL, conv);
	number = build_number(conv, digits, "");
	return (print_with_width(conv, number));
}

int	print_hex(va_list *ap, t_struct *conv)
{
	unsigned int	nbr;
	char			*base;
	char			*prefix;
	char			*number;

	nbr = va_arg(*ap, unsigned int);
	base = HEX_LOWER;
	prefix = "";
	if (conv->conversion == 'X')
		base = HEX_UPPER;
	if (conv->hash && nbr != 0 && conv->conversion == 'X')
		prefix = "0X";
	else if (conv->hash && nbr != 0)
		prefix = "0x";
	number = build_number(conv, get_digits(nbr, base, conv), prefix);
	return (print_with_width(conv, number));
}

int	print_ptr(va_list *ap, t_struct *conv)
{
	unsigned long	addr;
	char			*number;

	addr = (unsigned long)va_arg(*ap, void *);
	if (addr == 0)
		return (print_with_width(conv, ft_strdup(NULL_PTR)));
	number = build_number(conv, ft_utoa_base(addr, HEX_LOWER), "0x");
	return (print_with_width(conv, number));
}
