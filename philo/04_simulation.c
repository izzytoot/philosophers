/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:27:17 by root              #+#    #+#             */
/*   Updated: 2025/02/17 12:33:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_simulation(t_program **program)
{
	int	i;

	i = 0;
	if((*program)->max_meals == 0)
		return ;
	if((*program)->nb_philos == 1)
		handle_thread(*program, (*program)->philos[0]->philo_thread, lonely_philo, (*program)->philos[0], CREATE)
	else
	{
		while (i++ < (*program)->nb_philos)
			handle_thread(*program, (*program)->philos[i]->philo_thread, group_philos, (*program)->philos[i], CREATE);
	}
	
}

handle_thread(t_program *program, pthread_t *thread_info, void *(*foo)(void *), void *t_data, t_code code)