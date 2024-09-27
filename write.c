#include "philo.h"

/*
** [time_ms] [philo_id] [action]
*/

void write_status(t_status status, t_philo *philo)
{
    safe_mutex_handle(&philo->data->write_mutex, LOCK);
    if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)

    safe_mutex_handle(&philo->data->write_mutex, UNLOCK);
}