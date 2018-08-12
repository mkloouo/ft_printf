/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_form_arg6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 18:05:02 by modnosum          #+#    #+#             */
/*   Updated: 2018/08/12 21:31:25 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_form_arg.h>
#include <ft_printf.h>

void			form_wide_string(t_info *info)
{
	info->arg_size = my_wstrclen(info->data.ws);
	if (info->is_prec && info->precision < info->arg_size)
		info->arg_size = info->precision;
	if (info->width > info->arg_size)
		info->arg_size = info->width;
	// info->arg = my_strnew(info->arg_size, ' ');x
	ft_printf("arg size: %zu\n", info->arg_size);
} 
