#include "../inc/philo.h"

void    just_one(t_table *table)
{
    //philo_status(&table->philos[0], FORK);
    usleep(table->time_to_die);
    philo_status(&table->philos[0], DIED);
}

void    synchro_philos(t_table *table)
{
    bool    val;

    val = false;
    while (!val)
    {
        pthread_mutex_lock(&table->table_mtx);
        val = table->ready_to_go;
        pthread_mutex_unlock(&table->table_mtx);
    }
    return ;
}

void    philo_status(t_philo *philo, t_philo_status status)
{
    long    timestamp;

    pthread_mutex_lock(&philo->table->write_mtx);
    timestamp = get_timestamp() - philo->table->start_time;
    if (status == EATING && !finished(philo->table))
        printf("%ld %d is eating\n", timestamp, philo->id);
    else if (status == LEFT_FORK && !finished(philo->table))
        printf("%ld %d has taken left fork\n", timestamp, philo->id);
    else if (status == RIGHT_FORK && !finished(philo->table))
        printf("%ld %d has taken right fork\n", timestamp, philo->id);
    else if (status == SLEEPING && !finished(philo->table))
        printf("%ld %d is sleeping\n", timestamp, philo->id);
    else if (status == THINKING && !finished(philo->table))
        printf("%ld %d is thinking\n", timestamp, philo->id);
    else if (status == DIED && !finished(philo->table))
        printf("%ld %d died\n", timestamp, philo->id);
    pthread_mutex_unlock(&philo->table->write_mtx);

}

void    eat(t_philo *philo)
{
    //taking fork
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->left_fork->fork);
        philo_status(philo, LEFT_FORK);
        pthread_mutex_lock(&philo->right_fork->fork);
        philo_status(philo, RIGHT_FORK);
    }
    else
    {
        pthread_mutex_lock(&philo->right_fork->fork);
        philo_status(philo, RIGHT_FORK);
        pthread_mutex_lock(&philo->left_fork->fork);
        philo_status(philo, LEFT_FORK);
    }
    //eat
    philo_status(philo, EATING);
    philo->time_last_meal = get_timestamp();
    usleep(philo->table->time_to_eat * 1e3);
    philo->meals++;
    //full?
    if (philo->table->max_meal_nb > 0 && philo->meals == philo->table->max_meal_nb)
        philo->done = true;
    //release forks
    pthread_mutex_unlock(&philo->left_fork->fork);
    pthread_mutex_unlock(&philo->right_fork->fork);
}

void    *philo_life(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;

    //synchro
    synchro_philos(philo->table);
    //real life
    while (!finished(philo->table))
    {
        //am I done?
        if (philo->done == true)
            break ;
        //eat
        eat(philo);
        //sleep
        philo_status(philo, SLEEPING);
        usleep(philo->table->time_to_sleep * 1e3);
        //think
        philo_status(philo, THINKING);
    }

    return (NULL);
}