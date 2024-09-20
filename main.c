/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:30:19 by smiranda          #+#    #+#             */
/*   Updated: 2024/09/20 16:34:48 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
    t_data data;

	if (argc == 5 || argc == 6)
	{
		// 1) errors checking, filling table data
        parse_input(&data, argv);

        // 2) creating the actual thing
        data_init(&data); //TO DO

        // 3) start dinner
        dinner_start(&data); //TO DO

        // 4) No leaks ->philos full | 1 philo died
        clean(&data); //TO DO
	}
	else
	{
		error_exit("Wrong intput:\n" G "Correct is ./philo 5 800 200 200 [5]" STD);
	}
}