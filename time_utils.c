/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:44:27 by smiranda          #+#    #+#             */
/*   Updated: 2024/10/08 16:29:50 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long usec, t_data *data)
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
			usleep(rem / 2);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				usleep(10);
		}
	}
}

long	gettime(t_time_code time_code)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		error_exit("Gettimeofday failed");
	if (time_code == SECOND)
		return (time.tv_sec);
	else if (time_code == MILISECOND)
		return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	else if (time_code == MICROSECOND)
		return ((time.tv_sec * 1000000) + time.tv_usec);
	else
		error_exit("Wrong input to gettime!");
	return (0);
}
