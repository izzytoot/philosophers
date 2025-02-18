/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_time_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:47:50 by root              #+#    #+#             */
/*   Updated: 2025/02/18 18:39:09 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_program *program, t_time	time_unit)
{
	struct timeval	current_time;

	if(gettimeofday(&current_time, NULL) != 0)
		print_error_and_exit(program, RED"Failed getting timeofday."RESET, 2);
	if (time_unit == MICROSSECONDS)
		return ((current_time.tv_sec * 1000000) + (current_time.tv_usec / 1000)); //why this sum?
	else if (time_unit == MILLISECONDS)
		return ((current_time.tv_sec * 1000) + current_time.tv_usec);
	else if (time_unit == SECONDS)
		return (current_time.tv_sec + (current_time.tv_usec / 1000000));
	else
		print_error_and_exit(program, RED"Error! Invalid time unit."RESET, 2);
	return (0);
}

void	set_long_time(t_program *program, t_mtx *mtx, long *result, long time)
{
	handle_mutex(program, mtx, LOCK);
	*result = time;
	handle_mutex(program, mtx, UNLOCK);
}

void	timming_to_eat(t_philo *philo)
{
	if(philo->id % 2 == 0)
		my_usleep(philo->program, 30000);
	else
		philo_thinking(philo);
}

void	my_usleep(t_program *program, long sleep_time)
{
	long	start;
	long	time_passed;
	long	time_remaining;

	start = get_time(program, MICROSSECONDS);
	while ((get_time(program, MICROSSECONDS) - start) < sleep_time)
	{
		if (true_or_false(program, &program->access_mutex, &program->time_is_up))
			break ;
		time_passed = get_time(program, MICROSSECONDS) - start;
		time_remaining = sleep_time - time_passed;
		if (time_remaining > 10000)
			usleep(time_remaining / 2);
		else
			while ((get_time(program, MICROSSECONDS) - start) < sleep_time)
				;
	}
}