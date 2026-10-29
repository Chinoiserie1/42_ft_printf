/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 15:05:50 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/29 14:38:15 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// handlers[i] prints the conversion convs[i]
t_handler	get_handler(char c)
{
	char					*found;
	static const t_handler	handlers[] = {print_char, print_str, print_ptr,
		print_int, print_int, print_uint, print_hex, print_hex, print_percent};

	if (c == 0)
		return (NULL);
	found = ft_strchr(CONVERSION, c);
	if (!found)
		return (NULL);
	return (handlers[found - CONVERSION]);
}
