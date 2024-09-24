/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:50:03 by smiranda          #+#    #+#             */
/*   Updated: 2024/09/24 16:36:26 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (!simulation_finished(philo->data))
	{
		if (philo->full) // TODO thread safe?
			break ;
		eat(philo);
		// 3) sleep ->write_status & precise usleep
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
		; // TO DO
	else
	{
		while (++i < data->philo_nbr)
			safe_thread_handle(&data->philos[i].thread_id, dinner_simulation,
				&data->philos[i], CREATE);
	}
	// Start Simulation
	data->start_simulation = gettime(MILISECOND);
	// now all threads are ready!
	set_bool(&data->data_mutex, &data->all_threads_ready, true);
	//  Wait for everyone
	i = -1;
	while (++i < data->philo_nbr)
		safe_thread_handle(&data->philos[i].thread_id, NULL, NULL, JOIN);
	// when this line, all philos are full
}
