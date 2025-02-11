/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:46:34 by root              #+#    #+#             */
/*   Updated: 2025/02/11 18:06:53 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_and_clean(t_program *program)
{
	
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

