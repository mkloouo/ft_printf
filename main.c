/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 13:20:05 by modnosum          #+#    #+#             */
/*   Updated: 2018/08/20 16:12:59 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <stdio.h>

#ifdef CUSTOM_PRECISION
	#include <stdlib.h>
#endif

int		main(int ac, char **av)
{
#ifdef CUSTOM_PRECISION
	if (ac != 2)
		return (1);
	int	precision = atoi(av[1]);
#endif

	ft_printf("[%15.4S]\n", L"我是一只猫。");
	return (0);
}
