/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:30:19 by smiranda          #+#    #+#             */
/*   Updated: 2024/10/08 15:53:55 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		parse_input(&data, argv);
		set_data(&data);
		launch_sim(&data);
		clean(&data);
	}
	else
		error_exit("Wrong intput:\n"
			G "Correct is ./philo 5 800 200 200 [5]" STD);
}
