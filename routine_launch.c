/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_launch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:50:03 by smiranda          #+#    #+#             */
/*   Updated: 2024/10/08 16:50:38 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo);
}

/*
** eat routine
** 1. Grab the forks: here first & second fork is taken
** 2. Eat: write eat, update last meal, update meals counter
	eventually bool FULL
** 3. Release the forks
*/

static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	philo->meals_num++;
	write_status(EATING, philo);
	ft_usleep(philo->data->t_eat, philo->data);
	if (philo->data->nbr_meals > 0
		&& philo->meals_num == philo->data->nbr_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

/*
** routine for dinner with 1+ philo 
** wait for all threads
** set time for last_meal
** counter for philos/threads
** eat, think, sleep
*/

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	increase_long(&philo->data->data_mutex, &philo->data->threads_running_nbr);
	while (!simulation_finished(philo->data))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		ft_usleep(philo->data->t_sleep, philo->data);
		thinking(philo);
	}
	return (NULL);
}

/*
** philosopher simulation
** threats cases with one philo and several
** creates all threads (philos + monitor)
** set start sim time, set thread_sync
** wait for all threads to finish
*/

void	launch_sim(t_data *data)
{
	int	i;

	i = -1;
	if (data->nbr_meals == 0)
		return ;
	else if (data->philo_nbr == 1)
		safe_thread_handle(&data->philos[0].thread_id, single_philo,
			&data->philos[0], CREATE);
	else
	{
		while (++i < data->philo_nbr)
			safe_thread_handle(&data->philos[i].thread_id, philo_routine,
				&data->philos[i], CREATE);
	}
	safe_thread_handle(&data->monitor, monitor_sim, data, CREATE);
	set_bool(&data->data_mutex, &data->threads_sync, true);
	i = -1;
	while (++i < data->philo_nbr)
		safe_thread_handle(&data->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&data->data_mutex, &data->end_sim, true);
	safe_thread_handle(&data->monitor, NULL, NULL, JOIN);
}
