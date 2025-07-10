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
    bool    done;
    long    

    table = (t_table *)data;
    while (!finished(table))
    {
        i = 0;
        full_philos = 0;
        while (i < table->philo_nb)
        {
            pthread_mutex_lock(&table->philos[i].philo_mtx);
            done = table->philos[i].done;
            pthread_mutex_unlock(&table->philos[i].philo_mtx);
            if (done == true)
            {
                full_philos++;
                if (full_philos == table->philo_nb)
                {
                    pthread_mutex_lock(&table->table_mtx);
                    table->done = true;
                    pthread_mutex_unlock(&table->table_mtx);
                    printf("all are full\n");
                    break ;
                }
            }
            else if ((get_timestamp() - table->philos[i].time_last_meal) > table->time_to_die)
            {
                pthread_mutex_lock(&table->table_mtx);
                table->done = true;
                pthread_mutex_unlock(&table->table_mtx);
                philo_status(&table->philos[i], DIED);
                break ;
            }
            i++;
        }
    }
    return (NULL);
}
bool    special_case(t_table *table)
{
    if (table->max_meal_nb == 0)
        return (true);
    if (table->philo_nb == 1)
        return (just_one(table), true);
    return (false);
}
void    dinner(t_table *table)
{
    int         i;
    pthread_t   monitor_thread;
    
    if (special_case(table) == true)
        return ;
    i = 0;
    while (i < table->philo_nb)
    {
        if (pthread_create(&table->philos[i].thread_id, NULL, &philo_life, &table->philos[i]) != 0)
            return(error("Failed to create philo thread"));
        i++;
    }
    if (pthread_create(&monitor_thread, NULL, &monitor, table) != 0)
        return (error("Failed to create monitor thread"));
    table->start_time = get_timestamp();
    set_bool_mtx(&table->table_mtx, &table->ready_to_go, true);
    i = 0;
    while (i < table->philo_nb)
    {
        if (pthread_join(table->philos[i].thread_id, NULL) != 0)
            return (error("Failed to join philo thread"));
        i++;
    }
    if (pthread_join(monitor_thread, NULL) != 0)
        return(error("Failed to join monitor thread"));
}
