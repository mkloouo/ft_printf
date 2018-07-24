/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_parse_printf.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 20:37:04 by modnosum          #+#    #+#             */
/*   Updated: 2018/07/24 21:00:17 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_PARSE_PRINTF_H
# define MY_PARSE_PRINTF_H

# include <my_printf_info.h>

void	my_parse_star(char const **fmt, int *number,
		va_list *args);
void	my_manage_size_flag(char const **fmt, t_info *info,
		t_size_f new_size);
void	my_parse_size_flags(char const **fmt, t_info *info);
int		my_parse_specifier(char const **fmt, t_info *info);
int		my_validate_arg(char const **pos, char const **fmt,
		t_info *info, va_list *args);
int		my_parse_number(char const **fmt);
void	my_parse_flags(char const **fmt, t_info *info);

#endif
