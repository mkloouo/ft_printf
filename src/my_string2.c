/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_string2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 20:32:32 by modnosum          #+#    #+#             */
/*   Updated: 2018/07/24 20:36:20 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_string.h>
#include <stdlib.h>

void		my_strnew(char **s, size_t size)
{
	size_t	i;

	*s = malloc(sizeof(char) * size);
	i = 0;
	while (i < size)
		(*s)[i++] = 0;
}

size_t		my_strlen(char const *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		++len;
	return (len);
}
