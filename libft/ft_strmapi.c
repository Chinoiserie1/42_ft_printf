/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:22:49 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/16 15:57:18 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	unsigned int	counter;

	if (s == NULL || f == NULL)
		return (NULL);
	counter = 0;
	new_str = malloc(ft_strlen(s) + 1);
	if (new_str == NULL)
		return (NULL);
	while (s[counter] != '\0')
	{
		new_str[counter] = f(counter, s[counter]);
		counter++;
	}
	new_str[counter] = '\0';
	return (new_str);
}
