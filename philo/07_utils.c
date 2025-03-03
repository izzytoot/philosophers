/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:46:34 by root              #+#    #+#             */
/*   Updated: 2025/02/27 13:41:19 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_th(t_data *data, t_mtx *mtx, long *nb_th, long nb_ph)
{
	bool	ret;

	ret = false;
	handle_mutex(data, mtx, LOCK);
	if (*nb_th == nb_ph)
		ret = true;
	handle_mutex(data, mtx, UNLOCK);
	return (ret);
}

void	set_bool_var(t_data *data, t_mtx *mtx, bool *boolean, bool value)
{
	handle_mutex(data, mtx, LOCK);
	*boolean = value;
	handle_mutex(data, mtx, UNLOCK);
}

bool	get_bool(t_data *data, t_mtx *mtx, bool *boolean)
{
	bool	result;

	handle_mutex(data, mtx, LOCK);
	result = *boolean;
	handle_mutex(data, mtx, UNLOCK);
	return (result);
}

long	get_long(t_data *data, t_mtx *mtx, long *long_var)
{
	long	result;

	handle_mutex(data, mtx, LOCK);
	result = *long_var;
	handle_mutex(data, mtx, UNLOCK);
	return (result);
}

void	print_ph_status(t_philo *philo, t_ph_status status)
{
	long	current_time;
	long	time_passed;

	current_time = get_time(philo->data, MILLISECONDS);
	time_passed = current_time - philo->data->start_meal_time;
	if (!end_dinner(philo->data, NULL, MEAL_END))
	{
		handle_mutex(philo->data, &philo->data->write_mtx, LOCK);
		if (status == TOOK_FORK)
			printf("%-6ld %d has taken a fork\n", time_passed, philo->ph_id);
		else if (status == EATING)
			printf(GR"%-6ld %d is eating\n"RES, time_passed, philo->ph_id);
		else if (status == SLEEPING)
			printf("%-6ld %d is sleeping\n", time_passed, philo->ph_id);
		else if (status == THINKING)
			printf("%-6ld %d is thinking\n", time_passed, philo->ph_id);
		else if (status == DIED)
			printf(RED"%-6ld %d died\n"RES, time_passed, philo->ph_id);
		handle_mutex(philo->data, &philo->data->write_mtx, UNLOCK);
	}
}
