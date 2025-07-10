/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:32:42 by jhelbig           #+#    #+#             */
/*   Updated: 2025/07/10 09:38:05 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>
#include "../libft/libft.h"

typedef struct s_philo t_philo;
typedef struct s_table t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}	t_fork;

struct s_philo
{
	int		id;
	pthread_t thread_id;
	int		meals;
	bool	done;
	t_fork	*right_fork;
	t_fork	*left_fork;
	long	time_last_meal;
	t_table	*table;
	pthread_mutex_t	philo_mtx;
};

struct s_table
{
	int		philo_nb;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		max_meal_nb;
	long	start_time;
	bool	ready_to_go;
	bool	done;
	bool	writting;
	pthread_mutex_t	write_mtx;
	pthread_mutex_t	table_mtx;
	t_fork	*forks;
	t_philo	*philos;
};

typedef enum	e_status
{
	LEFT_FORK,
	RIGHT_FORK,
	SLEEPING,
	THINKING,
	EATING,
	DIED,
}	t_status;

//parser
int create_table(char **argv, t_table *table);

//init
int     set_table(t_table *table);

//clean
void    clean_table(t_table *table);

//time
long    get_timestamp();

//dinner
void    dinner(t_table *table);
bool    finished(t_table *table);

//philos
void    just_one(t_table *table);
void    *philo_life(void *data);
void    philo_status(t_philo *philo, t_status status);

//utils
void    error(char *msg);
void    set_bool_mtx(pthread_mutex_t *mtx, bool *var, bool val);
