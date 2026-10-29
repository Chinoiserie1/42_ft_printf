/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_n_store.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 12:27:28 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/23 14:57:50 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_n_store_flag_digit(t_struct *conversion, const char *str)
{
	int		amount_char;
	int		nbr;
	char	*substr;

	amount_char = 0;
	while (ft_isdigit(str[amount_char]))
		amount_char++;
	if (amount_char == 0)
		return (0);
	substr = ft_substr(str, 0, amount_char);
	nbr = ft_atoi(substr);
	free(substr);
	conversion->width = nbr;
	return (amount_char);
}

// return 0 if no flags and 1 if flags is present
int	check_n_store_flags(t_struct *conversion, char c)
{
	if (c == '-')
		return (conversion->minus = 1, 1);
	if (c == '0')
		return (conversion->zero = 1, 1);
	if (c == '#')
		return (conversion->hash = 1, 1);
	if (c == ' ')
		return (conversion->space = 1, 1);
	if (c == '+')
		return (conversion->plus = 1, 1);
	return (0);
}

// check and store the precision and return the amount of character for 
// the precision so we can move the ptr after it
// [NOTE] maybe i can also just increment the ptr in this fn need to check!
int	check_n_store_precision(t_struct *conversion, const char *str)
{
	int		amount_char;
	int		nbr;

	amount_char = 0;
	if (*str != '.')
		return (0);
	conversion->precision = 0;
	str++;
	while (ft_isdigit(str[amount_char]))
		amount_char++;
	if (amount_char == 0)
		return (1);
	nbr = ft_atoi(str);
	conversion->precision = nbr;
	return (amount_char + 1);
}

int	check_n_store_length(t_struct *conversion, const char *str)
{
	if (str[0] == 'h' && str[1] == 'h')
		return (conversion->length = LEN_HH, 2);
	if (str[0] == 'l' && str[1] == 'l')
		return (conversion->length = LEN_LL, 2);
	if (str[0] == 'h')
		return (conversion->length = LEN_H, 1);
	if (str[0] == 'l')
		return (conversion->length = LEN_L, 1);
	if (str[0] == 'z')
		return (conversion->length = LEN_Z, 1);
	if (str[0] == 'j')
		return (conversion->length = LEN_J, 1);
	if (str[0] == 't')
		return (conversion->length = LEN_T, 1);
	return (0);
}

int	check_n_store_conversion(t_struct *conversion, char c)
{
	if (c == 'c')
		return (conversion->conversion = 'c', 1);
	if (c == 's')
		return (conversion->conversion = 's', 1);
	if (c == 'p')
		return (conversion->conversion = 'p', 1);
	if (c == 'd')
		return (conversion->conversion = 'd', 1);
	if (c == 'i')
		return (conversion->conversion = 'i', 1);
	if (c == 'u')
		return (conversion->conversion = 'u', 1);
	if (c == 'x')
		return (conversion->conversion = 'x', 1);
	if (c == 'X')
		return (conversion->conversion = 'X', 1);
	if (c == '%')
		return (conversion->conversion = '%', 1);
	return (0);
}
