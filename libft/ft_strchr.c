/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 20:54:42 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/15 17:53:33 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if ((unsigned char) *s == (unsigned char) c)
			return ((char *) s);
		s++;
	}
	if ((unsigned char) *s == (unsigned char) c)
		return ((char *) s);
	return (NULL);
}
