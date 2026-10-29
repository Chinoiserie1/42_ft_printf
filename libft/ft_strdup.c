/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:10:51 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/13 12:23:43 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	counter;
	size_t	size;

	counter = 0;
	size = ft_strlen(s1);
	dup = malloc(size + 1);
	if (dup == NULL)
		return (NULL);
	while (counter < size + 1)
	{
		dup[counter] = s1[counter];
		counter++;
	}
	return (dup);
}
