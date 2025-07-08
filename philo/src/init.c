#include "../inc/philo.h"

void    init_philo(t_table *table)
{
    int i;

    i = 0;
    while (i < table->philo_nb)
    {
        table->philos[i].id = i + 1;
        table->philos[i].meals = 0;
        table->philos[i].done = false;
        table->philos[i].time_since_last_meal = 0;
        table->philos[i].right_fork = &table->forks[i];
        if (i == 0)
            table->philos[i].left_fork = &table->forks[table->philo_nb - 1];
        else
            table->philos[i].left_fork = &table->forks[i - 1];
        table->philos[i].table = table;
        i++;
    }
}

int     set_table(t_table *table)
{
    int     i;
    
    table->done = false;
    
    table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_nb);
    if (!table->philos)
        return (free(table->forks), 1);
    table->forks = (t_fork *)malloc(sizeof(t_fork) * table->philo_nb);
    if (!table->forks)
        return (1);
    i = 0;
    while (i < table->philo_nb)
    {
        pthread_mutex_init(&(table->forks[i]).fork, NULL);
        table->forks[i].id = i;
        i++;
    }
    init_philo(table);
    return(0);

}