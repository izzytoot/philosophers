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

void    wait_threads(t_data *data)
{
    while(!get_bool(data, &data->data_mtx, &data->threads_ready));
}
/*
int	pre_dinner_check(t_philo *philo)
{
	long	time_passed;
	long	time_to_die;
	
	time_passed = get_time(philo->data, MILLISECONDS) - get_time_var(philo->data, &philo->ph_mtx, &philo->last_meal);
   	time_to_die = (get_time_var(philo->data, &philo->ph_mtx, &philo->data->time_to_die));
	if (!end_dinner(philo->data, NULL, MEAL_END) && !end_dinner(philo->data, philo, PH_FULL))
	{
		if (time_passed >= time_to_die && !philo->ph_eating) // ver se é preciso check ph_eating
		{
			set_bool_var(philo->data, &philo->ph_mtx, &philo->ph_dead, true);
			print_ph_status(philo, DIED);
			set_bool_var(philo->data, &philo->data->data_mtx, &philo->data->end_dinner, true);
			return (1);
		}
	}
	return(0);
}
*/
void	handle_forks(t_philo *philo, t_fork_action action)
{
	if (action == TAKE)
	{
		if (philo->ph_id % 2 == 0)
		{
			my_usleep(philo->data, 500);
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

void	ph_eating(t_philo *philo)
{
	//long	current_time;

	//current_time = get_time(philo->data, MILLISECONDS);
	handle_forks(philo, TAKE);
	handle_mutex(philo->data, &philo->ph_mtx, LOCK);
	philo->last_meal = get_time(philo->data, MILLISECONDS);
	philo->ph_eating = true;
	philo->meal_count++;
	print_ph_status(philo, EATING);
	my_usleep(philo->data, philo->data->time_to_eat);
	if (philo->data->av5 && philo->meal_count >= philo->data->max_meals)
	{
		philo->ph_full = true;
		printf(GR"philo %d is full at %d meals\n"RES, philo->ph_id, philo->meal_count);
		philo->data->nb_ph_full++;
	}
	philo->ph_eating = false; //check if needed
	handle_mutex(philo->data, &philo->ph_mtx, UNLOCK);
	handle_forks(philo, DROP);
	if (!end_dinner(philo->data, philo, PH_FULL))
	{
		print_ph_status(philo, SLEEPING);
		my_usleep(philo->data, philo->data->time_to_sleep);
	}	
}
