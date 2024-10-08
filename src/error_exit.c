/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:16:51 by smiranda          #+#    #+#             */
/*   Updated: 2024/10/08 17:01:40 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	clean(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->philo_nbr)
	{
		philo = data->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
		i++;
	}
	safe_mutex_handle(&data->write_mutex, DESTROY);
	safe_mutex_handle(&data->data_mutex, DESTROY);
	free(data->forks);
	free(data->philos);
}

void	error_exit(const char *error)
{
	printf(RED "%s\n" STD, error);
	exit(EXIT_FAILURE);
}
