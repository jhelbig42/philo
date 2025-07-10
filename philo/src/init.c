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
        table->philos[i].time_last_meal = get_timestamp();
        table->philos[i].right_fork = &table->forks[i];
        pthread_mutex_init(&table->philos[i].philo_mtx, NULL);
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
    table->ready_to_go = false;
    pthread_mutex_init(&table->table_mtx, NULL);
    pthread_mutex_init(&table->write_mtx, NULL);
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
