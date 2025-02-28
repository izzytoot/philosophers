/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_dinner_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:27:17 by root              #+#    #+#             */
/*   Updated: 2025/02/28 15:36:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*mr_lonely(void *ph_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ph_ptr;
	set_time_var(philo->data, &philo->ph_mtx, &philo->last_meal, get_time(philo->data, MILLISECONDS));
	print_ph_status(philo, TOOK_FORK);
	while(!end_dinner(philo->data, NULL, MEAL_END))
	{
		my_usleep(philo->data, philo->data->time_to_die);
	}
	return (NULL);
}

bool	check_time_left(t_philo *philo)
{
	long	time_passed;
	long	time_to_die;
	bool 	is_eating;

	handle_mutex(philo->data, &philo->ph_mtx, LOCK);
	time_passed = get_time(philo->data, MILLISECONDS) - philo->last_meal;
	time_to_die = philo->data->time_to_die / 1000;
	is_eating = philo->ph_eating;
	handle_mutex(philo->data, &philo->ph_mtx, UNLOCK);
	if (time_passed >= time_to_die && !is_eating) // ver se é preciso check ph_eating
	{
		print_ph_status(philo, DIED);
		set_bool_var(philo->data, &philo->ph_mtx, &philo->ph_dead, true);
		return (true);
	}
	return(false);
}

void	*monitor(void *ph_ptr)
{
	t_philo	*philo;
		
	philo = (t_philo *)ph_ptr;
	while(!end_dinner(philo->data, NULL, MEAL_END))
	{
		if (!get_bool(philo->data, &philo->ph_mtx, &philo->ph_full))
		{
			if (check_time_left(philo))
			{
				set_bool_var(philo->data, &philo->data->data_mtx, &philo->data->end_dinner, true);
				break;
			}	
		}
		if (philo->data->nb_ph_full >= philo->data->nb_ph)
		{
			set_bool_var(philo->data, &philo->data->data_mtx, &philo->data->all_ph_full, true);
			set_bool_var(philo->data, &philo->data->data_mtx, &philo->data->end_dinner, true);
		}
		my_usleep(philo->data, 100);
	}
	return (NULL);
}

void	*dinner_routine(void *ph_ptr)
{
	t_philo *philo;

	
	philo = (t_philo *)ph_ptr;
	wait_threads(philo->data);
	set_time_var(philo->data, &philo->ph_mtx, &philo->last_meal, get_time(philo->data, MILLISECONDS));
	while(!end_dinner(philo->data, NULL, MEAL_END) && !end_dinner(philo->data, philo, PH_FULL))
	{
		ph_eating(philo);
		if (!end_dinner(philo->data, philo, PH_FULL))
			print_ph_status(philo, THINKING);
		my_usleep(philo->data, 10);
	}
	return (NULL);
}

void	start_dinner(t_data *data)
{
	int	i;
	
	set_time_var(data, &data->data_mtx, &data->start_meal_time, get_time(data, MILLISECONDS));
	handle_thread(data, &data->mon_thread, &monitor, &data->ph[0], CREATE);
	if (data->nb_ph == 1)
	{	
		handle_thread(data, &data->data_thread, &mr_lonely, &data->ph[0], CREATE);
//		handle_thread(data, &data->data_thread, NULL, NULL, JOIN);
	}
	else
	{
		i = -1;	
		while(++i < data->nb_ph)
			handle_thread(data, &data->ph[i].ph_thread, &dinner_routine, &data->ph[i], CREATE);
	}
	set_bool_var(data, &data->data_mtx, &data->threads_ready, true);
	i = -1;
	while(++i < (data)->nb_ph)
		handle_thread(data, &data->ph[i].ph_thread, NULL, NULL, JOIN);
	handle_thread(data, &data->mon_thread, NULL, NULL, JOIN);
}
