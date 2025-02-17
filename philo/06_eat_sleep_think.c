/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_eat_sleep_think.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:44:36 by root              #+#    #+#             */
/*   Updated: 2025/02/17 19:48:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(t_philo *philo)
{
	
}

void	philo_sleeping(t_philo *philo)
{
	print_status();
	usleep(philo->program->time_to_sleep);
}

void	philo_thinking(t_philo *philo)
{
	
}
