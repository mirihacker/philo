#include "philo.h"

/*
** [time_ms] [philo_id] [action]
*/

static write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
    if (status == TAKE_FIRST_FORK && !simulation_finished(philo->data))
            printf(W"%-6ld"STD" %d has taken first fork"
        "\t\t\tn°"B"%d\n"STD, elapsed, philo_id,
        philo->first_fork->fork_id);
    else if (status == TAKE_SECOND_FORK && !simulation_finished(philo->data))
            printf(W"%-6ld"STD" %d has taken second fork"
        "\t\t\tn°"B"%d\n"STD, elapsed, philo_id,
        philo->second_fork->fork_id);
    else if (status == EATING && !simulation_finished(philo->data))
        printf(W"%-6ld"STD" %d is eating"
        "\t\t\tn°"Y"%d\n"STD, elapsed, philo_id, philo->meals_num);
    else if (status == SLEEPING && !simulation_finished(philo->data))
            printf(W"%-6ld"STD" %d is sleeping\n", elapsed, philo_id);
    else if (status == THINKING && !simulation_finished(philo->data))
            printf(W"%-6ld"STD" %d is thinking\n", elapsed, philo_id);
    else if (status == DEAD)
            printf(R"%-6ld"STD" %d died\n", elapsed, philo_id);
}

void write_status(t_status status, t_philo *philo, bool debug)
{
    long elapsed;

    elapsed = gettime(MILISECOND);

    if (philo->full)
        return ;
    safe_mutex_handle(&philo->data->write_mutex, LOCK);
    if (debug)
        write_status_debug(status, philo, elapsed);
    else
    {
        if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
            && !simulation_finished(philo->data))
            printf(W"%-6ld"STD" %d has taken a fork\n", elapsed, philo_id);
        else if (status == EATING && !simulation_finished(philo->data))
            printf(W"%-6ld"C" %d is eating\n"STD, elapsed, philo_id);
        else if (status == SLEEPING && !simulation_finished(philo->data))
            printf(W"%-6ld"STD" %d is sleeping\n", elapsed, philo_id);
        else if (status == THINKING && !simulation_finished(philo->data))
            printf(W"%-6ld"STD" %d is thinking\n", elapsed, philo_id);
        else if (status == DEAD)
            printf(W"%-6ld"STD" %d died\n", elapsed, philo_id);
    }
    safe_mutex_handle(&philo->data->write_mutex, UNLOCK);
}
