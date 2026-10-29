/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 15:34:08 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/18 15:43:11 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*res;
	unsigned char	*ptr_src;
	void			*start;
	size_t			counter;

	if (dst == src)
		return (dst);
	start = dst;
	res = (unsigned char *) dst;
	ptr_src = (unsigned char *) src;
	counter = 0;
	while (counter < n)
	{
		*res = *ptr_src;
		res++;
		ptr_src++;
		counter++;
	}
	return (start);
}
