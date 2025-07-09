#include "../inc/philo.h"

void    clean_table(t_table *table)
{
    int i;

    i = 0;
    while(i < table->philo_nb)
    {
        pthread_mutex_destroy(&(table->forks[i]).fork);
        i++;
    }
    free(table->forks);
    free(table->philos);
}
