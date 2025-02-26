/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_time_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:47:50 by root              #+#    #+#             */
/*   Updated: 2025/02/26 18:20:37 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_data *data, t_time time_unit)
{
	struct timeval	current_time;

	if(gettimeofday(&current_time, NULL))
		error_and_exit(data, RED ERR_TIME RES, 2);
	if (time_unit == MICROSECONDS)
		return ((current_time.tv_sec * 1000000) + (current_time.tv_usec));
	else if (time_unit == MILLISECONDS)
		return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
	else if (time_unit == SECONDS)
		return (current_time.tv_sec);
	error_and_exit(data, RED ERR_TIME2 RES, 2);
	return (0);
}

void	set_time_var(t_data *data, t_mtx *mtx, long *result, long time)
{
	handle_mutex(data, mtx, LOCK);
	*result = time;
	handle_mutex(data, mtx, UNLOCK);
}

void	my_usleep(t_data *data, long sleep_time)
{
	long	start;
	long	time_passed;
	long	remaining;
	
	start = get_time(data, MICROSECONDS);
	while (get_time(data, MICROSECONDS) - start < sleep_time)
	{
		if (end_dinner(data))
			break ;
		time_passed = get_time(data, MICROSECONDS) - start;
		remaining = sleep_time - time_passed;
 		if (remaining > 1000)
        	usleep(remaining / 2);
		else
			while(get_time(data, MICROSECONDS) - start < sleep_time)
				;
	}
}
