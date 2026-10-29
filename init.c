/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 16:16:47 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/22 16:19:55 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_conversion_struct(t_struct *conversion)
{
	conversion->conversion = 0;
	conversion->hash = 0;
	conversion->length = 0;
	conversion->minus = 0;
	conversion->plus = 0;
	conversion->precision = -1;
	conversion->space = 0;
	conversion->width = 0;
	conversion->zero = 0;
}
