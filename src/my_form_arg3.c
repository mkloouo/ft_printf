/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_form_arg3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 17:04:20 by modnosum          #+#    #+#             */
/*   Updated: 2018/07/28 17:10:07 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_form_arg.h>

void			manage_unsigned(va_list *args, t_info *info)
{
	if (info->size_flag == CHAR_SIZE)
		info->data.ull = (unsigned char)va_arg(*args, unsigned int);
	else if (info->size_flag == SHORT_SIZE)
		info->data.ull = (unsigned short int)va_arg(*args, unsigned int);
	else if (info->size_flag == LONG_SIZE)
		info->data.ull = (unsigned long)va_arg(*args, unsigned long);
	else if (info->size_flag == LONG_LONG_SIZE)
		info->data.ull = va_arg(*args, unsigned long long);
	else if (info->size_flag == SIZE_T_SIZE)
		info->data.st = va_arg(*args, size_t);
	else
		info->data.ull = va_arg(*args, unsigned int);
}

void			manage_unsi(t_info *info)
{
	(void)info;
}

void			manage_octa(t_info *info)
{
	(void)info;
}

void			manage_hexa(t_info *info)
{
	(void)info;
}

void			manage_cap_hexa(t_info *info)
{
	(void)info;
}
