/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_printf_info1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 20:57:07 by modnosum          #+#    #+#             */
/*   Updated: 2018/07/28 20:41:42 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <my_string.h>

#include <my_printf_info.h>

void			print_result(const char *fmt, const char *p, t_info *info)
{
	update_result(info, p, (fmt - p));
	my_putnstr(info->result, info->cur);
	free((void*)info->result);
}

void			clear_info(t_info *info)
{
	if (!info->init)
	{
		info->cur = 0;
		info->size = 200;
		info->result = my_strnew(info->size, 0);
		info->init = 1;
	}
	info->width = 0;
	info->precision = 0;
	info->is_alt = 0;
	info->is_left_adj = 0;
	info->is_plus = 0;
	info->is_space = 0;
	info->is_zero_padd = 0;
	info->no_prec = 1;
	info->size_flag = NO_SIZE;
	info->specifier = 0;
	info->data.p = 0;
	info->arg = 0;
	info->arg_size = 0;
	info->arg_cur = 0;
}

void			init_info(t_info *info)
{
	info->init = 0;
	clear_info(info);
}

void			update_result(t_info *info, const char *str, size_t n)
{
	if (n > (info->size - info->cur))
	{
		info->result = my_resize_str(info->result, info->size,
									(info->size * 2) + n);
		info->size = (info->size * 2) + n;
	}
	my_strncpy((info->result + info->cur), str, n);
	info->cur += n;
}