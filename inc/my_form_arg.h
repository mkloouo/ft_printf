/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_form_arg.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 16:57:02 by modnosum          #+#    #+#             */
/*   Updated: 2018/08/08 20:46:14 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_FORM_ARG_H
# define MY_FORM_ARG_H

# include <stdarg.h>
# include <stdlib.h>
# include <my_printf_info.h>
# include <my_string.h>

void			manage_arg(va_list *args, t_info *info);

void			manage_letters(va_list *args, t_info *info);

void			manage_unsigned(va_list *args, t_info *info);
void			form_unsigned(t_info *info, char const *base_chars);

void			manage_signed(va_list *args, t_info *info);
void			manage_custom(va_list *args, t_info *info);
void			manage_pointer(va_list *args, t_info *info);

#endif
