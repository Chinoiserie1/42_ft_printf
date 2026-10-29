/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 16:06:59 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/28 18:10:59 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*create_same_char(char c, int len)
{
	int		counter;
	char	*new_str;

	if (len <= 0)
		return (NULL);
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	counter = 0;
	while (counter < len)
	{
		new_str[counter] = c;
		counter++;
	}
	new_str[counter] = '\0';
	return (new_str);
}

// return a new string: str with c added on the left until total_len
char	*pad_left(char *str, char c, int total_len)
{
	int		pad;
	char	*padding;
	char	*new_str;

	pad = total_len - (int)ft_strlen(str);
	if (pad <= 0)
		return (ft_strdup(str));
	padding = create_same_char(c, pad);
	if (!padding)
		return (NULL);
	new_str = ft_strjoin(padding, str);
	free(padding);
	return (new_str);
}

char	*add_basic_flags(t_struct *conv, char *str)
{
	int		pad;
	char	*padding;
	char	*new_str;

	if (!conv->minus)
		return (pad_left(str, ' ', conv->width));
	pad = conv->width - (int)ft_strlen(str);
	if (pad <= 0)
		return (ft_strdup(str));
	padding = create_same_char(' ', pad);
	if (!padding)
		return (NULL);
	new_str = ft_strjoin(str, padding);
	free(padding);
	return (new_str);
}

// add the width, print, and free str
int	print_with_width(t_struct *conv, char *str)
{
	char	*result;
	int		count;

	if (!str)
		return (-1);
	result = add_basic_flags(conv, str);
	free(str);
	if (!result)
		return (-1);
	count = ft_putstr(result);
	free(result);
	return (count);
}
