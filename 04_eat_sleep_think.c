/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_eat_sleep_think.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:44:36 by root              #+#    #+#             */
/*   Updated: 2025/02/24 11:59:32 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myphilo.h"

void	handle_forks(t_philo *philo, t_fork_action action)
{
	if (action == TAKE)
	{
		handle_mutex(philo->data, &philo->l_fork_mtx, LOCK);
		print_ph_status(philo, TOOK_FORK);
		handle_mutex(philo->data, &philo->r_fork_mtx, LOCK);
		print_ph_status(philo, TOOK_FORK);
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
	
	printf(YLL"entered ph_eating for philo %d\n"RES, philo->ph_id);
	handle_forks(philo, TAKE);
	handle_mutex(philo->data, &philo->acc_mtx_ph, LOCK);
	philo->ph_eating = true;
	printf(YLL"philo %d is eating\n"RES, philo->ph_id);
	time_left = philo->data->time_to_die + get_time(philo->data, MILLISECONDS);
	set_time_var(philo->data, &philo->acc_mtx_ph, &philo->time_left, time_left);
	print_ph_status(philo, EATING);
	philo->meal_count++;
	my_usleep(philo->data, philo->data->time_to_eat);
	philo->ph_eating = false;
	printf(YLL"philo %d has finished mean %d\n"RES, philo->ph_id, philo->meal_count);
	handle_mutex(philo->data, &philo->acc_mtx_ph, UNLOCK);
	handle_forks(philo, DROP);
}

void	ph_sleeping(t_philo *philo)
{
	printf(YLL"entered ph_sleeping for philo %d\n"RES, philo->ph_id);
	handle_mutex(philo->data, &philo->acc_mtx_ph, LOCK);
	print_ph_status(philo, SLEEPING);
	my_usleep(philo->data, philo->data->time_to_sleep);
	handle_mutex(philo->data, &philo->acc_mtx_ph, UNLOCK);
}

void	ph_thinking(t_philo *philo)
{
	printf(YLL"entered ph_thinking for philo %d\n"RES, philo->ph_id);
	handle_mutex(philo->data, &philo->acc_mtx_ph, LOCK);
	print_ph_status(philo, THINKING);
}
