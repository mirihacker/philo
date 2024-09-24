/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:07:59 by smiranda          #+#    #+#             */
/*   Updated: 2024/09/24 16:36:56 by smiranda         ###   ########.fr       */
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
** 1) check for negatives
** 2) check if the number is legit
**      "     +777$%" --> correct
**      "    +&%42" --> incorrect
** 3) check for INT_MAX
**      check for len 2_147_483_647 if len > 10, sure > INT_MAX
**      (2_147_483_647 -> 9_999_999_999) still to chek
**
**      Return pointer to the digit to start processing
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
	if (!is_digit)
		error_exit("Not correct digit");
	nbr = str;
	while (is_digit(*str))
		++len;
	if (len > 10)
		error_exit("Value too big");
	return (nbr);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		error_exit("Value too big");
	return (num);
}

/*
** 1) actual numbers
** 2) not > INT_MAX
** 3) timestamps > 60ms
*/

void	parse_input(t_data *data, char **argv)
{
	data->philo_nbr = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]) * 1e3;
	data->time_to_eat = ft_atol(argv[3]) * 1e3;
	data->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (data->time_to_die < 6e4 || data->time_to_eat < 6e4
		|| data->time_to_sleep < 6e4)
		error_exit("Timestamps must be bigger than 60ms");
	if (!argv[5])
		data->nbr_limit_meals = -1;
	else
		data->nbr_limit_meals = ft_atol(argv[5]);
}