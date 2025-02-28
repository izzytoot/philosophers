/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_dinner_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:27:17 by root              #+#    #+#             */
/*   Updated: 2025/02/28 12:57:12 by root             ###   ########.fr       */
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

bool	check_time_to_die(t_philo *philo)
{
	long	time_passed;
	long	time_to_die;
	//bool 	is_eating;
	
	handle_mutex(philo->data, &philo->ph_mtx, LOCK);
	time_passed = get_time(philo->data, MILLISECONDS) - philo->last_meal;
   	printf("ph %d time passed: %lu\n", philo->ph_id, time_passed);
	time_to_die = philo->data->time_to_die / 1000;
	printf("ph %d time to die: %lu\n", philo->ph_id, time_to_die);
	//is_eating = philo->ph_eating;
	handle_mutex(philo->data, &philo->ph_mtx, UNLOCK);
	if (time_passed >= time_to_die) // ver se é preciso check ph_eating
	{
		print_ph_status(philo, DIED);
		set_bool_var(philo->data, &philo->ph_mtx, &philo->ph_dead, true);
		return (true);
	}
	return(false);
}

//PHILOS + 1 FOR PASSING PHILO INFO
void	*monitor(void *data_ptr)
{
	t_data	*data;
	bool all_full;
	int	i;
	
	data = (t_data *)data_ptr;
	//wait_threads(philo->data);
	printf("entered monitor\n");
	while(!end_dinner(data, NULL, MEAL_END))
	{		
		i = -1;
		while(++i < data->nb_ph && !end_dinner(data, NULL, MEAL_END)) //en dinner??
		{
			printf("entered here 2\n");
			if (check_time_to_die(data->ph + i))
			{	
				set_bool_var(data, &data->data_mtx, &data->end_dinner, true);
				break;
			}
		}
		handle_mutex(data, &data->data_mtx, LOCK);
		all_full = (data->nb_ph_full >= data->nb_ph);
		handle_mutex(data, &data->data_mtx, UNLOCK);
		if (all_full)
		{
			set_bool_var(data, &data->data_mtx, &data->all_ph_full, true);
			set_bool_var(data, &data->data_mtx, &data->end_dinner, true);
			break;
		}
		my_usleep(data, 100);
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

