/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 00:21:25 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/18 15:42:58 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	verifier(const char **str)
{
	int	sign;

	sign = 1;
	while (**str == '\t' || **str == '\n' || **str == '\f'
		|| **str == '\v' || **str == '\r' || **str == ' ')
		(*str)++;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	result = 0;
	sign = verifier(&str);
	while (*str >= '0' && *str <= '9')
	{
		if (result > (LONG_MAX - (*str - '0')) / 10)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return ((int)(result * sign));
}
