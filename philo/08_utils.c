/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:46:34 by root              #+#    #+#             */
/*   Updated: 2025/02/18 14:16:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	change_bool_value(t_program *program, t_mtx *mtx, bool *boolean, bool value)
{
	handle_mutex(program, mtx, LOCK);
	*boolean = value;
	handle_mutex(program, mtx, UNLOCK);
}

bool	true_or_false(t_program *program, t_mtx *mtx, bool *variable)
{
	bool	result;
	
	handle_mutex(program, mtx, LOCK);
	result = *variable;
	handle_mutex(program, mtx, UNLOCK);
	return (result);
}

void	count_active_philos(t_program *program, t_mtx *mtx, int counter)
{
	handle_mutex(program, mtx, LOCK);
	counter++;
	handle_mutex(program, mtx, UNLOCK);
}

void	print_ph_status(t_philo *philo, t_ph_status status)
{
	long time_passed;

	time_passed = (get_time(philo->program, MILLISECONDS))- (philo->program->starting_time);
	if (!true_or_false(philo->program, &philo->program->access_mutex, philo->program->time_ended))
	{
		handle_mutex(philo->program, &philo->program->access_mutex, LOCK);
		if (status == TOOK_FORK)
			printf("%ld"GREEN" %d has taken a fork"RESET" %s", time_passed, philo->id, "U+1F374
");
		else if (status == EATING)
			printf("%ld"GREEN" %d is eating"RESET" %s", time_passed, philo->id, "U+1F60B");
		else if (status == SLEEPING)
			printf("%ld"GREEN" %d is sleeping"RESET" %s", time_passed, philo->id, "U+1F634");
		else if (status == THINKING)
			printf("%ld"GREEN" %d is thinking"RESET" %s", time_passed, philo->id, "U+1F914");
		else if (status == DIED)
			printf("%ld"RED" %d died"RESET" %s", time_passed, philo->id, "U+2620");

	}
	handle_mutex(philo->program, &philo->program->access_mutex, UNLOCK);

}
