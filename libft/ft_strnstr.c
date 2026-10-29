/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 00:02:37 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/18 11:33:39 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	counter;
	size_t	j;

	counter = 0;
	if (ft_strlen(needle) == 0)
		return ((char *) haystack);
	while (counter < len && *haystack != '\0')
	{
		j = 0;
		while (counter + j < len && haystack[j] == needle[j]
			&& haystack[j] != '\0' && needle[j] != '\0')
			j++;
		if (needle[j] == '\0')
			return ((char *) haystack);
		haystack++;
		counter++;
	}
	return (NULL);
}
