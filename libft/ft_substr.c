/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:24:54 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/16 15:57:26 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dup;
	size_t	counter;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	counter = 0;
	if (start > s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	dup = malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	while (counter < len)
	{
		dup[counter] = s[start + counter];
		counter++;
	}
	dup[counter] = '\0';
	return (dup);
}
