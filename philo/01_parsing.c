/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:44:32 by root              #+#    #+#             */
/*   Updated: 2025/02/27 14:21:07 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	conv_and_check(t_data *data, char *av)
{
	long	result;
	int	i;

	result = 0;
	i = 0;
	while ((av[i] >= 9 && av[i] <= 13) || av[i] == 32)
		i++;
	if (av[i] == '+' || av[i] == '-')
		i++;
	while ((av[i] >= '0') && (av[i] <= '9'))
	{
		result = result * 10 + (av[i] - '0');
		i++;
	}
	if (result < 1 || result > INT_MAX)
		error_and_exit(data, RED ERR_INP2 RES, 2);
	return(result);
}

void	basic_checker(char *av)
{
	int	i;

	i = 0;
	while(av[i])
	{
		if (av[i] == ' ')
			i++;
		if (av[i] < '0' || av[i] > '9')
			error_and_exit(NULL, RED ERR_INP2 RES, 2);
		i++;
	}
}
void	init_input_data(t_data *data, char **av)
{
	data->nb_ph = conv_and_check(data, av[1]);
	if (data->nb_ph > 200)
		error_and_exit(data, RED ERR_NB_PHILOS RES, 2);
	data->time_to_die = conv_and_check(data, av[2]) * 1000;
	data->time_to_eat = conv_and_check(data, av[3]) * 1000;
	data->time_to_sleep = conv_and_check(data, av[4]) * 1000;
	if (data->time_to_die < 60000 || data->time_to_eat < 60000 || data->time_to_sleep < 60000)
		error_and_exit(data, RED ERR_TIME_LIMIT RES, 2);
	if (av[5])
	{
		data->max_meals = conv_and_check(data, av[5]);
		data->av5 = true;	
	}
	else
	{
		data->max_meals = -1;
		data->av5 = false;
	}
}

void	input_parsing_and_sort(t_data *data, char **av)
{
	int	i;

	i = 0;
	if (!data)
		error_and_exit(data, RED ERR_MEM RES, 2);
	data->ph_check = false;
	data->forks_check = false;
	data->write_mtx_check = false;
	data->data_mtx_check = false;
	while(av[++i])
		basic_checker(av[i]);
	init_input_data(data, av);
}