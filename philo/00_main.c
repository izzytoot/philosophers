/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:54:47 by root              #+#    #+#             */
/*   Updated: 2025/02/10 18:04:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_program program;
	
	if (ac == 5 || ac == 6)
	{
		program.init_error = false;
		input_parsing(&program, av);
		if(program.init_error == false)
		{
			program_init(&program);
			start_simulation(&program);
			free_and_clean (&program);
		}
		else
			print_error_and_exit(&program, RED"Error!\n"RESET, 2);
	}
	else
		print_error_and_exit(&program, RED"Error!\nRun: ./philo <nb_of_philos><time_to_die><time_to_eat><time_to_sleep><max_meals>[optional]"RESET, 2);
	return (0);
}