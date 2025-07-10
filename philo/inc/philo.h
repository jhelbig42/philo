/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:32:42 by jhelbig           #+#    #+#             */
/*   Updated: 2025/07/10 11:16:08 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>
#include "../libft/libft.h"

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}	t_fork;

struct s_philo
{
	int				id;
	pthread_t		thread_id;
	pthread_mutex_t	philo_mtx;
	int				meals;
	bool			done;
	long			time_last_meal;
	t_fork			*right_fork;
	t_fork			*left_fork;
	t_table			*table;
};

struct s_table
{
	int				philo_nb;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				max_meals;
	long			start_time;
	bool			ready_to_go;
	bool			done;
	int				full_philos;
	pthread_mutex_t	write_mtx;
	pthread_mutex_t	table_mtx;
	t_fork			*forks;
	t_philo			*philos;
};

typedef enum e_status
{
	LEFT_FORK,
	RIGHT_FORK,
	SLEEPING,
	THINKING,
	EATING,
	DIED,
}	t_status;

//parser
int		create_table(char **argv, t_table *table);

//init
int		set_table(t_table *table);

//clean
void	clean_table(t_table *table);

//time
long	get_timestamp(void);

//dinner
void	dinner(t_table *table);
bool	finished(t_table *table);

//philos
void	*philo_life(void *data);
void	philo_status(t_philo *philo, t_status status);

//monitor
void	*monitor(void *data);

//utils
void	error(char *msg);
void	set_bool_mtx(pthread_mutex_t *mtx, bool *var, bool val);
void	set_long_mtx(pthread_mutex_t *mtx, long *var, long val);
bool	get_bool_mtx(pthread_mutex_t *mtx, bool *var);
long	get_long_mtx(pthread_mutex_t *mtx, long *var);
