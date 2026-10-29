/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 20:38:11 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/18 11:26:10 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	counter;

	counter = 0;
	while (counter < n && s1[counter] != '\0')
	{
		if (s1[counter] != s2[counter])
			return ((unsigned char) s1[counter] - (unsigned char) s2[counter]);
		counter++;
	}
	if (counter < n && s1[counter] != s2[counter])
		return ((unsigned char) s1[counter] - (unsigned char) s2[counter]);
	return (0);
}
