/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:54:47 by root              #+#    #+#             */
/*   Updated: 2025/02/27 15:14:01 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	data.ph_check = false;
	data.forks_check = false;
	data.write_mtx_check = false;
	data.data_mtx_check = false;
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
