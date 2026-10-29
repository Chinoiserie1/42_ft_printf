/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 15:16:18 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/28 14:49:55 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_spaces(int len)
{
	int	count;

	count = 0;
	while (count < len)
	{
		if (write(1, " ", 1) == -1)
			return (-1);
		count++;
	}
	return (count);
}

int	print_char(va_list *ap, t_struct *conv)
{
	char	c;
	int		pad;

	c = (char)va_arg(*ap, int);
	pad = 0;
	if (conv->width > 1)
		pad = conv->width - 1;
	if (conv->minus && write(1, &c, 1) == -1)
		return (-1);
	if (put_spaces(pad) == -1)
		return (-1);
	if (!conv->minus && write(1, &c, 1) == -1)
		return (-1);
	return (pad + 1);
}

int	print_str(va_list *ap, t_struct *conv)
{
	char	*arg;
	int		len;

	arg = va_arg(*ap, char *);
	if (!arg)
		arg = NULL_STR;
	len = ft_strlen(arg);
	if (conv->precision >= 0 && conv->precision < len)
		len = conv->precision;
	return (print_with_width(conv, ft_substr(arg, 0, len)));
}

int	print_percent(va_list *ap, t_struct *conv)
{
	(void)ap;
	return (print_with_width(conv, ft_strdup("%")));
}
