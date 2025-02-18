/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_handle_mutex_and_threads.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:27:00 by root              #+#    #+#             */
/*   Updated: 2025/02/18 16:14:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_mutex(t_program *program, t_mtx *mtx, t_code code)
{
	if (code == LOCK)
	{	
		if (pthread_mutex_lock(mtx) != 0)
			print_error_and_exit(program, RED"Error with mutex_lock.\n"RESET, 2);
	}
	else if (code == UNLOCK)
	{
		if (pthread_mutex_unlock(mtx) != 0)
			print_error_and_exit(program, RED"Error with mutex_unlock.\n"RESET, 2);
	}
	else if (code == INIT)
	{
		if (pthread_mutex_init(mtx, NULL) != 0)
			print_error_and_exit(program, RED"Error with mutex_init.\n"RESET, 2);
	}
	else if (code == DESTROY)
	{
		if (pthread_mutex_destroy(mtx) != 0)
			print_error_and_exit(program, RED"Error with mutex_destroy.\n"RESET, 2);
	}
	else
		print_error_and_exit(program, RED"Error! Wrong mutex code.\n"RESET, 2);
}

void	handle_thread(t_program *program, pthread_t *thread_info, void *(*ph_func)(void *), void *t_program, t_code code)
{
	if (code == CREATE)
	{	
		if (pthread_create(thread_info, NULL, ph_func, t_program) != 0)
			print_error_and_exit(program, RED"Error with thread_create.\n"RESET, 2);
	}
	else if (code == JOIN)
	{	
		if (pthread_join(*thread_info, NULL) == 0)
			print_error_and_exit(program, RED"Error with thread_join.\n"RESET, 2);
	}
	else if (code == DETACH)
	{
		if (pthread_detach(*thread_info) != 0)
			print_error_and_exit(program, RED"Error with thread_detach.\n"RESET, 2);
	}	
	else
		print_error_and_exit(program, RED"Error! Wrong thread code.\n"RESET, 2);
}
