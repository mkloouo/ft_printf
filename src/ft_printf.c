/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 16:03:40 by modnosum          #+#    #+#             */
/*   Updated: 2018/07/21 22:19:49 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

/*
** Allocate string of @new_size, copy all of @src size of @size.
** Return new string.
*/
static char			*resize(const char *src, size_t size, size_t new_size)
{
	size_t			i;
	char			*dst;

	dst = malloc(sizeof(char) * (new_size + 1));
	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		++i;
	}
	while (i <= new_size)
		dst[i++] = 0;
	free((void*)src);
	return (dst);
}

/*
** Copy contents of src to dst size of @size.
*/
static void			copynstr(char *dst, const char *src, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		++i;
	}
}

/*
** Fills the @str length of @len with char @ch.
*/
static void			strfill(char *str, size_t len, char ch)
{
	size_t			i;

	i = 0;
	while (i < len)
		str[i++] = ch;
}

/*
** Grow result (twice) to fit new data, update cursor (and size if needed).
*/
static void			grow_result(t_info *info, const char *s, size_t n)
{
	if (n > (info->size - info->cur))
		resize(info->result, info->size, info->size * 2);
	copynstr((info->result + info->cur), s, n);
	info->cur += n;
}

/*
** Print string size of @n.
*/
static void			printnstr(char *str, size_t n)
{
	write(STDOUT_FILENO, str, n);
}

/*
** Get @str length.
*/
static size_t		strlength(char const *str)
{
	size_t			len;

	len = 0;
	while (str[len])
		++len;
	return (len);
}

/*
** Print result, free result string.
*/
static void			end_result(const char *fmt, const char *p, t_info *info)
{
	grow_result(info, p, (fmt - p));
	printnstr(info->result, info->cur);
	free((void*)info->result);
}

/*
** Create string @str of size @size.
*/
static void			create_str(char **s, size_t size)
{
	size_t			i;

	*s = malloc(sizeof(char) * size);
	i = 0;
	while (i < size)
		(*s)[i++] = 0;
}

/*
** Clear all the info fields and initialize result, when run for the first time.
*/
static void			clear_info(t_info *info)
{
	if (!info->init)
	{
		info->cur = 0;
		create_str(&info->result, (info->size = 200));
		info->init = 1;
	}
	info->width = 0;
	info->precision = NO_PRECISION;
	info->is_alt = 0;
	info->is_left_adj = 0;
	info->is_plus = 0;
	info->is_space = 0;
	info->is_zero_padd = 0;
	info->size_flag = NO_SIZE;
	info->specifier = 0;
	info->data.p = 0;
	info->arg = 0;
	info->arg_size = 0;
	info->arg_cur = 0;
}

/*
** Gets number going through the string.
*/
static int			get_number(char const **fmt)
{
	int				sign;
	int				number;

	number = 0;
	sign = 1;
	if (**fmt == '-' && (++*fmt))
		sign = -1;
	while (**fmt >= '0' && **fmt <= '9')
	{
		number = number * 10 + (**fmt - '0');
		++*fmt;
	}
	return (number * sign);
}

/*
** Gets formatting flags.
*/
static void			get_flags(char const **fmt, t_info *info)
{
	while (**fmt == '#' || **fmt == '0' || **fmt == '-' ||
			**fmt == ' ' || **fmt == '+')
	{
		if (**fmt == '#')
			info->is_alt = 1;
		else if (**fmt == '0')
			info->is_zero_padd = 1;
		else if (**fmt == '-')
			info->is_left_adj = 1;
		else if (**fmt == ' ')
			info->is_space = 1;
		else
			info->is_plus = 1;
		++*fmt;
	}
}

/*
** Stores number or the placeholder to the @number.
*/
static void			get_num_or_pholder(char const **fmt, int *number,
					va_list *args)
{
	if (**fmt == '*')
		*number = va_arg(*args, int);
	else
		*number = get_number(fmt);
}

/*
** Find @needle occurence and returns pointer to the position.
*/
static char const	*getchinstr(char const *haystack, char needle)
{
	while (*haystack)
	{
		if (*haystack == needle)
			return (haystack);
		++haystack;
	}
	return (0);
}

/*
** Manages size priority and moves @fmt more if needed.
*/
static void			manage_size_flag(char const **fmt, t_info *info,
					t_size_f new_size)
{
	if (new_size == SHORT_SIZE || new_size == LONG_LONG_SIZE)
		++*fmt;
	if (new_size > info->size)
		info->size = new_size;
}

