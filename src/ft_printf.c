/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 16:03:40 by modnosum          #+#    #+#             */
/*   Updated: 2018/07/24 21:00:30 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <ft_printf.h>
#include <my_string.h>
#include <my_parse_printf.h>
#include <my_printf_info.h>

static void			manage_letters(va_list *args, t_info *info)
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

static void			manage_unsigned(va_list *args, t_info *info)
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

static void			manage_signed(va_list *args, t_info *info)
{
	if (info->size_flag == CHAR_SIZE)
		info->data.ll = (signed char)va_arg(*args, int);
	else if (info->size_flag == SHORT_SIZE)
		info->data.ll = (signed short int)va_arg(*args, int);
	else if (info->size_flag == LONG_SIZE)
		info->data.ll = (signed long)va_arg(*args, long);
	else if (info->size_flag == LONG_LONG_SIZE)
		info->data.ll = va_arg(*args, long long);
	else if (info->size_flag == SIZE_T_SIZE)
		info->data.sst = va_arg(*args, size_t);
	else
		info->data.ll = va_arg(*args, int);
}

static void			manage_custom(va_list *args, t_info *info)
{
	(void)args;
	if (info->specifier == '%')
	{
		info->arg = malloc(sizeof(char) * 2);
		info->arg[info->arg_cur++] = '%';
		info->arg[info->arg_cur] = 0;
	}
}

static void			form_hexadecimal(t_info *info)
{
	(void)info;
}

static void			manage_pointer(va_list *args, t_info *info)
{
	info->data.p = va_arg(*args, void*);
	info->is_alt = 1;
	info->precision = -1;
	info->specifier = 'x';
	info->size_flag = LONG_LONG_SIZE;
	form_hexadecimal(info);
}

static void			manage_arg(va_list *args, t_info *info)
{
	if (info->specifier == 's' || info->specifier == 'c')
		manage_letters(args, info);
	else if (info->specifier == 'u' || info->specifier == 'o' ||
				info->specifier == 'x' || info->specifier == 'X')
		manage_unsigned(args, info);
	else if (info->specifier == 'd')
		manage_signed(args, info);
	else if (info->specifier == 'p')
		manage_pointer(args, info);
	else
		manage_custom(args, info);
	if (info->arg_cur > 0)
		update_result(info, info->arg, info->arg_cur);
	if (info->arg)
		free((void*)info->arg);
}

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
