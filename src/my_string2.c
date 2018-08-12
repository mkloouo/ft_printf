/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_string2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 20:32:32 by modnosum          #+#    #+#             */
/*   Updated: 2018/08/12 18:33:35 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_string.h>
#include <stdlib.h>

char		*my_strnew(size_t size, char c)
{
	char	*str;
	size_t	i;

	str = malloc(sizeof(char) * (size + 1));
	i = 0;
	while (i < size)
		str[i++] = c;
	return (str);
}

size_t		my_wchar_size(wchar_t c)
{
	if (c <= 0x7F)
		return (1);
	else if (c <= 0x7FF)
		return (2);
	else if (c <= 0xFFFF)
		return (3);
	else
		return (4);
}

size_t		my_wstrlen(wchar_t const *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		++len;
	return (len);
}

size_t		my_wstrclen(wchar_t const *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		len += my_wchar_size(str[i]);
		++i;
	}
	return (len);
}

size_t		my_strlen(char const *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		++len;
	return (len);
}
