/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 18:50:52 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/18 11:33:21 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	counter;

	dst_len = 0;
	while (dst_len < dstsize && dst[dst_len])
		dst_len++;
	counter = 0;
	if (dst_len >= dstsize)
		return (dstsize + ft_strlen(src));
	while (src[counter] != '\0' && counter < dstsize - dst_len - 1)
	{
		dst[dst_len + counter] = src[counter];
		counter++;
	}
	dst[dst_len + counter] = '\0';
	return (dst_len + ft_strlen(src));
}
