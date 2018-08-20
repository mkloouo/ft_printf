/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 16:03:40 by modnosum          #+#    #+#             */
/*   Updated: 2018/08/20 15:51:31 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <my_string.h>
#include <my_parse_printf.h>
#include <my_printf_info.h>
#include <my_form_arg.h>

int					ft_printf(const char *fmt, ...)
{
	va_list			args;
	t_info			info;
	const char		*save;

	if (!(save = fmt) || fmt == 0)
		return (ENULLFMT);
	va_start(args, fmt);
	init_info(&info);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			update_result(&info, save, (fmt - save));
			if (my_validate_arg(&save, &fmt, &info, &args))
				manage_arg(&args, &info);
		}
		else
			++fmt;
	}
	print_result(fmt, save, &info);
	va_end(args);
	return ((int)info.cur);
}
