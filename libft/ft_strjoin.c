/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:38:43 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/16 15:57:12 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_size;
	size_t	counter;
	char	*new_str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	counter = 0;
	total_size = ft_strlen(s1) + ft_strlen(s2);
	new_str = malloc(total_size + 1);
	if (new_str == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		new_str[counter] = *s1;
		counter++;
		s1++;
	}
	while (*s2 != '\0')
	{
		new_str[counter] = *s2;
		counter++;
		s2++;
	}
	new_str[counter] = '\0';
	return (new_str);
}
