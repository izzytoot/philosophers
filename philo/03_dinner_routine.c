/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_dinner_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:27:17 by root              #+#    #+#             */
/*   Updated: 2025/02/26 18:20:18 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*mr_lonely(void *ph_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ph_ptr;
	print_ph_status(philo, TOOK_FORK);
	while(!end_dinner(philo->data))
	{
		handle_mutex(philo->data, &philo->ph_mtx, LOCK);
		my_usleep(philo->data, 200);
		handle_mutex(philo->data, &philo->ph_mtx, UNLOCK);
	}
	return (NULL);
}

void	*monitor(void *ph_ptr)
{
	t_philo	*philo;
		
	philo = (t_philo *)ph_ptr;
	while(!get_bool(philo->data, &philo->data->data_mtx, &philo->data->all_ph_full) &&
			!get_bool(philo->data, &philo->data->data_mtx, &philo->data->end_dinner))
	{
		if (philo->data->nb_ph_full >= philo->data->nb_ph)
			set_bool_var(philo->data, &philo->data->data_mtx, &philo->data->all_ph_full, true);
	}
	return (NULL);
}

void	*dinner_routine(void *ph_ptr)
{
	t_philo *philo;
	long	current_time;
	
	philo = (t_philo *)ph_ptr;
//	wait_threads(philo->data);
	current_time = get_time(philo->data, MILLISECONDS);
	set_time_var(philo->data, &philo->ph_mtx, &philo->last_meal, current_time);
	while(!end_dinner(philo->data))
	{
		if (pre_dinner_check(philo))
			break;
		ph_eating(philo);
		print_ph_status(philo, THINKING);
		my_usleep(philo->data, 10);
	}
	return (NULL);
}

bool	end_dinner(t_data *data)
{
	return(get_bool(data, &data->data_mtx, &data->end_dinner));
}

void	start_dinner(t_data *data)
{
	int	i;
	
	set_time_var(data, &data->data_mtx, &data->start_meal_time, get_time(data, MILLISECONDS));
	if (data->nb_ph == 1)
	{	
		handle_thread(data, &data->data_thread, &mr_lonely, &data->ph[0], CREATE);
		handle_thread(data, &data->data_thread, NULL, NULL, JOIN);
	}
	else
	{
		i = -1;	
		while(++i < data->nb_ph)
			handle_thread(data, &data->ph[i].ph_thread, &dinner_routine, &data->ph[i], CREATE);
	}
	set_bool_var(data, &data->data_mtx, &data->threads_ready, true);
	handle_thread(data, &data->mon_thread, &monitor, &data->ph[0], CREATE);
	i = -1;
	while(++i < (data)->nb_ph)
		handle_thread(data, &data->ph[i].ph_thread, NULL, NULL, JOIN);
	handle_thread(data, &data->mon_thread, NULL, NULL, JOIN);
	free_and_clean(data);
}
