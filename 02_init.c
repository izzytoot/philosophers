/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:02:13 by root              #+#    #+#             */
/*   Updated: 2025/02/21 16:52:39 by root             ###   ########.fr       */
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
		data->ph[i].ph_thread = malloc(sizeof(pthread_t) * data->nb_ph);
		handle_mutex(data, &data->ph[i].acc_mtx_ph, INIT);
	}
}

void	alloc_memory_data(t_data *data)
{
	int size;
	
	size = (int)data->nb_ph;
	data->data_thread = malloc(sizeof(pthread_t) * size);
	if(!data->data_thread)
		error_and_exit(data, RED ERR_MEM RES, 2);
	data->mon_thread = malloc(sizeof(pthread_t) * size);
	if(!data->mon_thread)
		error_and_exit(data, RED ERR_MEM RES, 2);
	data->ph = malloc(sizeof(t_philo) * size);
	if(!data->ph)
		error_and_exit(data, RED ERR_MEM RES, 2);
	data->forks = malloc(sizeof(t_mtx) * size);
	if(!data->forks)
		error_and_exit(data, RED ERR_MEM RES, 2);
}

void	program_init(t_data **data)
{
	(*data)->start_meal_time = 0;
	(*data)->ph_dead = false;
	(*data)->all_ph_full = false;
	handle_mutex(*data, &(*data)->write_mtx, INIT); 
	handle_mutex(*data, &(*data)->acc_mtx, INIT);
	alloc_memory_data(*data);
	init_philos(*data);
	assign_forks(*data);
	/*
	printf("nb_ph is %d\n", (*data)->nb_ph);
	printf("max_meals is %d\n", (*data)->max_meals);
	printf("time_to_die is %d\n", (*data)->time_to_die);
	printf("time_to_eat is %d\n", (*data)->time_to_eat);
	printf("time_to_sleep is %d\n", (*data)->time_to_sleep);
	printf("start_meal_time is %d\n", (*data)->start_meal_time);
	*/
}


