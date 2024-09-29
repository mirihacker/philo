/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:30:19 by smiranda          #+#    #+#             */
/*   Updated: 2024/09/24 16:36:48 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data data;

	if (argc == 5 || argc == 6)
	{
		parse_input(&data, argv);
		printf("Parsing done!\n");
		data_init(&data);
		printf("Data Init done!\n");
		dinner_start(&data);
		printf("Dinner Simulation done!\n");
		clean(&data);
	}
	else
		error_exit("Wrong intput:\n" G "Correct is ./philo 5 800 200 200 [5]" STD);
}