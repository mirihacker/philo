/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:02:34 by smiranda          #+#    #+#             */
/*   Updated: 2024/10/08 14:18:45 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** assigns the forks to the philosophers
** to avoid deadlocks odd/even fork picking
** first fork next pos, second fork current pos
** other way for even philos
*/

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	philo_nbr;

	philo_nbr = philo->data->philo_nbr;
	philo->first_fork = &forks[(philo_pos + 1) % philo_nbr];
	philo->second_fork = &forks[philo_pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_nbr];
	}
}

static void	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->philo_nbr)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->meals_num = 0;
		philo->full = false;
		philo->data = data;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, data->forks, i);
		i++;
	}
}
/*
** data initialize and philo structs
*/

void	data_init(t_data *data)
{
	int	i;

	i = 0;
	data->end_simulation = false;
	data->all_threads_ready = false;
	data->start_time = gettime(MILISECOND);
	data->threads_running_nbr = 0;
	data->philos = safe_malloc(sizeof(t_philo) * data->philo_nbr);
	safe_mutex_handle(&data->data_mutex, INIT);
	safe_mutex_handle(&data->write_mutex, INIT);
	data->forks = safe_malloc(sizeof(t_fork) * data->philo_nbr);
	while (i < data->philo_nbr)
	{
		safe_mutex_handle(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
		i++;
	}
	philo_init(data);
}
