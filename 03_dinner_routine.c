/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_dinner_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:27:17 by root              #+#    #+#             */
/*   Updated: 2025/02/24 16:00:01 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myphilo.h"

bool    get_bool(t_data *data, t_mtx *mtx, bool *value)
{
    bool ret;

    handle_mutex(data, mtx, LOCK);
    ret = *value;
    handle_mutex(data, mtx, UNLOCK);
    return (ret);

}

void    wait_threads(t_data *data)
{
    while(!get_bool(data, &data->acc_mtx, &data->threads_ready));
}


void	*mr_lonely(void *ph_ptr)
{
	t_philo	*philo;
	__uint64_t	time_left;

	philo = (t_philo *)ph_ptr;
	time_left = philo->data->time_to_die + get_time(philo->data, MILLISECONDS);
	set_time_var(philo->data, &philo->acc_mtx_ph, &philo->time_left, time_left);
	print_ph_status(philo, TOOK_FORK);
	while(!philo->ph_dead)
		my_usleep(philo->data, 200);
	return (NULL);
}

void	*monitor(void *ph_ptr)
{
	t_philo	*philo;
		
	philo = (t_philo *)ph_ptr;
//	printf(YLL"entered monitor\n"RES);
	while(!philo->data->ph_dead)
	{
		handle_mutex(philo->data, &philo->acc_mtx_ph, LOCK);
		if (philo->data->nb_ph_full >= philo->data->nb_ph)
			philo->data->ph_dead = true;
		handle_mutex(philo->data, &philo->acc_mtx_ph, UNLOCK);
	}
	return (NULL);
}
/*
void	*pre_dinner_check(void *ph_ptr)
{
	t_philo	*philo;
	__uint64_t	time_passed;
	
	philo = (t_philo *)ph_ptr;
//	printf(YLL"entered pre_dinner_check for philo %d\n"RES, philo->ph_id);
	wait_threads(philo->data);
	handle_mutex(philo->data, &philo->acc_mtx_ph, LOCK);
	if (philo->meal_count == philo->data->max_meals)
	{
		//set_bool_var(philo->data, &philo->acc_mtx_ph, &philo->ph_full, true);
		philo->ph_full = true;
		philo->data->nb_ph_full++;
	}
	time_passed = get_time(philo->data, MILLISECONDS) - philo->data->start_meal_time;
	if (time_passed >= philo->time_left && !philo->ph_eating)
	{	
		//set_bool_var(philo->data, &philo->acc_mtx_ph, &philo->ph_dead, true);
		philo->ph_dead = true;
		print_ph_status(philo, DIED);
	}
	handle_mutex(philo->data, &philo->acc_mtx_ph, UNLOCK);
	return (NULL);
}
*/

void	*dinner_routine(void *ph_ptr)
{
	t_philo *philo;
	__uint64_t	time_left;
	
	philo = (t_philo *)ph_ptr;
	time_left = philo->data->time_to_die + get_time(philo->data, MILLISECONDS);
	set_time_var(philo->data, &philo->acc_mtx_ph, &philo->time_left, time_left);
	printf(YLL"Philo %d time left: %-lu\n"RES, philo->ph_id, philo->time_left);
//	handle_thread(philo->data, &philo->ph_thread, &pre_dinner_check, philo, CREATE);
	while(philo->ph_dead == false)
	{
   		if (get_time(philo->data, MILLISECONDS) - philo->data->start_meal_time >= philo->time_left)
		{
			if (philo->ph_eating == false)
			{
				philo->ph_dead = true;
      		  	print_ph_status(philo, DIED);
       			break;
			}
		}
		ph_eating(philo);
		print_ph_status(philo, THINKING);
		my_usleep(philo->data, 100);
	}
	//handle_thread(philo->data, &philo->ph_thread, NULL, NULL, JOIN); - CAUSES DEADLOCK
	printf("Philosopher %d exiting routine\n", philo->ph_id);
	return (NULL);
}

void	start_dinner(t_data *data)
{
	int	i;
	
	data->start_meal_time = get_time(data, MILLISECONDS);
	handle_mutex(data, &data->acc_mtx, LOCK);
	if (data->max_meals > 0)
		handle_thread(data, &data->mon_thread, &monitor, &data->ph[0], CREATE);
	else
		return ;
	if (data->nb_ph == 1)
	{	
		handle_thread(data, &data->data_thread, &mr_lonely, &data->ph[0], CREATE);
		handle_thread(data, &data->data_thread, NULL, NULL, DETACH);
	}
	else
	{
		i = -1;	
		while(++i < data->nb_ph)
			handle_thread(data, &data->ph[i].ph_thread, &dinner_routine, &data->ph[i], CREATE);
		my_usleep(data, 1000000);
	}
	printf("left creation loop\n");
	i = -1;
	while(++i < (data)->nb_ph)
	{
		handle_thread(data, &data->ph[i].ph_thread, NULL, NULL, JOIN);
		printf("thread for philo %d was executed\n", data->ph[i].ph_id);
	}
	handle_mutex(data, &data->acc_mtx, UNLOCK);
}
