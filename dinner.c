/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:50:03 by smiranda          #+#    #+#             */
/*   Updated: 2024/10/07 14:37:25 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	increase_long(&philo->data->data_mutex, &philo->data->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo, DEBUGG_MODE);
	while (!simulation_finished(philo->data))
		sleep(0.2);
	return (NULL);
}

static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo, DEBUGG_MODE);
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
	write_status(TAKE_FIRST_FORK, philo, DEBUGG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUGG_MODE);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	philo->meals_num++;
	write_status(EATING, philo, DEBUGG_MODE);
	precise_usleep(philo->data->time_to_eat, philo->data);
	if (philo->data->nbr_limit_meals > 0
		&& philo->meals_num == philo->data->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

/* 0. If no meals, return ->[0]
**      0.1. If only 1 philo
** 1. Create all threads, all philos
** 2. Create a monitor thread for dead philo
** 3. Synchronize the beggining of the simulation
**      pthread_create -> philo starts running!
**      every philo starts simultaneously
** 4. Join everyone
*/

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	increase_long(&philo->data->data_mutex, &philo->data->threads_running_nbr);
	while (!simulation_finished(philo->data))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUGG_MODE);
		precise_usleep(philo->data->time_to_sleep, philo->data);
		thinking(philo);
	}
	return (NULL);
}

void	dinner_start(t_data *data)
{
	int	i;

	i = -1;
	if (data->nbr_limit_meals == 0)
		return ;
	else if (data->philo_nbr == 1)
		safe_thread_handle(&data->philos[0].thread_id, lone_philo,
			&data->philos[0], CREATE);
	else
	{
		while (++i < data->philo_nbr)
			safe_thread_handle(&data->philos[i].thread_id, dinner_simulation,
				&data->philos[i], CREATE);
	}
	// Monitor
	safe_thread_handle(&data->monitor, monitor_dinner, data, CREATE);
	// Start Simulation
	data->start_simulation = gettime(MILISECOND);
	// now all threads are ready!
	set_bool(&data->data_mutex, &data->all_threads_ready, true);
	//  Wait for everyone
	i = -1;
	while (++i < data->philo_nbr)
		safe_thread_handle(&data->philos[i].thread_id, NULL, NULL, JOIN);
	// when this line, all philos are full
	set_bool(&data->data_mutex, &data->end_simulation, true);
	safe_thread_handle(&data->monitor, NULL, NULL, JOIN);
}
