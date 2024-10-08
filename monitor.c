/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:39:29 by smiranda          #+#    #+#             */
/*   Updated: 2024/10/08 14:22:47 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime(MILISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	t_to_die = philo->data->time_to_die / 1000;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_data	*table;
	int		i;

	table = (t_data *)data;
	while (!all_threads_running(&table->data_mutex, &table->threads_running_nbr,
			table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr)
		{
			if (simulation_finished(table))
				return (NULL);
			if (philo_died(table->philos + i))
			{
				set_bool(&table->data_mutex, &table->end_simulation, true);
				write_status(DEAD, table->philos + i, DEBUGG_MODE);
			}
		}
		usleep(10);
	}
	return (NULL);
}
