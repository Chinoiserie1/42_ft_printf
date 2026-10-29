/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 16:50:18 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/18 11:35:10 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*res;
	void			*start;
	unsigned char	*ptr_src;

	if (len == 0 || dst == src)
		return (dst);
	start = dst;
	res = (unsigned char *) dst + len - 1;
	ptr_src = (unsigned char *) src + len - 1;
	if (dst < src)
		return (ft_memcpy(dst, src, len));
	while (len > 0)
	{
		*res = *ptr_src;
		res--;
		ptr_src--;
		len--;
	}
	return (start);
}
