/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 14:17:56 by modnosum          #+#    #+#             */
/*   Updated: 2018/07/21 20:35:25 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INC_FT_PRINTF_H
# define INC_FT_PRINTF_H

# include <wchar.h>
# include <stdarg.h>
# include <sys/types.h>
# include <inttypes.h>
# include <unistd.h>
#include <stdlib.h>

# define ENULLFMT (-1)
# define EINVFMT (-2)

# define NO_PRECISION (-1)

/*
** structures needed for printf
*/
typedef union			u_data {
	char				c;
	long long			ll;
	wchar_t				wc;
	unsigned long long	ull;
	size_t				st;
	ssize_t				sst;
	const char			*s;
	const wchar_t		*ws;
	void				*p;
}						t_data;

typedef enum			e_size_f
{
	NO_SIZE,
	CHAR_SIZE,
	SHORT_SIZE,
	LONG_SIZE,
	LONG_LONG_SIZE,
	SIZE_T_SIZE
}						t_size_f;

typedef struct			s_info {
	int					width;
	int					precision;

	unsigned int		is_alt:1;
	unsigned int		is_zero_padd:1;
	unsigned int		is_left_adj:1;
	unsigned int		is_space:1;
	unsigned int		is_plus:1;

	t_size_f			size_flag;
	char				specifier;

	t_data				data;
	char				*result;
	size_t				size;
	size_t				cur;

	char				*arg;
	size_t				arg_cur;
	size_t				arg_size;
	int					init;
}						t_info;

int						ft_printf(const char *fmt, ...);

#endif
