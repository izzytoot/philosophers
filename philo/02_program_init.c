/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_program_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:02:13 by root              #+#    #+#             */
/*   Updated: 2025/02/13 16:23:31 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_mutex_error(t_program *program, int status, t_code code)
{
	if (status != 0 && (code == LOCK || code == UNLOCK
			|| code == INIT || code == DESTROY))
	{
		print_error_and_exit(program, RED"Error with Mutex.\n"RESET, 2);
		return ;
	}
}

void	handle_mutex(t_program *program, t_mtx *mtx, t_code code)
{
	if (code == LOCK)
		check_mutex_error(program, pthread_mutex_lock(mtx), code);
	else if (code == UNLOCK)
		check_mutex_error(program, pthread_mutex_unlock(mtx), code);
	else if (code == INIT)
		check_mutex_error(program, pthread_mutex_init(mtx, NULL), code);
	else if (code == DESTROY)
		check_mutex_error(program, pthread_mutex_destroy(mtx), code);
	else
		print_error_and_exit(program, RED"Error! Wrong mutex code.\n"RESET, 2);
}
/*
void	handle_thread(t_program *program, pthread_t *thread_info, void *(*foo)(void *), void *t_data, t_thread_code code)
{
	if (code == CREATE)
		//check_thread_error(pthread_create());
	else if (code == JOIN)
		//check_thread_error(pthread_join());
	else if (code == DETACH)
		//check_thread_error(pthread_detach());
	else
		print_error_and_exit(&program, RED"Error! Wrong thread code.\n"RESET, 2);
}
*/

void	assign_forks(t_program * program, t_philo *philo, t_fork *fork, int i)
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

void	philo_init(t_program *program)
{
		int	i;
		t_philo philo;
		
		i = 0;
		while(i < program->nb_philos)
		{
			philo = program->philos[i];
			philo.id = i + 1;
			philo.nb_meals = 0;
			philo.max_meals_reached = false;
			handle_mutex(program, &philo.mutex_philo, INIT);
			assign_forks(program, &philo, program->forks, i);
			i++;
		}
}

void	program_init(t_program *program)
{
	int	i;

	i = 0;
	program->philos = malloc(program->nb_philos * sizeof (t_philo)); // ver se faz sentido por 200
	program->forks = malloc(program->nb_philos * sizeof (t_fork));
	handle_mutex(program, &program->write_mutex, INIT);
	handle_mutex(program, &program->access_mutex, INIT);
	while(i < program->nb_philos)
	{
		handle_mutex(program, &program->forks[i].mutex_fork, INIT);
		program->forks[i].fork_id = i;
		i++;
	}
	philo_init(program);
}

