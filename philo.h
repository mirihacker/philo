/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:52:42 by smiranda          #+#    #+#             */
/*   Updated: 2024/10/08 16:21:12 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define STD "\033[0m"
# define RED "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define M "\033[1;35m"
# define C "\033[1;36m"
# define W "\033[1;37m"

# define DEBUGG_MODE 0

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DEAD,
}						t_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}						t_time_code;

/*
** number_of_philo
** time_to_die
** time_to_eat
** time_to_sleep
** number_of_times_each_philo_eat
*/

typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_num;
	bool				full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_mtx				philo_mutex;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meals;
	long				start_simulation;
	bool				end_simulation;
	bool				threads_sync;
	long				threads_running_nbr;
	long				start_time;
	pthread_t			monitor;
	t_mtx				data_mutex;
	t_mtx				write_mutex;
	t_fork				*forks;
	t_philo				*philos;
}						t_data;

// time_utils.c //
long					gettime(t_time_code time_code);
void					ft_usleep(long usec, t_data *data);

// error_exit.c //
void					error_exit(const char *error);
void					clean(t_data *data);

// parsing.c //
void					parse_input(t_data *data, char **argv);

// safe_functions.c //
void					*safe_malloc(size_t bytes);
void					safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void					safe_thread_handle(pthread_t *thread,
							void *(*foo)(void *), void *data, t_opcode opcode);

// data_init.c //
void					set_data(t_data *data);

// getters and setters //
void					set_bool(t_mtx *mutex, bool *dest, bool value);
bool					get_bool(t_mtx *mutex, bool *value);
void					set_long(t_mtx *mutex, long *dest, long value);
long					get_long(t_mtx *mutex, long *value);
bool					simulation_finished(t_data *data);

// synchro.c //
void					wait_threads(t_data *data);
bool					all_threads_running(t_mtx *mutex, long *threads,
							long philo_nbr);
void					increase_long(t_mtx *mutex, long *value);

// write.c //
void					write_status(t_status status, t_philo *philo);

// monitor.c //
void					*monitor_sim(void *data);

// dinner.c //
void					*single_philo(void *arg);
void					*philo_routine(void *data);
void					launch_sim(t_data *data);

#endif