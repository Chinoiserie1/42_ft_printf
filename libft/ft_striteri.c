/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:30:32 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/16 15:57:07 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	counter;

	if (s == NULL || f == NULL)
		return ;
	counter = 0;
	while (*s != '\0')
	{
		f(counter, s);
		s++;
		counter++;
	}
}
