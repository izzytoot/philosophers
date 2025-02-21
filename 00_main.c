/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:54:47 by root              #+#    #+#             */
/*   Updated: 2025/02/21 17:47:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myphilo.h"

int	main(int ac, char **av)
{
	t_data	data;
	
	if (ac == 5 || ac == 6)
	{
		input_parsing_and_sort(&data, av);
		program_init(&data);
		start_dinner(&data);
	}
	else
		error_and_exit(&data, RED ERR_INP RES, 2);
	free_and_clean(&data);
	return (0);
}
