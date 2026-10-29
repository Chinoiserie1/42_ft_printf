/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 14:40:31 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/09 15:31:49 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*res;
	size_t			counter;
	void			*start;

	res = (unsigned char *) b;
	start = b;
	counter = 0;
	while (counter < len)
	{
		*res = (unsigned char)c;
		res++;
		counter++;
	}
	return (start);
}
