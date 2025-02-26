/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:54:47 by root              #+#    #+#             */
/*   Updated: 2025/02/26 13:27:55 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myphilo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		input_parsing_and_sort(&data, av);
		program_init(&data);
		start_dinner(&data);
		free_and_clean(&data);
	}
	else
		error_and_exit(&data, RED ERR_INP RES, 2);
	return (0);
}