/*
** Gets size flag.
*/
static void			get_size_flags(char const **fmt, t_info *info)
{
	char const		*f;
	char const		*flags;

	flags = "zjhl";
	while ((f = getchinstr(flags, **fmt)))
	{
		if (*f == 'h')
			manage_size_flag(fmt, info, (*(f + 1) == 'h' ? SHORT_SIZE
														: CHAR_SIZE));
		else if (*f == 'l')
			manage_size_flag(fmt, info, (*(f + 1) == 'l' ? LONG_LONG_SIZE
														: LONG_SIZE));
		else if (*f == 'j')
			manage_size_flag(fmt, info, LONG_LONG_SIZE);
		else
			manage_size_flag(fmt, info, SIZE_T_SIZE);
		++*fmt;
	}
}

/*
** Gets specifier.
*/
static int			get_spec(char const **fmt, t_info *info)
{
	char			test;

	test = (**fmt >= 'A' && **fmt <= 'Z') ? (**fmt + ('a' - 'A'))
										: (**fmt);
	if (!(test == 's' || test == 'c' || test == 'u' || test == 'o' ||
		test == 'x' || test == 'i' || test == 'd' || test == 'p' ||
		test == '%'))
		return (0);
	if (**fmt == 'S' || **fmt == 'C' || **fmt == 'U' || **fmt == 'O' ||
		**fmt == 'D')
		info->size_flag = LONG_SIZE;
	else if (**fmt == 'X')
		test = 'X';
	if (test == 'i')
		test = 'd';
	info->specifier = test;
	++*fmt;
	return (1);
}

/*
** Parse fmt and write all the flags and stuff to info.
** In case something goes wrong <- invalidate (return 0).
*/
static int			validate_arg(char const **fmt, t_info *info, va_list *args)
{
	get_flags(fmt, info);
	get_num_or_pholder(fmt, &info->width, args);
	if (**fmt == '.' && ++*fmt)
		get_num_or_pholder(fmt, &info->precision, args);
	get_size_flags(fmt, info);
	return (get_spec(fmt, info));
}

/*
** Count size of string needed to fill in number in char form.
*/
static int			signedstrlen(long long number, int precision)
{
	int				size;

	if (number == 0)
		return (precision > 0 ? precision : 0);
	size = (number < 0) ? 1 : 0;
	while (number)
	{
		number /= 10;
		++size;
	}
	return ((size < precision) ? precision : size);
}

/*
** Count size of string needed to fill in unsigned number in char form.
*/
static int			unsignedstrlen(unsigned long long number, int base,
					int precision)
{
	int				size;

	size = 0;
	if (number == 0)
		return ((precision > 0) ? precision : 0);
	while (number)
	{
		number /= base;
		++size;
	}
	return ((size < precision) ? precision : size);
}

/*
** Gets string of @number.
*/
static char			*signedtochar(long long number, int precision)
{
	int				digit;
	char			*s;
	size_t			len;

	len = (size_t)signedstrlen(number, precision);
	s = malloc(sizeof(char) * (len + 1));
	if (number < 0)
		s[0] = '-';
	s[len--] = 0;
	while (number)
	{
		digit = number % 10;
		digit = (digit < 0) ? (digit * -1) : (digit);
		s[len] = digit + '0';
		if (len != 0)
			--len;
		number /= 10;
	}
	while (len)
	{
		s[len--] = '0';
		if (len == 0)
			s[len] = '0';
	}
	return (s);
}

/*
** Gets string of unsigned @number using @tag.
*/
static char			*unsignedtochar(unsigned long long number, char const *tab,
					int precision)
{
	int				base;
	int				digit;
	char			*s;
	size_t			len;

	base = (int)strlength(tab);
	len = (size_t)unsignedstrlen(number, base, precision);
	s = malloc(sizeof(char) * (len + 1));
	s[len--] = 0;
	while (number)
	{
		digit = number % base;
		s[len] = tab[digit];
		if (len != 0)
			--len;
		number /= base;
	}
	while (len)
	{
		s[len--] = '0';
		if (len == 0)
			s[len] = '0';
	}
	return (s);
}

/*
** Manage letter(s).
*/
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

