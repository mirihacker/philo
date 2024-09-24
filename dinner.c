/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:50:03 by smiranda          #+#    #+#             */
/*   Updated: 2024/09/24 15:19:53 by smiranda         ###   ########.fr       */
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

void *dinner_simulation(void *data)
{
    t_philo *philo;
    
    philo = (t_philo *)data;

}

void dinner_start(t_data *data)
{
    int i;

    i = 0;
    if (data->nbr_limit_meals == 0)
        return;
    else if (data->philo_nbr == 1)
    ;//TO DO
    else
    {
        while (i < data->philo_nbr)
        {
            safe_thread_handle(&data->philos[i].thread_id, dinner_simulation, data->philos[i], CREATE);
            i++;
        }
    }
    // now all threads are ready!
}
