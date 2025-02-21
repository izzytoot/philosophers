/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_closing_dinner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:50:08 by root              #+#    #+#             */
/*   Updated: 2025/02/21 17:14:24 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myphilo.h"

void	free_and_clean(t_data *data)
{
	int	i;

	i = -1;
	if (data->ph)
	{
		while(++i < data->nb_ph)
		{
		//	handle_mutex(data, &data->ph[i].acc_mtx_ph, DESTROY);
		//	handle_mutex(data, &data->ph[i].r_fork_mtx, DESTROY);
		//	handle_mutex(data, &data->ph[i].l_fork_mtx, DESTROY);
		//	handle_mutex(data, &data->forks[i], DESTROY);
			free(data->ph[i].ph_thread);
			data->ph[i].ph_thread = NULL;
		}
		free(data->ph);
		data->ph = NULL;
	}
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->data_thread)
	{
		free(data->data_thread);
		data->data_thread = NULL;
	}
	if (data->mon_thread)
	{
		free(data->mon_thread);
		data->mon_thread = NULL;
	}
//	handle_mutex(data, &data->write_mtx, DESTROY);
//	handle_mutex(data, &data->acc_mtx, DESTROY);
	free(data);
	data = NULL;
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
	exit(1);
}
