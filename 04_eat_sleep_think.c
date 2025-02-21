/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_eat_sleep_think.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:44:36 by root              #+#    #+#             */
/*   Updated: 2025/02/21 19:58:56 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myphilo.h"

void	handle_forks(t_philo *philo, t_fork_action action)
{
	if (action == TAKE)
	{
		handle_mutex(philo->data, &philo->l_fork_mtx, LOCK);
		print_ph_status(philo->data, TOOK_FORK);
		handle_mutex(philo->data, &philo->r_fork_mtx, LOCK);
		print_ph_status(philo->data, TOOK_FORK);
	}
	else if (action == DROP)
	{
		handle_mutex(philo->data, &philo->l_fork_mtx, UNLOCK);
		handle_mutex(philo->data, &philo->r_fork_mtx, UNLOCK);
	}
}
void	ph_eating(t_philo *philo)
{
	__uint64_t	time_left;
	
	handle_forks(philo, TAKE);
	handle_mutex(philo->data, &philo->acc_mtx_ph, LOCK);
	philo->ph_eating = true;
	time_left = philo->data->time_to_die + get_time(philo->data, MILLISECONDS);
	set_time_var(philo->data, &philo->acc_mtx_ph, &philo->time_left, time_left);
	print_ph_status(philo->data, EATING);
	philo->meal_count++;
	my_usleep(philo->data, philo->data->time_to_eat);
	philo->ph_eating = false;
	handle_mutex(philo->data, &philo->acc_mtx_ph, UNLOCK);
	handle_forks(philo, DROP);
}

void	ph_sleeping(t_philo *philo)
{
	handle_mutex(philo->data, &philo->acc_mtx_ph, LOCK);
	print_ph_status(philo->data, SLEEPING);
	my_usleep(philo->data, philo->data->time_to_sleep);
	handle_mutex(philo->data, &philo->acc_mtx_ph, UNLOCK);
}

void	ph_thinking(t_philo *philo)
{
	handle_mutex(philo->data, &philo->acc_mtx_ph, LOCK);
	print_ph_status(philo->data, THINKING);
}
