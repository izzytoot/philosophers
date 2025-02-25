/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_dinner_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:27:17 by root              #+#    #+#             */
/*   Updated: 2025/02/25 20:08:33 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myphilo.h"

void	*mr_lonely(void *ph_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ph_ptr;
	print_ph_status(philo, TOOK_FORK);
	while(!philo->ph_dead)
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
	while(!philo->data->all_ph_full || !philo->data->ph_dead)
	{
		handle_mutex(philo->data, &philo->ph_mtx, LOCK);
		if (philo->data->nb_ph_full >= philo->data->nb_ph)
			philo->data->all_ph_full = true;
		handle_mutex(philo->data, &philo->ph_mtx, UNLOCK);
	}
	return (NULL);
}

int	pre_dinner_check(t_philo *philo)
{
	__uint64_t	time_passed;
	
	if(!philo->data->ph_dead)
	{
		time_passed = get_time(philo->data, MILLISECONDS) - philo->last_meal;
   		if (time_passed >= philo->data->time_to_die && !philo->ph_eating)
		{
			set_bool_var(philo->data, &philo->ph_mtx, &philo->ph_dead, true);
			set_bool_var(philo->data, &philo->data->data_mtx, &philo->data->ph_dead, true);
    	  	print_ph_status(philo, DIED);
			return (1);
		}
	}
	if(philo->data->all_ph_full)
	{
		printf("philos are full!\n");
		return (1);
	}
	return(0);
}

void	*dinner_routine(void *ph_ptr)
{
	t_philo *philo;
	
	philo = (t_philo *)ph_ptr;
	set_bool_var(philo->data, &philo->data->data_mtx, &philo->data->threads_ready, true); // do we need this?
	while(!philo->data->ph_dead)
	{
		if (pre_dinner_check(philo))
			break;
		ph_eating(philo);
		print_ph_status(philo, THINKING);
		my_usleep(philo->data, 100);
	}
	return (NULL);
}

void	start_dinner(t_data *data)
{
	int	i;
	
//	set_time_var(data, &data->data_mtx, &data->start_meal_time, get_time(data, MILLISECONDS));
	if (data->max_meals > 0)
		handle_thread(data, &data->mon_thread, &monitor, &data->ph[0], CREATE);
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
	i = -1;
	while(++i < (data)->nb_ph)
		handle_thread(data, &data->ph[i].ph_thread, NULL, NULL, JOIN);
	if (data->max_meals > 0)
        handle_thread(data, &data->mon_thread, NULL, NULL, JOIN);
	free_and_clean(data);
}
