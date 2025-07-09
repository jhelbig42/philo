#include "../inc/philo.h"

//number of meals = 0
//just 1 philo

bool    finished(t_table *table)
{
    bool    ret;
    pthread_mutex_lock(&table->table_mtx);
    ret = table->done;
    pthread_mutex_unlock(&table->table_mtx);

    return (ret);
}


void    *monitor(void *data)
{
    t_table *table;
    int     i;
    int     full_philos;

    table = (t_table *)data;
    while (!finished(table))
    {
        i = 0;
        full_philos = 0;
        while (i < table->philo_nb)
        {
            if (table->philos[i].done == true)
            {
                full_philos++;
                if(full_philos == table->philo_nb)
                {
                    table->done = true;
                    printf("done because of full\n");
                    break ;
                }
            }
            else if ((get_timestamp() - table->philos[i].time_last_meal) > table->time_to_die)
            {
                philo_status(&table->philos[i], DIED);
                table->done = true;
                break ;
            }
            i++;
        }
    }
    return (NULL);

}

void    dinner(t_table *table)
{
    int i;
    pthread_t   monitor_thread;
    //edge cases
    if (table->max_meal_nb == 0)
        return ;
    if (table->philo_nb == 1)
        return (just_one(table));
    //create threads
    i = 0;
    while (i < table->philo_nb)
    {
        if (pthread_create(&table->philos[i].thread_id, NULL, &philo_life, &table->philos[i]) != 0)
        {
            printf("Failed to create philo thread\n");
            return ;
        }
        i++;
    }
    //monitor/waiter
    if (pthread_create(&monitor_thread, NULL, &monitor, table) != 0)
    {
        printf("Failed to create monitor thread\n");
        return ;
    }
    //dinner_ready
    table->start_time = get_timestamp();
    table->ready_to_go = true;
    //join threads -- wait for everyone
    i = 0;
    while (i < table->philo_nb)
    {
        if (pthread_join(table->philos[i].thread_id, NULL) != 0)
        {
            printf("Failed to join philo thread\n");
            return ;
        }
        i++;
    }
    if (pthread_join(monitor_thread, NULL) != 0)
    {
        printf("Failed to join monitor thread\n");
        return ;
    }
    
    
}
