/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 20:22:24 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/27 12:00:00 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

# define LEN_NONE 0
# define LEN_HH   1
# define LEN_H    2
# define LEN_L    3
# define LEN_LL   4
# define LEN_Z    5
# define LEN_J    6
# define LEN_T    7

# define DECIMAL "0123456789"
# define HEX_LOWER "0123456789abcdef"
# define HEX_UPPER "0123456789ABCDEF"
# define NULL_STR "(null)"

# ifdef __linux__
#  define NULL_PTR "(nil)"
# else
#  define NULL_PTR "0x0"
# endif

typedef struct s_struct
{
	int	minus;
	int	zero;
	int	hash;
	int	space;
	int	plus;
	int	width;
	int	precision;
	int	length;
	int	conversion;
}	t_struct;

typedef int	(*t_handler)(va_list *ap, t_struct *conv);

int			ft_printf(const char *str, ...);

int			ft_putstr(char *str);
void		init_conversion_struct(t_struct *conversion);

t_handler	get_handler(char c);

// check and store
int			check_n_store_flag_digit(t_struct *conversion, const char *str);
int			check_n_store_flags(t_struct *conversion, char c);
int			check_n_store_precision(t_struct *conversion, const char *str);
int			check_n_store_length(t_struct *conversion, const char *str);
int			check_n_store_conversion(t_struct *conversion, char c);

// flags (add_flags.c)
char		*pad_left(char *str, char c, int total_len);
char		*add_basic_flags(t_struct *conv, char *str);
int			print_with_width(t_struct *conv, char *str);

// numbers (number_utils.c)
char		*ft_utoa_base(unsigned long nbr, char *base);
char		*get_digits(unsigned long nbr, char *base, t_struct *conv);
char		*build_number(t_struct *conv, char *digits, char *prefix);

// printer
int			print_char(va_list *ap, t_struct *conv);
int			print_str(va_list *ap, t_struct *conv);
int			print_ptr(va_list *ap, t_struct *conv);
int			print_int(va_list *ap, t_struct *conv);
int			print_uint(va_list *ap, t_struct *conv);
int			print_hex(va_list *ap, t_struct *conv);
int			print_percent(va_list *ap, t_struct *conv);

#endif
