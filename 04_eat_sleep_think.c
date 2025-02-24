/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_eat_sleep_think.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:44:36 by root              #+#    #+#             */
/*   Updated: 2025/02/24 19:27:40 by root             ###   ########.fr       */
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
		print_ph_status(philo, SLEEPING);
		my_usleep(philo->data, philo->data->time_to_sleep);
	}
}
int	ph_eating(t_philo *philo)
{
	__uint64_t	time_left;
	
	handle_forks(philo, TAKE);
//	handle_mutex(philo->data, &philo->acc_mtx_ph, LOCK);
	philo->ph_eating = true;
	time_left = philo->data->time_to_die + get_time(philo->data, MILLISECONDS);
	philo->time_left = time_left;
	//set_time_var(philo->data, &philo->acc_mtx_ph, &philo->time_left, time_left); - isto causa entrave e nao deixa sequencia continuar
	print_ph_status(philo, EATING);
//	handle_mutex(philo->data, &philo->acc_mtx_ph, UNLOCK);
	my_usleep(philo->data, philo->data->time_to_eat); //GETS STUCK
	philo->meal_count++;
	philo->ph_eating = false;
	if (philo->meal_count == philo->data->max_meals)
	{
		philo->ph_full = true;
		philo->data->nb_ph_full++;	
	}
	handle_forks(philo, DROP);
	return (0);
}
/*
void	ph_sleeping(t_philo *philo)
{
	handle_mutex(philo->data, &philo->acc_mtx_ph, LOCK);
	print_ph_status(philo, SLEEPING);
	my_usleep(philo->data, philo->data->time_to_sleep);
	handle_mutex(philo->data, &philo->acc_mtx_ph, UNLOCK);
}

void	ph_thinking(t_philo *philo)
{
	handle_mutex(philo->data, &philo->acc_mtx_ph, LOCK);
	print_ph_status(philo, THINKING);
	handle_mutex(philo->data, &philo->acc_mtx_ph, UNLOCK);
}
*/