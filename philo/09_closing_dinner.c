/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_closing_dinner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:50:08 by root              #+#    #+#             */
/*   Updated: 2025/02/17 19:51:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_and_clean(t_program *program)
{
	int	i;

	i = -1;
	if (program->philos)
	{
		while (++i < program->nb_philos)
		{
			free(program->philos[i]->philo_thread);
			free(program->philos[i]);	
		}
		free(program->philos);
	}
	if (program->forks)
		free(program->forks);
	if (program->philo_death)
		free(program->philo_death);
	free(program);
}

void	print_error_and_exit(t_program *program, char *message, int fd)
{
	int	i;

	i = 0;
	if (!program)
		return ;
	free_and_clean(program);
	if (message)
	{
		while(message[i])
		{
			write(fd, &message[i], 1);
			i++;
		}	
	}
	exit(1);
}
