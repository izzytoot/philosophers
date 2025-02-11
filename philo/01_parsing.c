/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:44:32 by root              #+#    #+#             */
/*   Updated: 2025/02/11 18:05:31 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	conv_nb;
	int		i;
	
	conv_nb = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		conv_nb = conv_nb * 10 + (str[i] - '0');
		i++;
	}
	return(conv_nb);
}

long	conv_and_check_limits(t_program *program, char *av)
{
	long	checked_nb;
	
	checked_nb = ft_atol(av);
	if (checked_nb > INT_MAX || checked_nb < 1)
		print_error_and_exit(&program, RED"Error! Values must be positive ints.\n"RESET, 2);
	return(checked_nb);
}

void	input_parsing(t_program *program, char **av)
{
	program->nb_philos = conv_and_check_limits(&program, av[1]);
	if (program->nb_philos > 200 || program->nb_philos < 1)
		print_error_and_exit(&program, RED"Error! Philos must be between 1 and 200.\n"RESET, 2);
	program->time_to_die = conv_and_check_limits(&program, av[2]) * 1000;
	program->time_to_eat = conv_and_check_limits(&program, av[3]) * 1000;
	program->time_to_sleep = conv_and_check_limits(&program, av[4]) * 1000;
	if (program->time_to_die < 60000 || program->time_to_eat < 60000 || program->time_to_die < 60000)
		print_error_and_exit(&program, RED"Error!Time values must be at least 60 seconds.\n"RESET, 2);
	if(av[5])
		program->max_meals = conv_and_check_limits(&program, av[5]);
	else
		program->max_meals = -1;
}