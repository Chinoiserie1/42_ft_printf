/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 11:52:24 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/11 18:40:45 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			counter;

	str = (unsigned char *)s;
	counter = 0;
	while (counter < n)
	{
		if (*str == (unsigned char) c)
			return (str);
		str++;
		counter++;
	}
	return (NULL);
}
