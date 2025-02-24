/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_time_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:47:50 by root              #+#    #+#             */
/*   Updated: 2025/02/24 19:23:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myphilo.h"

__uint64_t	get_time(t_data *data, t_time time_unit)
{
	struct timeval	current_time;

	if(gettimeofday(&current_time, NULL))
		error_and_exit(data, RED ERR_TIME RES, 2);
	if (time_unit == MICROSECONDS)
		return ((current_time.tv_sec * 1000000ULL) + (current_time.tv_usec));
	else if (time_unit == MILLISECONDS)
		return ((current_time.tv_sec * 1000000ULL) + (current_time.tv_usec + 500 / 1000));
	else if (time_unit == SECONDS)
		return (current_time.tv_sec);
	error_and_exit(data, RED ERR_TIME2 RES, 2);
	return (0);
}
/*
void	set_time_var(t_data *data, t_mtx *mtx, __uint64_t *result, __uint64_t time)
{
//	handle_mutex(data, mtx, LOCK);
	*result = time;
//	handle_mutex(data, mtx, UNLOCK);
}
*/
void	my_usleep(t_data *data, __uint64_t sleep_time)
{
	__uint64_t	start;
	__uint64_t	current;
	
	start = get_time(data, MICROSECONDS);
	current = start;
	
	while ((current - start) < sleep_time)
	{
 		usleep(500);
        current = get_time(data, MICROSECONDS);
	}
}