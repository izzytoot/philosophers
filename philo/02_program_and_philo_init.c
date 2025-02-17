/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_program_and_philo_init.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:02:13 by root              #+#    #+#             */
/*   Updated: 2025/02/14 19:47:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	assign_forks(t_program *program, t_philo *philo, t_fork *fork, int i)
{
	int	nb_philos;

	nb_philos = program->nb_philos;
	if (philo->id % 2 == 0)
	{
		philo->left_fork = &fork[i];
		philo->right_fork = &fork[(i + 1) % nb_philos];
	}
	else
	{
		philo->left_fork = &fork[(i + 1) % nb_philos];
		philo->right_fork = &fork[i];
	}
}

void	philo_init(t_program **program, t_philo **philo)
{
		int	i;
		
		i = 0;
		while(i < (*program)->nb_philos)
		{
			(*program)->philos[i] = malloc(sizeof(t_philo));
			if (!(*program)->philos[i])
				print_error_and_exit(*program, RED"Error allocating memory.\n"RESET, 2);
			(*philo) = (*program)->philos[i];
			(*philo)->id = i + 1;
			(*philo)->nb_meals = 0;
			(*philo)->max_meals_reached = false;
			handle_mutex(*program, &(*philo)->mutex_philo, INIT);
			assign_forks(*program, *philo, (*program)->forks, i);
			i++;
		}
}

void	program_init(t_program **program, t_philo **philo)
{
	int	i;

	i = 0;
	(*program)->philos = malloc((*program)->nb_philos * sizeof (t_philo *)); // ver se faz sentido por 200
	if (!(*program)->philos)
			print_error_and_exit(*program, RED"Error allocating memory.\n"RESET, 2);
	(*program)->forks = malloc((*program)->nb_philos * sizeof (t_fork));
	if (!(*program)->forks)
			print_error_and_exit(*program, RED"Error allocating memory.\n"RESET, 2);
	handle_mutex(*program, &(*program)->write_mutex, INIT); //perceber melhor
	handle_mutex(*program, &(*program)->access_mutex, INIT); //perceber melhor
	while(i < (*program)->nb_philos)
	{
		handle_mutex(*program, &(*program)->forks[i].mutex_fork, INIT);
		(*program)->forks[i].fork_id = i;
		i++;
	}
	philo_init(&(*program), &(*philo));
}

