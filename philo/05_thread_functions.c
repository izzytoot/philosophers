/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_thread_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:25:48 by root              #+#    #+#             */
/*   Updated: 2025/02/18 18:03:00 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
void	lonely_philo(t_philo philo)
{
	
}
*/

void	*lets_feast(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(!true_or_false(philo->program, &philo->program->access_mutex, &philo->program->all_threads_active))
		;
	set_long_time(philo->program, &philo->program->access_mutex, &philo->started_dinning_at, get_time(philo->program, MILLISECONDS));
	count_active_philos(philo->program, &philo->program->access_mutex, philo->program->nb_philos_active);
	timming_to_eat(philo);  // perceber melhor
	while(!true_or_false(philo->program, &philo->program->access_mutex, &philo->program->time_is_up))
	{
		if(true_or_false(philo->program, &philo->program->access_mutex, &philo->max_meals_reached))
			break;
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	return (NULL);
}


void	*death_confirm(void *arg)
{
	int	i;
	t_program *program;
	
	program = (t_program *)arg;
	while(!true_or_false(program, &program->access_mutex, &program->all_threads_active))
		;
	while(!true_or_false(program, &program->access_mutex, &program->time_is_up))
	{
		i = 0;
		while (i < program->nb_philos)
		{
			if (philo_died(program->philos[i]))
			{
				change_bool_value(program, &program->access_mutex, &program->time_is_up, true);
				print_ph_status(program->philos[i], DIED);
			}
			i++;
		}
	}
	return (NULL);
}

