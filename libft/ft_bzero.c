/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 15:00:10 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/09 15:12:52 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*res;
	size_t			counter;

	counter = 0;
	res = (unsigned char *) s;
	while (counter < n)
	{
		*res = (unsigned char)0;
		res++;
		counter++;
	}
}
