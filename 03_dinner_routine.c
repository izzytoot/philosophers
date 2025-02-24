/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_dinner_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:27:17 by root              #+#    #+#             */
/*   Updated: 2025/02/24 11:40:11 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myphilo.h"

bool    get_bool(t_data *data, t_mtx *mtx, bool *value)
{
    bool ret;

    handle_mutex(data, mtx, LOCK);
    ret = *value;
    handle_mutex(data, mtx, UNLOCK);
    return (ret);

}

void    wait_threads(t_data *data)
{
    while(!get_bool(data, &data->acc_mtx, &data->threads_ready));
}


void	*mr_lonely(void *ph_ptr)
{
	t_philo	*philo;
	__uint64_t	time_left;

	philo = (t_philo *)ph_ptr;
	time_left = philo->data->time_to_die + get_time(philo->data, MILLISECONDS);
	set_time_var(philo->data, &philo->acc_mtx_ph, &philo->time_left, time_left);
	print_ph_status(philo->data, TOOK_FORK);
	while(!philo->ph_dead)
		my_usleep(philo->data, 200);
	return (NULL);
}

void	*monitor(void *data_ptr)
{
	t_data	*data;
	int	i;
	int	nb_ph_full;
	
	data = (t_data *)data_ptr;
	printf(YLL"entered monitor\n"RES);
	while(!data->all_ph_full || !data->ph_dead)
	{
		handle_mutex(data, &data->acc_mtx, LOCK);
		i = -1;
		while(++i < data->nb_ph)
		{
			nb_ph_full = 0;
			handle_mutex(data, &data->ph[i].acc_mtx_ph, LOCK);
			if (data->ph[i].ph_full)
				nb_ph_full++;
			if (data->ph[i].ph_dead)
				break;
			handle_mutex(data, &data->ph[i].acc_mtx_ph, UNLOCK);
		}
		handle_mutex(data, &data->acc_mtx, UNLOCK);
	}
	error_and_exit(data, NULL, 2);
	return (NULL);
}

void	*pre_dinner_check(void *ph_ptr)
{
	t_philo	*philo;
	__uint64_t	time_passed;
	
	philo = (t_philo *)ph_ptr;
	printf(YLL"entered pre_dinner_check for philo %d\n"RES, philo->ph_id);
	wait_threads(philo->data);
	//handle_mutex(philo->data, &philo->acc_mtx_ph, LOCK);
	if (philo->meal_count == philo->data->max_meals)
		set_bool_var(philo->data, &philo->acc_mtx_ph, &philo->ph_full, true);
	time_passed = get_time(philo->data, MILLISECONDS) - philo->data->start_meal_time;
	if (time_passed >= philo->time_left && !philo->ph_eating)
	{	
		set_bool_var(philo->data, &philo->acc_mtx_ph, &philo->ph_dead, true);
		print_ph_status(philo->data, DIED);
	}
//	handle_mutex(philo->data, &philo->acc_mtx_ph, UNLOCK);
	return (NULL);
}
void	*dinner_routine(void *ph_ptr)
{
	t_philo *philo;
	__uint64_t	time_left;
	
	philo = (t_philo *)ph_ptr;
	time_left = philo->data->time_to_die + get_time(philo->data, MILLISECONDS);
	printf(YLL"entered routine for philo %d\n"RES, philo->ph_id);
	set_time_var(philo->data, &philo->acc_mtx_ph, &philo->time_left, time_left);
//	pthread_create(&philo->ph_thread, NULL, &pre_dinner_check, &philo);
	handle_thread(philo->data, &philo->ph_thread, &pre_dinner_check, philo, CREATE);
	if(!philo->ph_dead)
	{
		ph_eating(philo);
		ph_sleeping(philo);
		ph_thinking(philo);
	}
//	pthread_join(philo->ph_thread, NULL);
	handle_thread(philo->data, &philo->ph_thread, NULL, NULL, JOIN);
	return (NULL);
}
void	start_dinner(t_data *data)
{
	int	i;
		
	data->start_meal_time = get_time(data, MILLISECONDS);
	handle_mutex(data, &data->acc_mtx, LOCK);
	if (data->max_meals == 0)
		return ;
	else if (data->nb_ph == 1)
	{	
		//pthread_create(&data->ph[0].ph_thread, NULL, &mr_lonely, &data->ph[0]);
		handle_thread(data, &data->data_thread, &mr_lonely, &data->ph[0], CREATE);
		//pthread_detach(data->ph[0].ph_thread);
		handle_thread(data, &data->data_thread, NULL, NULL, DETACH);
	}
	else
	{
		i = -1;	
		while(++i < data->nb_ph)
		{
			handle_thread(data, &data->ph[i].ph_thread, &dinner_routine, &data->ph[i], CREATE);
			printf(YLL"thread for philo %d was created\n"RES, data->ph[i].ph_id);
		//	pthread_create(&data->ph[i].ph_thread, NULL, &dinner_routine, &data->ph[i]);
		}
		my_usleep(data, 100);
	}
//	pthread_create(&data->mon_thread, NULL, &monitor, &data);
	handle_thread(data, &data->mon_thread, &monitor, &data, CREATE);
	i = -1;
	while(++i < (data)->nb_ph)
	{
		handle_thread(data, &data->ph[i].ph_thread, NULL, NULL, JOIN);
		printf("thread for philo %d was executed\n", data->ph[i].ph_id);
		//	pthread_join(data->ph[i].ph_thread, NULL);
	}
	handle_mutex(data, &data->acc_mtx, UNLOCK);
}
