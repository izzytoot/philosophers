/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:46:34 by root              #+#    #+#             */
/*   Updated: 2025/02/26 16:58:02 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myphilo.h"

void	handle_mutex(t_data *data, t_mtx *mtx, t_code code)
{
	if (code == INIT)
	{
		if (pthread_mutex_init(mtx, NULL) != 0)
			error_and_exit(data, RED ERR_MTX_INIT RES, 2);
	}
	else if (code == LOCK)
	{	
		if (pthread_mutex_lock(mtx) != 0)
			error_and_exit(data, RED ERR_MTX_LOCK RES, 2);
	}
	else if (code == UNLOCK)
	{
		if (pthread_mutex_unlock(mtx) != 0)
			error_and_exit(data, RED ERR_MTX_UNLOCK RES, 2);
	}
	else if (code == DESTROY)
	{
		if (pthread_mutex_destroy(mtx) != 0)
			error_and_exit(data, RED ERR_MTX_DESTR RES, 2);
	}
	else
		error_and_exit(data, RED ERR_MTX_CODE RES, 2);
}

void	handle_thread(t_data *data, pthread_t *thread, void *(*function)(void *), void *t_data, t_code code)
{
	if (code == CREATE)
	{	
		if (pthread_create(thread, NULL, function, t_data) != 0)
			error_and_exit(data, RED ERR_TH_CR RES, 2);
	}
	else if (code == JOIN)
	{	
		if (pthread_join(*thread, NULL) != 0)
			error_and_exit(data, RED ERR_TH_J RES, 2);
	}
	else if (code == DETACH)
	{
		if (pthread_detach(*thread) != 0)
			error_and_exit(data, RED ERR_TH_DET RES, 2);
	}	
	else
		error_and_exit(data, RED ERR_TH_CODE RES, 2);
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

//WITH EMOJIS AND COLORS                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
void	print_ph_status(t_philo *philo, t_ph_status status)
{
	long	current_time;
	long	time_passed;
	
 	current_time = get_time(philo->data, MILLISECONDS);
	time_passed =  current_time - philo->data->start_meal_time;
	handle_mutex(philo->data, &philo->data->write_mtx, LOCK);
	if (status == TOOK_FORK && !end_dinner(philo->data))
		printf("%-6ld"YLL" %d has taken fork"RES" %s\n", time_passed, philo->ph_id, "\U0001f374");
	else if (status == EATING && !end_dinner(philo->data))
		printf("%-6ld"GR" %d is eating"RES" %s\n", time_passed, philo->ph_id, "\U0001f60B");
	else if (status == SLEEPING && !end_dinner(philo->data))
		printf("%-6ld"YLL" %d is sleeping"RES" %s\n", time_passed, philo->ph_id, "\U0001f634");
	else if (status == THINKING && !end_dinner(philo->data))
		printf("%-6ld"YLL" %d is thinking"RES" %s\n", time_passed, philo->ph_id, "\U0001f914");
	else if (status == DIED && !end_dinner(philo->data))
		printf("%-6ld"RED" %d died"RES"%s\n", time_passed, philo->ph_id, "\U0002f620");
	handle_mutex(philo->data, &philo->data->write_mtx, UNLOCK);
}
/*
void	print_ph_status(t_philo *philo, t_ph_status status)
{
	long time_passed;

	time_passed = (get_time(philo->program, MILLISECONDS)) - (philo->program->starting_time);
	if (!true_or_false(philo->program, &philo->program->access_mutex, &philo->program->time_is_up))
	{
		handle_mutex(philo->program, &philo->program->access_mutex, LOCK);
		if (status == TOOK_FORK)
			printf("%-6ld %d has taken a fork\n", time_passed, philo->id);
		else if (status == EATING)
			printf("%-6ld"G" %d is eating\n"RES, time_passed, philo->id);
		else if (status == SLEEPING)
			printf("%-6ld %d is sleeping\n"RES, time_passed, philo->id);
		else if (status == THINKING)
			printf("%-6ld %d is thinking\n"RES, time_passed, philo->id);
		else if (status == DIED)
			printf("%-6ld"R" %d died\n"RES, time_passed, philo->id);

	}
	handle_mutex(philo->program, &philo->program->access_mutex, UNLOCK);

}
*/
