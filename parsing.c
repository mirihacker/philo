/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:07:59 by smiranda          #+#    #+#             */
/*   Updated: 2024/10/08 15:49:44 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

/*
** Verifies that the input value is correct,
** skips white space, checks for negative,
** an acceptable number (+77$%)
** checks for INT_MAX
** Returns pointer to the digit to start processing
*/

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*nbr;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("Only positive numbers");
	if (!is_digit(*str))
		error_exit("Not correct digit");
	nbr = str;
	while (is_digit(*str))
	{
		++len;
		++str;
	}
	if (len > 10)
		error_exit("Value too big");
	return (nbr);
}

static long	ft_atol(const char *str)
{
	long		num;
	const char	*start;

	num = 0;
	start = valid_input(str);
	while (*start && is_digit(*start))
	{
		if (num > (INT_MAX / 10) || (num == (INT_MAX / 10) && (*start
					- '0') > (INT_MAX % 10)))
			error_exit("Value too big");
		num = (num * 10) + (*start - '0');
		++start;
	}
	return (num);
}

/*
** checks for numbers smaller than INT_MAX
** and timestamps > 60ms
** converts to ms
*/

void	parse_input(t_data *data, char **argv)
{
	data->philo_nbr = ft_atol(argv[1]);
	if (data->philo_nbr <= 0)
		error_exit("Number of philo bigger than 0");
	data->time_to_die = ft_atol(argv[2]) * 1000;
	data->time_to_eat = ft_atol(argv[3]) * 1000;
	data->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (data->time_to_die < 60000 || data->time_to_eat < 60000
		|| data->time_to_sleep < 60000)
		error_exit("Timestamps must be bigger than 60ms");
	if (!argv[5])
		data->nbr_limit_meals = -1;
	else
		data->nbr_limit_meals = ft_atol(argv[5]);
}
