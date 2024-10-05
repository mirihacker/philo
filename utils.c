/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:44:27 by smiranda          #+#    #+#             */
/*   Updated: 2024/09/24 16:37:24 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	precise_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finished(data))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1000)
			sleep((rem / 2)/1000);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				sleep(10/1000);
		}
	}
}

long	gettime(t_time_code time_code)
{
    struct timeval	time;
    long            result;

    if (gettimeofday(&time, NULL))
        error_exit("Gettimeofday failed");
    if (time_code == SECOND)
		return(time.tv_sec);
    else if (time_code == MILISECOND)
        return((time.tv_sec * 1000) + (time.tv_usec / 1000));
    else if (time_code == MICROSECOND)
        return((time.tv_sec * 1000000) + time.tv_usec);
    else
        error_exit("Wrong input to gettime!");
    return (0);
}


void clean(t_data *data)
{
	t_philo *philo;
	int i;
	
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