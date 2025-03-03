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
	wait_threads(philo->data);
	set_time_var(philo->data, &philo->ph_mtx, &philo->last_meal, get_time(philo->data, MILLISECONDS));
	handle_mutex(philo->data, &philo->data->data_mtx, LOCK);
	philo->data->th_running++;
	handle_mutex(philo->data, &philo->data->data_mtx, UNLOCK);
	print_ph_status(philo, TOOK_FORK);
	while(!end_dinner(philo->data, NULL, MEAL_END))
	{
		my_usleep(philo->data, philo->data->time_to_die);
	}
	return (NULL);
}
/*
bool check_time_left(t_philo *philo)
{
long time_passed;
long time_to_die;
if (philo->ph_eating)
return (false);
time_passed = get_time(philo->data, MILLISECONDS) - philo->last_meal;
time_to_die = philo->data->time_to_die / 1000;
if (time_passed >= time_to_die)
{
print_ph_status(philo, DIED);
philo->ph_dead = true;
return (true);
}
return(false);
}
*/


bool	check_time_left(t_philo *philo)
{
	long	time_passed;
	long	time_to_die;
	long	last_meal;
	bool	eating;

	handle_mutex(philo->data, &philo->ph_mtx, LOCK);
	eating = philo->ph_eating;
	last_meal = philo->last_meal;
	handle_mutex(philo->data, &philo->ph_mtx, UNLOCK);

	if (eating)
		return (false);
	
	time_passed = get_time(philo->data, MILLISECONDS) - last_meal;
	time_to_die = philo->data->time_to_die / 1000;
	if (time_passed >= time_to_die)
	{
		print_ph_status(philo, DIED);
		return (true);
	}
	return(false);
}

bool	check_threads(t_data *data, t_mtx *mtx, long *nb_th, long nb_ph)
{
	bool	ret;

	ret = false;
	handle_mutex(data, mtx, LOCK);
	if (*nb_th == nb_ph)
		ret = true;
	handle_mutex(data, mtx, UNLOCK);
	return (ret);
}

void	*monitor(void *data_ptr)
{
	t_data	*data;
	int	i;
	long nb_ph_full;
	data = (t_data *)data_ptr;
	while (!check_threads(data, &data->data_mtx, &data->th_running, data->nb_ph))
		;
	while(!end_dinner(data, NULL, MEAL_END))
	{
		i = -1;
		while(++i < data->nb_ph && !end_dinner(data, NULL, MEAL_END))
		{
			if (check_time_left(data->ph + i))
				set_bool_var(data, &data->data_mtx, &data->end_dinner, true);
		}
		usleep(500);
		handle_mutex(data, &data->data_mtx, LOCK);
		nb_ph_full = data->nb_ph_full;
		handle_mutex(data, &data->data_mtx, UNLOCK);
		if (data->nb_ph_full >= data->nb_ph)
		{
			set_bool_var(data, &data->data_mtx, &data->all_ph_full, true);
			set_bool_var(data, &data->data_mtx, &data->end_dinner, true);
		}
	}
	return (NULL);
}

void	*dinner_routine(void *ph_ptr)
{
	t_philo *philo;

	
	philo = (t_philo *)ph_ptr;
	wait_threads(philo->data);
	set_time_var(philo->data, &philo->ph_mtx, &philo->last_meal, get_time(philo->data, MILLISECONDS));
	handle_mutex(philo->data, &philo->data->data_mtx, LOCK);
	philo->data->th_running++;
	handle_mutex(philo->data, &philo->data->data_mtx, UNLOCK);
	hold_your_horses(philo);
	while(!end_dinner(philo->data, NULL, MEAL_END) && !end_dinner(philo->data, philo, PH_FULL))
	{
		ph_eating(philo);
		if (philo->ph_full)
			break;
		print_ph_status(philo, SLEEPING);
		my_usleep(philo->data, philo->data->time_to_sleep);
		ph_thinking(philo, false);
		my_usleep(philo->data, 10);
	}
	return (NULL);
}

void	start_dinner(t_data *data)
{
	int	i;
	
	set_time_var(data, &data->data_mtx, &data->start_meal_time, get_time(data, MILLISECONDS));
	if (data->nb_ph == 1)
		handle_thread(data, &data->ph[0].ph_thread, &mr_lonely, &data->ph[0], CREATE);
	else
	{
		i = -1;	
		while(++i < data->nb_ph)
			handle_thread(data, &data->ph[i].ph_thread, &dinner_routine, &data->ph[i], CREATE);
	}
	handle_thread(data, &data->mon_thread, &monitor, data, CREATE);
	set_bool_var(data, &data->data_mtx, &data->threads_ready, true);
	i = -1;
	while(++i < data->nb_ph)
		handle_thread(data, &data->ph[i].ph_thread, NULL, NULL, JOIN);
	handle_thread(data, &data->mon_thread, NULL, NULL, JOIN);
}
