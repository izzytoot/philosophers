/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_program_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:02:13 by root              #+#    #+#             */
/*   Updated: 2025/02/11 18:39:14 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	handle_mutex(t_program *program, t_mtx *mtx, t_mutex_code code)
{
	if (code == LOCK)
		check_mutex_error(pthread_mutex_lock(mtx), code);
	else if (code == UNLOCK)
		check_mutex_error(pthread_mutex_lock(mtx), code);
	else if (code == INIT)
		check_mutex_error(pthread_mutex_init(mtx, NULL), code);
	else if (code == DESTROY)
		check_mutex_error(pthread_mutex_destroy(mtx), code);
	else
		print_error_and_exit(&program, RED"Error! Wrong mutex code.\n"RESET, 2);
}

void	handle_thread(pthread_t *thread_info, void *(*foo)(void *), void *t_data, t_ftcode ftcode)
	else if (code == CREATE)
		check_mutex_error(pthread_mutex_init(mtx, NULL), code);
	else if (code == JOIN)
	else if (code == DETACH)
	
	
void	program_init(t_program *program)
{
	int	i;

	i = 0;
	program->forks = malloc(program->nb_philos * sizeof (t_fork));
	program->philos = malloc(program->nb_philos * sizeof (t_philo));
	handle_mutex(&program->)
	while(i < program->nb_philos)
	{
		handle_mutex(&program, &program->forks[i].mutex_fork, INIT);
		program->forks[i].fork_id = i;
	}
}

void	start_simulation(t_program	*program)
{
	
}