/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:02:34 by smiranda          #+#    #+#             */
/*   Updated: 2024/09/20 17:06:14 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void data_init(t_data *data)
{
    data->end_simulation = false;
    data->philos = safe_malloc(data->philo_nbr);

}