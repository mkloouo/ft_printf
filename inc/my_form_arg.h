/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_form_arg.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 16:57:02 by modnosum          #+#    #+#             */
/*   Updated: 2018/07/28 17:51:22 by modnosum         ###   ########.fr       */
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
void			manage_unsi(t_info *info);
void			manage_octa(t_info *info);
void			manage_hexa(t_info *info);
void			manage_cap_hexa(t_info *info);

void			manage_signed(va_list *args, t_info *info);
void			manage_custom(va_list *args, t_info *info);
void			manage_pointer(va_list *args, t_info *info);

#endif
