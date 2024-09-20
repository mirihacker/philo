/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:44:27 by smiranda          #+#    #+#             */
/*   Updated: 2024/09/20 14:58:32 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void error_exit(const char *error)
{
    printf(RED"%s\n"STD, error);
    exit(EXIT_FAILURE);
}