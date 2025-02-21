/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myphilo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:24:12 by root              #+#    #+#             */
/*   Updated: 2025/02/21 20:03:06 by root             ###   ########.fr       */
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
//colors
# define 	RED "\033[0;31m"
# define 	GR "\033[0;32m"  
# define 	YLL "\033[0;33m" 
# define 	RES "\033[0m"
//errors
# define	ERR_MEM "Error allocating memory\n"
# define	ERR_INP "Error!\nRun: ./philo <nb_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> <max_meals>\n"
# define	ERR_INP2 "Error! Inputs must be positive ints.\n"
# define	ERR_NB_PHILOS "Error! Philos must be between 1 and 200.\n"
# define	ERR_TIME_LIMIT "Error!Time values must be at least 60 seconds.\n"
# define	ERR_MTX_INIT "Error with mutex_init.\n"
# define	ERR_MTX_LOCK "Error with mutex_lock.\n"
# define	ERR_MTX_UNLOCK "Error with mutex_unlock.\n"
# define	ERR_MTX_DESTR "Error with mutex_destroy.\n"
# define	ERR_MTX_CODE "Error! Wrong mutex code.\n"
# define	ERR_TH_CR "Error! Unable to create thread.\n"
# define	ERR_TH_J "Error! Unable to join thread.\n"
# define	ERR_TH_DET "Error! Unable to detach thread.\n"
# define	ERR_TH_CODE "Error! Wrong thread code.\n"
# define	ERR_TIME "Failed getting timeofday.\n"
# define	ERR_TIME2 "Error! Invalid time unit.\n"
//etc
# define	MAX_PHILOS 200
/* ************************************************************************** */
/*                                   STRUCTS                                  */
/* ************************************************************************** */

typedef pthread_mutex_t	t_mtx;
typedef struct s_data t_data;
typedef struct s_philo t_philo;

typedef enum s_time
{
	MICROSSECONDS,
	MILLISECONDS,
	SECONDS,
}	t_time;

typedef enum s_fork_action
{
	TAKE,
	DROP,
}	t_fork_action;

typedef enum s_ph_status
{
	TOOK_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
}	t_ph_status;

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

typedef struct s_philo
{
	t_data		*data;
	pthread_t	ph_thread;
	int			ph_id;
	int			meal_count;
	bool		ph_eating;
	bool		ph_full;
	bool		ph_dead;
	__uint64_t	time_left;
	t_mtx		acc_mtx_ph; 
	t_mtx		r_fork_mtx;
	t_mtx		l_fork_mtx;
}	t_philo;

typedef struct s_data
{
	pthread_t		data_thread;
	pthread_t		mon_thread;
	t_philo			*ph;
	long			nb_ph;
	long			max_meals;
	__uint64_t		time_to_die; //u_int64_t - unsigned interger of 64 bits
	__uint64_t		time_to_eat;
	__uint64_t		time_to_sleep;
	__uint64_t		start_meal_time;
	bool			ph_dead;
	bool			all_ph_full;
	bool			threads_ready;
	t_mtx			*forks;
	t_mtx			write_mtx;
	t_mtx			acc_mtx;
}	t_data;

/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */

//00_main.c
int	main(int ac, char **av);

//01_parsing.c
void	input_parsing_and_sort(t_data *data, char **av);
void	basic_checker(t_data *data, char *av);
void	init_input_data(t_data *data, char **av);
long	conv_and_check(t_data *data, char *av);

//02_init.c
void	program_init(t_data *data);
void	alloc_memory_data(t_data *data);
void	init_philos(t_data *data);
void	assign_forks(t_data *data);

//03_routine.c
void	start_dinner(t_data *data);
void	*dinner_routine(void *ph_ptr);
void	*pre_dinner_check(void *ph_ptr);
void	*monitor(void *data_ptr);
void	*mr_lonely(void *ph_ptr);

// 04_eat_sleep_think.c
void	handle_forks(t_philo *philo, t_fork_action action);
void	ph_eating(t_philo *philo);
void	ph_sleeping(t_philo *philo);
void	ph_thinking(t_philo *philo);

// 05_time_functions.c
__uint64_t	get_time(t_data *data, t_time	time_unit);
void	set_time_var(t_data *data, t_mtx *mtx, __uint64_t *result, __uint64_t time);
void	my_usleep(t_data *data, __uint64_t sleep_time);

// 06_utils
void	handle_mutex(t_data *data, t_mtx *mtx, t_code code);
void	handle_thread(t_data *data, pthread_t *thread, void *(*function)(void *), void *t_data, t_code code);
void	set_bool_var(t_data *data, t_mtx *mtx, bool *boolean, bool value);
void	print_ph_status(t_data *data, t_ph_status status);

// 07_closing_dinner.c
void	error_and_exit(t_data *data, char *message, int fd);
void	free_and_clean(t_data *data);

#endif
