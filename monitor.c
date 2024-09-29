#include "philo.h"

static void philo_died(t_philo *philo)
{
    long elapsed;
    long t_to_die;

    if (get_bool(&philo->philo_mutex, &philo->full))
        return (false);
    elapsed = gettime(MILISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
    t_to_die = philo->data->time_to_die / 1000;
    if (elapsed >t_to_die)
        return (true);
    return (false);
}

void *monitor_dinner(void *data)
{
    t_data *table;

    table = (t_data *)data;
    //spinlock till all threads run
    while (!all_threads_running(&data->data_mutex, &data->threads_running_nbr,
            data->philo_nbr))
    ;
    while (!simulation_finished(data))
    {
        i = -1;
        while (++i < data->philo_nbr)
        {
            if (philo_died(data->philos + i))
            {
                set_bool(&data->data_mutex, &data->end_simulation, true);
                write_status(DIED, data->philos + i, DEBUG_MODE);
            }
        }
    }
}