/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:02:13 by root              #+#    #+#             */
/*   Updated: 2025/02/27 14:50:16 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_data *data)
{
	int	i;
	
	i = -1;
	while(++i < data->nb_ph)
		handle_mutex(data, &data->forks[i], INIT);
}

void	init_philos(t_data *data)
{
	int	i;
	t_philo *philo;
	
	i = -1;
	while(++i < data->nb_ph)
	{
		philo = data->ph + i;
		philo->ph_id = i + 1;
		philo->meal_count = 0;
		philo->ph_eating = false;
		philo->ph_full = false;
		philo->ph_dead = false;
		philo->data = data;
		philo->last_meal = get_time(philo->data, MILLISECONDS);
		philo->l_fork_mtx = &data->forks[i];
		philo->r_fork_mtx = &data->forks[(i + 1) % data->nb_ph];
		handle_mutex(data, &data->ph[i].ph_mtx, INIT);
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
	data->end_dinner = false;
	data->nb_ph_full = 0;
	data->all_ph_full = false;
	data->threads_ready = false;
	data->start_meal_time = 0;
	data->th_running = 0;
	alloc_memory_data(data);
	handle_mutex(data, &data->write_mtx, INIT);
	data->write_mtx_check = true; 
	handle_mutex(data, &data->data_mtx, INIT);
	data->data_mtx_check = true;
	init_forks(data);
	data->forks_check = true;
	init_philos(data);
	data->ph_check = true;
}

