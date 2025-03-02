/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_routine_actions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:44:36 by root              #+#    #+#             */
/*   Updated: 2025/02/27 17:03:55 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    wait_threads(t_data *data)
{
    while(!get_bool(data, &data->data_mtx, &data->threads_ready))
		;
}

void	handle_forks(t_philo *philo, t_fork_action action)
{
	if (action == TAKE)
	{
		/*
		if (philo->ph_id % 2 != 0)
		{
			my_usleep(philo->data, 5000);
			handle_mutex(philo->data, philo->r_fork_mtx, LOCK);
			print_ph_status(philo, TOOK_FORK);
			handle_mutex(philo->data, philo->l_fork_mtx, LOCK);
			print_ph_status(philo, TOOK_FORK);		
		}
		else
		{
		*/
			handle_mutex(philo->data, philo->l_fork_mtx, LOCK);
			print_ph_status(philo, TOOK_FORK);
			handle_mutex(philo->data, philo->r_fork_mtx, LOCK);
			print_ph_status(philo, TOOK_FORK);		
		//}
	}
	else if (action == DROP)
	{
		handle_mutex(philo->data, philo->l_fork_mtx, UNLOCK);
		handle_mutex(philo->data, philo->r_fork_mtx, UNLOCK);
	}
}

void	ph_eating(t_philo *philo)
{
	handle_forks(philo, TAKE);
	handle_mutex(philo->data, &philo->ph_mtx, LOCK);
	philo->ph_eating = true; //check if needed
	philo->meal_count++;
	print_ph_status(philo, EATING);
	philo->last_meal = get_time(philo->data, MILLISECONDS);
	my_usleep(philo->data, philo->data->time_to_eat);
	if (philo->data->av5 && philo->meal_count >= philo->data->max_meals)
	{
		philo->ph_full = true;
		philo->data->nb_ph_full++;
	}
	philo->ph_eating = false; //check if needed
	handle_mutex(philo->data, &philo->ph_mtx, UNLOCK);
	handle_forks(philo, DROP);
}

void	ph_thinking(t_philo *philo, bool check)
{
	long time_to_think;

	if (!check)
		print_ph_status(philo, THINKING);
	if (philo->data->nb_ph % 2 == 0)
		return ;
	time_to_think = (get_time_var(philo->data, &philo->ph_mtx, &philo->data->time_to_eat) * 2) - get_time_var(philo->data, &philo->ph_mtx, &philo->data->time_to_sleep);
	if (time_to_think < 0)
		time_to_think = 0;
	my_usleep(philo->data, time_to_think * 0.46);
	return ;
}