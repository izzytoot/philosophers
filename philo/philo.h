/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:24:12 by root              #+#    #+#             */
/*   Updated: 2025/02/13 16:47:57 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ************************************************************************** */
/*                                  LIBRARIES                                 */
/* ************************************************************************** */
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
/* ************************************************************************** */
/*                                    MACROS                                  */
/* ************************************************************************** */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"  
# define YELLOW "\033[0;33m" 
# define RESET "\033[0m"
# define	MAX_PHILOS 200
/* ************************************************************************** */
/*                                   STRUCTS                                  */
/* ************************************************************************** */

typedef pthread_mutex_t t_mtx;
typedef struct t_program s_program;

typedef enum s_code	
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
    CREATE,
    JOIN,
    DETACH,
}	t_code;

typedef struct s_fork
{
	t_mtx	mutex_fork;
	int		fork_id;
	bool	left; //?
	bool	right; //?
}	t_fork;

typedef struct s_philo
{
	pthread_t	philo_thread; // ??
	int			id;
	int			nb_meals;
	bool		max_meals_reached; // for optional arg
	// long meal_time // time for next meal against time to die
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_mtx		mutex_philo;
}	t_philo;

typedef struct s_program
{
	int		nb_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		max_meals;
	t_fork	*forks; //array of forks
	t_philo *philos; //array of philos
	t_mtx	write_mutex;
	t_mtx	access_mutex;
}	t_program;

/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */

//00_main.c
int	main(int ac, char **av);

//01_parsing.c
long	ft_atol(const char *str);
long	conv_and_check_limits(t_program *program, char *av);
void	input_parsing(t_program *program, char **av);

//02_program_init.c
void	program_init(t_program *program);
void	philo_init(t_program *program);
void	assign_forks(t_program * program, t_philo *philo, t_fork *fork, int i);
void	handle_mutex(t_program *program, t_mtx *mtx, t_code code);
void	check_mutex_error(t_program *ptogram, int status, t_code code);

// 05_utils
void	print_error_and_exit(t_program *program, char *message, int fd);
//void	free_and_clean(t_program *program);
			
#endif
