/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_start_dinner_threads.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:27:17 by root              #+#    #+#             */
/*   Updated: 2025/02/17 18:12:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_dinner(t_program **program)
{
	int	i;

	i = 0;
	if((*program)->max_meals == 0)
		return ;
	if((*program)->nb_philos == 1)
		handle_thread(*program, (*program)->philos[0]->philo_thread, lonely_philo, (*program)->philos[0], CREATE);
	else
	{
		while (i < (*program)->nb_philos)
			handle_thread(*program, (*program)->philos[i++]->philo_thread, lets_feast, (*program)->philos[i], CREATE);
	}
	handle_thread(*program, (*program)->philo_death, death_confirm, *program, CREATE);
	(*program)->starting_time = get_time(program, MILLISECONDS);
	change_bool_value((*program), &(*program)->access_mutex, (*program)->all_threads_active, true);
	i = 0;
	while(i++ < (*program)->nb_philos)
			handle_thread(*program, (*program)->philos[i++]->philo_thread, NULL, NULL, JOIN);
	change_bool_value((*program), &(*program)->access_mutex, (*program)->time_ended, true);
	handle_thread(*program, (*program)->philo_death, NULL, NULL, JOIN);
}
