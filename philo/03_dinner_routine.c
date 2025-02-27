/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_dinner_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:27:17 by root              #+#    #+#             */
/*   Updated: 2025/02/27 17:40:19 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*mr_lonely(void *ph_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ph_ptr;
	print_ph_status(philo, TOOK_FORK);
	while(!end_dinner(philo->data, NULL, MEAL_END))
	{
		handle_mutex(philo->data, &philo->ph_mtx, LOCK);
		my_usleep(philo->data, 200);
		handle_mutex(philo->data, &philo->ph_mtx, UNLOCK);
	}
	return (NULL);
}
//PHILOS + 1 FOR PASSING PHILO INFO
void	*monitor(void *data_ptr)
{
	t_data	*data;
	long	start_time;
	long	time_passed;
	long	time_to_die;
	long	current_time;
	long	last_meal_time;
		
	data = (t_data *)data_ptr;
	//wait_threads(philo->data);
   	start_time = get_time_var(data, &data->data_mtx, &data->start_meal_time);
	while(!end_dinner(data, NULL, MEAL_END))
	{
		current_time = get_time(data, MILLISECONDS);
		last_meal_time = get_time_var(data, &data->, &data->last_meal);
		time_passed =  current_time - last_meal_time;
		time_to_die = get_time_var(philo->data, &philo->ph_mtx, &philo->data->time_to_die) / 1000;		
		printf("Current time: %ld\n", current_time - start_time);
        printf("Last meal time: %ld\n", last_meal_time - start_time);
        printf("Time passed: %ld\n", time_passed);
        printf("Time to die: %ld\n", time_to_die);
		if (time_passed >= time_to_die) // ver se é preciso check ph_eating
		{
			set_bool_var(philo->data, &philo->ph_mtx, &philo->ph_dead, true);
			print_ph_status(philo, DIED);
			set_bool_var(philo->data, &philo->data->data_mtx, &philo->data->end_dinner, true);
			break;
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

/*
void	*monitor(void *ph_ptr)
{
	t_philo	*philo;
		
	philo = (t_philo *)ph_ptr;
	while(!end_dinner(philo->data, philo, MEAL_END))
	{
		if (philo->data->nb_ph_full >= philo->data->nb_ph)
		{
			set_bool_var(philo->data, &philo->data->data_mtx, &philo->data->all_ph_full, true);
			set_bool_var(philo->data, &philo->data->data_mtx, &philo->data->end_dinner, true);
		}
	}
	return (NULL);
}
*/
void	*dinner_routine(void *ph_ptr)
{
	t_philo *philo;
//	long	current_time;
	
	philo = (t_philo *)ph_ptr;
	wait_threads(philo->data);
//	current_time = get_time(philo->data, MILLISECONDS);
	set_time_var(philo->data, &philo->ph_mtx, &philo->last_meal, get_time(philo->data, MILLISECONDS));
	while(!end_dinner(philo->data, NULL, MEAL_END) && !end_dinner(philo->data, philo, PH_FULL))
	{
		/*
		if (pre_dinner_check(philo))
			break;
		*/
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
	handle_thread(data, &data->mon_thread, &monitor, &data, CREATE);
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
	i = -1;
	while(++i < (data)->nb_ph)
		handle_thread(data, &data->ph[i].ph_thread, NULL, NULL, JOIN);
	handle_thread(data, &data->mon_thread, NULL, NULL, JOIN);
}
