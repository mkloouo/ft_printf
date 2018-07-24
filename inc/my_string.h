/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 20:33:46 by modnosum          #+#    #+#             */
/*   Updated: 2018/07/24 20:37:20 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_STRING_H
# define MY_STRING_H

# include <stddef.h>
# include <sys/types.h>

char const	*my_strchr(char const *haystack, char needle);
void		my_putnstr(char *str, size_t n);
void		my_strfill(char *str, size_t len, char ch);
void		my_strncpy(char *dst, const char *src, size_t n);
char		*my_resize_str(const char *src, size_t size, size_t new_size);
void		my_strnew(char **s, size_t size);
size_t		my_strlen(char const *str);

#endif