/*
** Creates a string of 16/8/10 base number, based on specifier.
*/
static char			*convunsigtostr(t_info *info)
{
	char const		*tab;
	char			*conv;

	if (info->specifier == 'u')
		tab = "0123456789";
	else if (info->specifier == 'X')
		tab = "0123456789ABCDEF";
	else if (info->specifier == 'x')
		tab = "0123456789abcdef";
	else
		tab = "01234567";
	conv = unsignedtochar(info->data.ull, tab, info->precision);
	return (conv);
}

/*
** Calculates proper size.
*/
static void			unsigned_arg_size(t_info *info, int conv_len)
{
	if (info->is_alt && (info->specifier == 'o' ||
		info->specifier == 'x' || info->specifier == 'X'))
		info->arg_size = (info->specifier == 'o' ? 1 : 2);
	if (info->width > conv_len)
	{
		if ((size_t)(info->width - conv_len) >= info->arg_size)
			info->arg_size = info->width;
		else
			info->arg_size += info->width;
	}
	else
		info->arg_size += conv_len;
}

/*
** Correctly fill with numbers handling '#' and '-' flags.
*/
static void			unsigned_fill_arg(t_info *info, char *conv, int conv_len)
{
	int				move;

	move = 0;
	if (!(info->is_left_adj))
		move += (info->arg_size - conv_len);
	if (info->is_alt && (info->specifier == 'o' || info->specifier == 'x' ||
							info->specifier == 'X'))
	{
		if (move > 0)
			info->arg[move - 2] = '0';
		else
			info->arg[move++] = '0';
		if (!(info->specifier == 'o'))
		{
			if (move > 1)
				info->arg[move - 1] = info->specifier;
			else
				info->arg[move++] = info->specifier;
		}
	}
	copynstr((info->arg + move), conv, conv_len);
}

/*
** Manage unsigned numbers.
*/
static void			mmanage_unsigned(t_info *info)
{
	size_t			conv_len;
	char			*conv;

	conv = convunsigtostr(info);
	conv_len = strlength(conv);
	unsigned_arg_size(info, conv_len);
	create_str(&info->arg, info->arg_size);
	strfill(info->arg, info->arg_size, (info->precision == -1
								&& info->is_zero_padd ? '0' : ' '));
	unsigned_fill_arg(info, conv, conv_len);
	free(conv);
	info->arg_cur = info->arg_size;
}

/*
** Manage unsigned numbers with sizes.
*/
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
	mmanage_unsigned(info);
}

/*
** Manage signed numbers.
*/
static void			mmanage_signed(t_info *info)
{
	char			*conv;

	conv = signedtochar(info->data.ll, info->precision);
	(void)conv;
	(void)info;
}

/*
** Manage signed numbers with sizes.
*/
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
	mmanage_signed(info);
}

/*
** Manages custom specifiers, currently just '%'.
*/
static void			manage_custom(va_list *args, t_info *info)
{
	(void)args;
	if (info->specifier == '%')
	{
		info->arg = malloc(sizeof(char) * 2);
		*info->arg = '%';
		*(info->arg + 1) = 0;
		info->arg_size = 2;
	}
}

/*
** Manages pointer.
*/
static void			manage_pointer(va_list *args, t_info *info)
{
	info->data.p = va_arg(*args, void*);
	info->is_alt = 1;
	info->precision = -1;
	info->specifier = 'x';
	info->size_flag = LONG_LONG_SIZE;
	mmanage_unsigned(info);
}

/*
** Build argument string and copy it to the result.
*/
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
	grow_result(info, info->arg, info->arg_cur);
	free((void*)info->arg);
}

/*
** Outputs formatted string.
*/
int					ft_printf(const char *fmt, ...)
{
	va_list			args;
	t_info			info;
	const char		*p;

	if (!(p = fmt) || fmt == 0)
		return (ENULLFMT);
	va_start(args, fmt);
	info.init = 0;
	clear_info(&info);
	while (*fmt)
	{
		if (*fmt == '%' && ++fmt)
		{
			grow_result(&info, p, ((fmt - 1) - p));
			if (!validate_arg(&fmt, &info, &args))
				return (EINVFMT);
			manage_arg(&args, &info);
			clear_info(&info);
			p = fmt;
		}
		++fmt;
	}
	end_result(fmt, p, &info);
	va_end(args);
	return ((int)info.cur);
}
