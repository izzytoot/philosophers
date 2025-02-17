/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:46:34 by root              #+#    #+#             */
/*   Updated: 2025/02/17 19:54:28 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	change_bool_value(t_program *program, t_mtx *mtx, bool *boolean, bool value)
{
	handle_mutex(program, mtx, LOCK);
	*boolean = value;
	handle_mutex(program, mtx, UNLOCK);
}

bool	true_or_false(t_program *program, t_mtx *mtx, bool *value)
{
	bool	result;
	
	handle_mutex(program, mtx, LOCK);
	result = *value;
	handle_mutex(program, mtx, UNLOCK);
	return (result);
}

void	count_active_philos(t_program *program, t_mtx *mtx, int counter)
{
	handle_mutex(program, mtx, LOCK);
	counter++;
	handle_mutex(program, mtx, UNLOCK);
}

void	print_ph_status(t_philo *philo, t_ph_status status);
{
	if (t_ph_status == EATING)
		printf(GREEN"")
}
