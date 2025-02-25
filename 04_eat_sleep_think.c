/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_eat_sleep_think.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:44:36 by root              #+#    #+#             */
/*   Updated: 2025/02/25 19:50:27 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myphilo.h"

void    wait_threads(t_data *data)
{
    while(data->threads_ready == false);
//   while(!get_bool(data, &data->acc_mtx, &data->threads_ready));

}

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
	}
}
int	ph_eating(t_philo *philo)
{
	__uint64_t	current_time;
	
	wait_threads(philo->data);
	handle_forks(philo, TAKE);
	set_bool_var(philo->data, &philo->ph_mtx, &philo->ph_eating, true);
	current_time = get_time(philo->data, MILLISECONDS);
	set_time_var(philo->data, &philo->ph_mtx, &philo->last_meal, current_time);
	print_ph_status(philo, EATING);
	handle_mutex(philo->data, &philo->ph_mtx, LOCK);
	my_usleep(philo->data, philo->data->time_to_eat);
	philo->meal_count++;
	if (philo->meal_count >= philo->data->max_meals)
	{
		philo->ph_full = true;
		philo->data->nb_ph_full++;
	}
	philo->ph_eating = false;
	handle_forks(philo, DROP);
	my_usleep(philo->data, philo->data->time_to_sleep);
	handle_mutex(philo->data, &philo->ph_mtx, UNLOCK);
	return (0);
}
