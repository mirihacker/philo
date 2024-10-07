/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:39:53 by smiranda          #+#    #+#             */
/*   Updated: 2024/10/07 14:37:47 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** [time_ms] [philo_id] [action]
*/

static void write_status_debug(t_status status, t_philo *philo, long elapsed)
{
    if (status == TAKE_FIRST_FORK && !simulation_finished(philo->data))
            printf(W"%ld"STD" %d has taken first fork"
        "\t\t\tn°"B"%d\n"STD, elapsed, philo->id,
        philo->first_fork->fork_id);
    else if (status == TAKE_SECOND_FORK && !simulation_finished(philo->data))
            printf(W"%ld"STD" %d has taken second fork"
        "\t\t\tn°"B"%d\n"STD, elapsed, philo->id,
        philo->second_fork->fork_id);
    else if (status == EATING && !simulation_finished(philo->data))
        printf(W"%ld"STD" %d is eating"
        "\t\t\tn°"Y"%d\n"STD, elapsed, philo->id, philo->meals_num);
    else if (status == SLEEPING && !simulation_finished(philo->data))
            printf(W"%ld"STD" %d is sleeping\n", elapsed, philo->id);
    else if (status == THINKING && !simulation_finished(philo->data))
            printf(W"%ld"STD" %d is thinking\n", elapsed, philo->id);
    else if (status == DEAD)
            printf(W"%ld"STD" %d died\n", elapsed, philo->id);
}

void write_status(t_status status, t_philo *philo, bool debug)
{
    long elapsed;

    elapsed = gettime(MILISECOND) - philo->data->start_time;

    if (philo->full)
        return ;
    safe_mutex_handle(&philo->data->write_mutex, LOCK);
    if (debug)
        write_status_debug(status, philo, elapsed);
    else
    {
        if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
            && !simulation_finished(philo->data))
            printf(W"%ld"STD" %d has taken a fork\n", elapsed, philo->id);
        else if (status == EATING && !simulation_finished(philo->data))
            printf(W"%ld"C" %d is eating\n"STD, elapsed, philo->id);
        else if (status == SLEEPING && !simulation_finished(philo->data))
            printf(W"%ld"STD" %d is sleeping\n", elapsed, philo->id);
        else if (status == THINKING && !simulation_finished(philo->data))
            printf(W"%ld"STD" %d is thinking\n", elapsed, philo->id);
        else if (status == DEAD)
            printf(W"%ld"STD" %d died\n", elapsed, philo->id);
    }
    safe_mutex_handle(&philo->data->write_mutex, UNLOCK);
}
