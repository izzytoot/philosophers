/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_handle_mtx_and_th.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:00:20 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/03 17:55:56 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_mutex(t_data *data, t_mtx *mtx, t_code code)
{
	if (code == INIT)
	{
		if (pthread_mutex_init(mtx, NULL) != 0)
			error_and_exit(data, RED ERR_MTX_INIT RES, 2);
	}
	else if (code == LOCK)
	{
		if (pthread_mutex_lock(mtx) != 0)
			error_and_exit(data, RED ERR_MTX_LOCK RES, 2);
	}
	else if (code == UNLOCK)
	{
		if (pthread_mutex_unlock(mtx) != 0)
			error_and_exit(data, RED ERR_MTX_UNLOCK RES, 2);
	}
	else if (code == DESTROY)
	{
		if (pthread_mutex_destroy(mtx) != 0)
			error_and_exit(data, RED ERR_MTX_DESTR RES, 2);
	}
	else
		error_and_exit(data, RED ERR_MTX_CODE RES, 2);
}

void	handle_thread(pthread_t *thread, void *(*function)(void *),
			void *t_data, t_code code)
{
	if (code == CREATE)
	{
		if (pthread_create(thread, NULL, function, t_data) != 0)
			error_and_exit(NULL, RED ERR_TH_CR RES, 2);
	}
	else if (code == JOIN)
	{
		if (pthread_join(*thread, NULL) != 0)
			error_and_exit(NULL, RED ERR_TH_J RES, 2);
	}
	else if (code == DETACH)
	{
		if (pthread_detach(*thread) != 0)
			error_and_exit(NULL, RED ERR_TH_DET RES, 2);
	}
	else
		error_and_exit(NULL, RED ERR_TH_CODE RES, 2);
}
