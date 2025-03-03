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

void	wait_threads(t_data *data)
{
	while (!get_bool(data, &data->data_mtx, &data->threads_ready))
		;
}

void	hold_your_horses(t_philo *philo)
{
	if (philo->data->nb_ph % 2 == 0)
	{
		if (philo->ph_id % 2 == 0)
			my_usleep(philo->data, 30000);
	}
	else
	{
		if (philo->ph_id % 2)
			ph_thinking(philo, true);
	}
}

void	ph_eating(t_philo *philo)
{
	long	current_time;

	handle_forks(philo, TAKE);
	current_time = get_time(philo->data, MILLISECONDS);
	set_time_var(philo->data, &philo->ph_mtx, &philo->last_meal, current_time);
	set_bool_var(philo->data, &philo->ph_mtx, &philo->ph_eating, true);
	philo->meal_count++;
	print_ph_status(philo, EATING);
	my_usleep(philo->data, philo->data->time_to_eat);
	if ((philo->data->max_meals > 0)
		&& philo->meal_count >= philo->data->max_meals)
	{
		set_bool_var(philo->data, &philo->ph_mtx, &philo->ph_full, true);
		handle_mutex(philo->data, &philo->data->data_mtx, LOCK);
		philo->data->nb_ph_full++;
		handle_mutex(philo->data, &philo->data->data_mtx, UNLOCK);
	}
	set_bool_var(philo->data, &philo->ph_mtx, &philo->ph_eating, false);
	handle_forks(philo, DROP);
}

void	handle_forks(t_philo *philo, t_fork_action action)
{
	if (action == TAKE)
	{
		if (philo->ph_id % 2 == 0)
		{
			handle_mutex(philo->data, philo->r_fork_mtx, LOCK);
			print_ph_status(philo, TOOK_FORK);
			handle_mutex(philo->data, philo->l_fork_mtx, LOCK);
			print_ph_status(philo, TOOK_FORK);
		}
		else
		{
			handle_mutex(philo->data, philo->l_fork_mtx, LOCK);
			print_ph_status(philo, TOOK_FORK);
			handle_mutex(philo->data, philo->r_fork_mtx, LOCK);
			print_ph_status(philo, TOOK_FORK);
		}
	}
	else if (action == DROP)
	{
		handle_mutex(philo->data, philo->l_fork_mtx, UNLOCK);
		handle_mutex(philo->data, philo->r_fork_mtx, UNLOCK);
	}
}

void	ph_thinking(t_philo *philo, bool check)
{
	long	time_to_think;

	if (!check)
		print_ph_status(philo, THINKING);
	if (philo->data->nb_ph % 2 == 0)
		return ;
	time_to_think = (philo->data->time_to_eat * 2) - philo->data->time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	my_usleep(philo->data, time_to_think * 0.46);
	return ;
}
