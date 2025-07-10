#include "../inc/philo.h"

void    error(char *msg)
{
    printf("%s\n", msg);
    return ;
}

void    set_bool_mtx(pthread_mutex_t *mtx, bool *var, bool val)
{
    pthread_mutex_lock(mtx);
    *var = val;
    pthread_mutex_unlock(mtx);
}
