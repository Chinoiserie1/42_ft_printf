/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 10:10:51 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/13 12:10:05 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t			counter;
	size_t			total_mem;
	unsigned char	*ptr;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	total_mem = count * size;
	counter = 0;
	if (total_mem == 0)
		ptr = malloc(1);
	else
		ptr = malloc(total_mem);
	if (ptr == NULL)
		return (NULL);
	while (counter < total_mem)
	{
		ptr[counter] = (unsigned char) 0;
		counter++;
	}
	return ((void *) ptr);
}
