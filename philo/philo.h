/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:24:12 by root              #+#    #+#             */
/*   Updated: 2025/02/27 14:50:41 by icunha-t         ###   ########.fr       */
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
#include <errno.h> // APAGAR
#include <signal.h> //APAGAR
#include <time.h> //APAGAR
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
	MICROSECONDS,
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

typedef enum s_end
{
	PH_FULL,
	MEAL_END,
}	t_end;

typedef struct s_philo
{
	t_data		*data;
	pthread_t	ph_thread;
	int			ph_id;
	int			meal_count;
	bool		ph_eating;
	bool		ph_full;
	bool		ph_dead;
	long		last_meal;
	t_mtx		ph_mtx; 
	t_mtx		*r_fork_mtx;
	t_mtx		*l_fork_mtx;
}	t_philo;

typedef struct s_data
{
	pthread_t		data_thread;
	pthread_t		mon_thread;
	t_philo			*ph;
	long			nb_ph;
	long			max_meals;
	long			nb_ph_full;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_meal_time;
	t_mtx			*forks;
	t_mtx			write_mtx;
	t_mtx			data_mtx;
	bool			end_dinner;
	bool			threads_ready;
	bool			all_ph_full;
	bool			av5;
	bool			write_mtx_check;
	bool			data_mtx_check;
	bool			forks_check;
	bool			ph_check;
}	t_data;

/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */

//00_main.c
int			main(int ac, char **av);

//01_parsing.c
void		input_parsing_and_sort(t_data *data, char **av);
void		basic_checker(char *av);
void		init_input_data(t_data *data, char **av);
long		conv_and_check(t_data *data, char *av);
	
//02_init.c
void		program_init(t_data *data);
void		alloc_memory_data(t_data *data);
void		init_philos(t_data *data);

//03_routine_threads.c
void		start_dinner(t_data *data);
void		*monitor(void *data_ptr);
void		*dinner_routine(void *ph_ptr);
void		*mr_lonely(void *ph_ptr);

// 04_routine_actions.c
void  	 	wait_threads(t_data *data);
void		ph_eating(t_philo *philo);
void		handle_forks(t_philo *philo, t_fork_action action);
void		ph_thinking(t_philo *philo, bool check);

// 05_time_functions.c
long		get_time(t_data *data, t_time	time_unit);
void		set_time_var(t_data *data, t_mtx *mtx, long *result, long time);
long		get_time_var(t_data *data, t_mtx *mtx, long *time);
void		my_usleep(t_data *data, long sleep_time);

// 06_utils
void		handle_mutex(t_data *data, t_mtx *mtx, t_code code);
void		handle_thread(t_data *data, pthread_t *thread, void *(*function)(void *), void *t_data, t_code code);
void		set_bool_var(t_data *data, t_mtx *mtx, bool *boolean, bool value);
bool		get_bool(t_data *data, t_mtx *mtx, bool *boolean);
void		print_ph_status(t_philo *philo, t_ph_status status);
void		hold_your_horses(t_philo *philo); //enquadrar

// 07_closing_dinner.c
bool		end_dinner(t_data *data, t_philo *philo, t_end code);
void		error_and_exit(t_data *data, char *message, int fd);
void		free_and_clean(t_data *data);

#endif
