/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 12:01:17 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/29 14:29:31 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_digits(unsigned long nbr, unsigned long base_len)
{
	int	len;

	len = 1;
	while (nbr >= base_len)
	{
		nbr = nbr / base_len;
		len++;
	}
	return (len);
}

char	*ft_utoa_base(unsigned long nbr, char *base)
{
	unsigned long	base_len;
	int				len;
	char			*str;

	base_len = ft_strlen(base);
	len = count_digits(nbr, base_len);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		len--;
		str[len] = base[nbr % base_len];
		nbr = nbr / base_len;
	}
	return (str);
}

char	*get_digits(unsigned long nbr, char *base, t_struct *conv)
{
	if (nbr == 0 && conv->precision == 0)
		return (ft_strdup(""));
	return (ft_utoa_base(nbr, base));
}

char	*build_number(t_struct *conv, char *digits, char *prefix)
{
	char	*number;
	char	*tmp;

	if (!digits)
		return (NULL);
	number = pad_left(digits, '0', conv->precision);
	free(digits);
	if (number && conv->zero && !conv->minus && conv->precision < 0)
	{
		tmp = pad_left(number, '0', conv->width - (int)ft_strlen(prefix));
		free(number);
		number = tmp;
	}
	if (!number)
		return (NULL);
	tmp = ft_strjoin(prefix, number);
	free(number);
	return (tmp);
}
