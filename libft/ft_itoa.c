/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 18:56:40 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/13 20:25:01 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_char(long long n)
{
	size_t		counter;

	counter = 1;
	while (n >= 10)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char		*res;
	size_t		counter;
	int			is_neg;
	long long	nb;

	nb = n;
	is_neg = (nb < 0);
	if (is_neg == 1)
		nb = nb * -1;
	counter = count_char(nb) + is_neg;
	res = malloc(counter + 1);
	if (res == NULL)
		return (NULL);
	res[counter] = '\0';
	while (counter > (size_t) is_neg)
	{
		res[counter - 1] = (nb % 10) + '0';
		nb = nb / 10;
		counter--;
	}
	if (is_neg == 1)
		res[0] = '-';
	return (res);
}
