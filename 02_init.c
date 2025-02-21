/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:02:13 by root              #+#    #+#             */
/*   Updated: 2025/02/21 18:32:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myphilo.h"

void	assign_forks(t_data *data)
{
	int	i;
	
	i = -1;
	while(++i < data->nb_ph)
		handle_mutex(data, &data->forks[i], INIT);
	i = 0;
		data->ph[0].r_fork_mtx = data->forks[i];
		data->ph[0].l_fork_mtx = data->forks[i + 1];
		data->ph[data->nb_ph - 1].r_fork_mtx = data->forks[data->nb_ph - 1];
		data->ph[data->nb_ph - 1].l_fork_mtx = data->forks[i];
		while(++i < (data->nb_ph - 1))
		{
			data->ph[i].r_fork_mtx = data->forks[i];
			data->ph[i].l_fork_mtx = data->forks[i + 1];
		}
}

void	init_philos(t_data *data)
{
	int	i;
	
	i = -1;
	while(++i < data->nb_ph)
	{
		data->ph[i].data = data;
		data->ph[i].ph_id = i + 1;
		data->ph[i].meal_count = 0;
		data->ph[i].ph_eating = false;
		data->ph[i].ph_full = false;
		data->ph[i].ph_dead = false;
		data->ph[i].time_left = data->time_to_die;
		handle_mutex(data, &data->ph[i].acc_mtx_ph, INIT);
	}
}

void	alloc_memory_data(t_data *data)
{
	int size;
	
	size = (int)data->nb_ph;
	data->ph = malloc(sizeof(t_philo) * size);
	if(!data->ph)
		error_and_exit(data, RED ERR_MEM RES, 2);
	data->forks = malloc(sizeof(t_mtx) * size);
	if(!data->forks)
		error_and_exit(data, RED ERR_MEM RES, 2);
}

void	program_init(t_data *data)
{
	data->start_meal_time = 0;
	data->ph_dead = false;
	data->all_ph_full = false;
	alloc_memory_data(data);
	handle_mutex(data, &data->write_mtx, INIT); 
	handle_mutex(data, &data->acc_mtx, INIT);
	init_philos(data);
	assign_forks(data);
}


