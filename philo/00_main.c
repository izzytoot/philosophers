/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:54:47 by root              #+#    #+#             */
/*   Updated: 2025/02/13 17:27:29 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_program program;
	
	if (ac == 5 || ac == 6)
	{
		input_parsing(&program, av);
		program_init(&program);
	//	start_simulation(&program);
	//	free_and_clean (&program);
	}
	else
		print_error_and_exit(&program, RED"Error!\nRun: ./philo <nb_of_philos><time_to_die><time_to_eat><time_to_sleep><max_meals>[optional]\n"RESET, 2);
	free_and_clean(&program);
	return (0);
}