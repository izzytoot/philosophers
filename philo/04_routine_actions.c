/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_routine_actions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:44:36 by root              #+#    #+#             */
/*   Updated: 2025/02/26 18:20:30 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    wait_threads(t_data *data)
{
    while(!get_bool(data, &data->data_mtx, &data->threads_ready));
}

int	pre_dinner_check(t_philo *philo)
{
	long	time_passed;
	
	if(!end_dinner(philo->data))
	{
		time_passed = get_time(philo->data, MILLISECONDS) - philo->last_meal;
   		if (time_passed >= philo->data->time_to_die && !end_dinner(philo->data) && get_bool(philo->data, &philo->ph_mtx, &philo->ph_eating)) // ver se é preciso check ph_eating
		{
			set_bool_var(philo->data, &philo->ph_mtx, &philo->ph_dead, true);
    	  	print_ph_status(philo, DIED);
			set_bool_var(philo->data, &philo->data->data_mtx, &philo->data->end_dinner, true);
			return (1);
		}
	}
	if(get_bool(philo->data, &philo->ph_mtx, &philo->data->all_ph_full) && !end_dinner(philo->data))
	{
		printf("philos are full!\n"); //to delete
		set_bool_var(philo->data, &philo->data->data_mtx, &philo->data->end_dinner, true);
		return (1);
	}
	return(0);
}

void	handle_forks(t_philo *philo, t_fork_action action)
{
	if (action == TAKE)
	{
		{
			if (philo->ph_id % 2 == 0)
				my_usleep(philo->data, 500);
			if (philo->ph_id % 2 == 0)
			{
				handle_mutex(philo->data, philo->r_fork_mtx, LOCK);
				print_ph_status(philo, TOOK_FORK);
				handle_mutex(philo->data, philo->l_fork_mtx, LOCK);
				print_ph_status(philo, TOOK_FORK);		
			}
			else
			if (philo->ph_id)
			{
				handle_mutex(philo->data, philo->l_fork_mtx, LOCK);
				print_ph_status(philo, TOOK_FORK);
				handle_mutex(philo->data, philo->r_fork_mtx, LOCK);
				print_ph_status(philo, TOOK_FORK);		
			}
		}
	}
	else if (action == DROP)
	{
		handle_mutex(philo->data, philo->l_fork_mtx, UNLOCK);
		handle_mutex(philo->data, philo->r_fork_mtx, UNLOCK);
		print_ph_status(philo, SLEEPING);
	}
}

int	ph_eating(t_philo *philo)
{
	handle_forks(philo, TAKE);
	set_bool_var(philo->data, &philo->ph_mtx, &philo->ph_eating, true);
	print_ph_status(philo, EATING);
	handle_mutex(philo->data, &philo->ph_mtx, LOCK);
	my_usleep(philo->data, philo->data->time_to_eat);
	philo->meal_count++;
	if (philo->data->av5 && philo->meal_count >= philo->data->max_meals)
	{
		philo->ph_full = true;
		philo->data->nb_ph_full++;
	}
	philo->ph_eating = false;
	handle_mutex(philo->data, &philo->ph_mtx, UNLOCK);
	handle_forks(philo, DROP);
	my_usleep(philo->data, philo->data->time_to_sleep);
	return (0);
}
