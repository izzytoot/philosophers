/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_handle_mutex_and_threads.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:27:00 by root              #+#    #+#             */
/*   Updated: 2025/02/17 12:00:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_thread_error(t_program *program, int thread_action, t_code code)
{
	if (thread_action != 0 && (code == CREATE || code == JOIN
			|| code == DETACH))
	{
		print_error_and_exit(program, RED"Error with Thread.\n"RESET, 2);
		return ;
	}
}
void	handle_mutex(t_program *program, t_mtx *mtx, t_code code)
{
	if (code == LOCK)
	{	
		if (pthread_mutex_lock(mtx) != 0)
			print_error_and_exit(program, RED"Error with mutex_lock.\n"RESET, 2);
	}
	else if (code == UNLOCK)
	{
		if (!pthread_mutex_unlock(mtx) != 0)
			print_error_and_exit(program, RED"Error with mutex_unlock.\n"RESET, 2);
	}
	else if (code == INIT)
	{
		if (!pthread_mutex_init(mtx, NULL) != 0)
			print_error_and_exit(program, RED"Error with mutex_inti.\n"RESET, 2);
	}
	else if (code == DESTROY)
	{
		if (!pthread_mutex_destroy(mtx) != 0)
			print_error_and_exit(program, RED"Error with mutex_destroy.\n"RESET, 2);
	}
	else
		print_error_and_exit(program, RED"Error! Wrong mutex code.\n"RESET, 2);
}

void	handle_thread(t_program *program, pthread_t *thread_info, void *(*foo)(void *), void *t_program, t_code code)
{
	if (code == CREATE)
		check_thread_error(pthread_create());
	else if (code == JOIN)
		check_thread_error(pthread_join());
	else if (code == DETACH)
		check_thread_error(pthread_detach());
	else
		print_error_and_exit(&program, RED"Error! Wrong thread code.\n"RESET, 2);
}
