/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:59:28 by smiranda          #+#    #+#             */
/*   Updated: 2024/10/08 16:11:44 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	increase_long(&philo->data->data_mutex, &philo->data->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->data))
		usleep(200);
	return (NULL);
}
