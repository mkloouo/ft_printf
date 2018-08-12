/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_string3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 21:23:31 by modnosum          #+#    #+#             */
/*   Updated: 2018/08/12 21:33:41 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_string.h>

/*

if (byte == 1)
	*(dst) = (char)src;
else if (byte == 2)
{
	*(dst) = (char)((src >> 6) + 0xC0);
	*(dst + 1) = (char)((src & 0x3F) + 0x80);
}
else if (byte == 3)
{
	*(dst) = (char)((src >> 12) + 0xE0);
	*(dst + 1) = (char)(((src >> 6) & 0x3F) + 0x80);
	*(dst + 2) = (char)((src & 0x3F) + 0x80);
}
else if (byte == 4)
{
	*(dst) = (char)((src >> 18) + 0xF0);
	*(dst + 1) = (char)(((src >> 12) & 0x3F) + 0x80);
	*(dst + 2) = (char)(((src >> 6) & 0x3F) + 0x80);
	*(dst + 3) = (char)((src & 0x3F) + 0x80);
}

*/

char		*my_wstrncpy(char *dst, wchar_t const *src, size_t n)
{
	size_t	i;
	size_t	wc_size;

	i = 0;
	while (i < n)
	{
		if ((wc_size = my_wchar_size(src[i])) == 1)
			dst[i] = (char)src[i];
		++i;
	}
	return (dst);
}
