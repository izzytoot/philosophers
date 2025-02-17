/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_thread_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:25:48 by root              #+#    #+#             */
/*   Updated: 2025/02/17 19:46:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
void	lonely_philo(t_philo philo)
{
	
}
*/

void	*lets_feast(t_philo *philo)
{
	while(!true_or_false(philo->program, &philo->program->access_mutex, philo->program->all_threads_active))
	set_long_time(philo->program, &philo->program->access_mutex, &philo->started_dinning_at, get_time(philo->program, MILLISECONDS));
	count_active_threads(philo->program, &philo->program->access_mutex, &philo->program->nb_philos_active);
	timming_to_eat(philo);  // perceber melhor
	while(!true_or_false(philo->program, &philo->program->access_mutex, philo->program->time_ended))
	{
		if(true_or_false(philo->program, &philo->program->access_mutex, philo->max_meals_reached))
			break;
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
}
/*
void	death_confirm(t_program *program)
{
	
}
*/
