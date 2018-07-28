/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_form_arg2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 17:01:27 by modnosum          #+#    #+#             */
/*   Updated: 2018/07/28 17:41:19 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_form_arg.h>

void			manage_letters(va_list *args, t_info *info)
{
	if (info->specifier == 's')
	{
		if (info->size_flag == LONG_SIZE)
			info->data.ws = va_arg(*args, const wchar_t*);
		else
			info->data.s = va_arg(*args, const char*);
	}
	else
	{
		if (info->size_flag == LONG_SIZE)
			info->data.wc = va_arg(*args, wchar_t);
		else
			info->data.c = va_arg(*args, int);
	}
}
