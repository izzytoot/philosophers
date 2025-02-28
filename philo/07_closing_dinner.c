/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_closing_dinner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:50:08 by root              #+#    #+#             */
/*   Updated: 2025/02/27 14:51:06 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	end_dinner(t_data *data, t_philo *philo, t_end code)
{
	if (code == PH_FULL)
		return(get_bool(data, &philo->ph_mtx, &philo->ph_full));
	else if (code == MEAL_END)
		return(get_bool(data, &data->data_mtx, &data->end_dinner));
	return (false);
}

void	free_and_clean(t_data *data)
{
	int	i;

	i = -1;
	if (data->ph_check)
	{
		while(++i < data->nb_ph)
		{
			handle_mutex(data, &data->ph[i].ph_mtx, DESTROY);
			handle_mutex(data, &data->forks[i], DESTROY);
		}
		free(data->ph);
		data->ph = NULL;
	}
	if (data->forks_check)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->write_mtx_check)
		handle_mutex(data, &data->write_mtx, DESTROY);
	if (data->data_mtx_check)
		handle_mutex(data, &data->data_mtx, DESTROY);
}

void	error_and_exit(t_data *data, char *message, int fd)
{
	int	i;

	i = 0;
	(void)data;
	if (data)
		free_and_clean(data);
	if (message)
	{
		while(message[i])
		{
			write(fd, &message[i], 1);
			i++;
		}	
	}
	exit(EXIT_FAILURE);
}
