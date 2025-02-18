/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_eat_sleep_think_die.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:44:36 by root              #+#    #+#             */
/*   Updated: 2025/02/18 18:38:52 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(t_philo *philo)
{
	handle_mutex(philo->program, &philo->fork1->mutex_fork, LOCK);
	print_ph_status(philo, TOOK_FORK);
	handle_mutex(philo->program, &philo->fork2->mutex_fork, LOCK);
	print_ph_status(philo, TOOK_FORK);
	set_long_time(philo->program, &philo->program->access_mutex, &philo->started_dinning_at, get_time(philo->program, MILLISECONDS));
	philo->nb_meals++;
	print_ph_status(philo, EATING);
	my_usleep(philo->program, philo->program->time_to_eat);
	if(philo->program->max_meals && (philo->nb_meals == philo->program->max_meals))
		change_bool_value(philo->program, &philo->program->access_mutex, &philo->max_meals_reached, true);
	handle_mutex(philo->program, &philo->fork1->mutex_fork, UNLOCK);
	handle_mutex(philo->program, &philo->fork2->mutex_fork, UNLOCK);
}

void	philo_sleeping(t_philo *philo)
{
	print_ph_status(philo, SLEEPING);
	my_usleep(philo->program, philo->program->time_to_sleep);
}

void	philo_thinking(t_philo *philo)
{
	print_ph_status(philo, THINKING);
	if (philo->program->nb_philos % 2 == 0)
		return ;
	my_usleep(philo->program, philo->program->time_to_think);
}

bool	philo_died(t_philo	*philo)
{
	long	time_passed;
	
	if (true_or_false(philo->program, &philo->program->access_mutex, &philo->max_meals_reached))
		return (false);
	time_passed = get_time(philo->program, MILLISECONDS) - philo->started_dinning_at;
	if (time_passed >= philo->program->time_to_die)
		return (true);
	return (false);
}