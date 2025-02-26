/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_closing_dinner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:50:08 by root              #+#    #+#             */
/*   Updated: 2025/02/26 18:20:49 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_and_clean(t_data *data)
{
	int	i;

	i = -1;
	if (data->ph)
	{
		while(++i < data->nb_ph)
		{
			handle_mutex(data, &data->ph[i].ph_mtx, DESTROY);
			handle_mutex(data, &data->forks[i], DESTROY);
		}
		free(data->ph);
		data->ph = NULL;
	}
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	handle_mutex(data, &data->write_mtx, DESTROY);
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
