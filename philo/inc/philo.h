/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:32:42 by jhelbig           #+#    #+#             */
/*   Updated: 2025/06/27 09:40:09 by jhelbig          ###   ########.fr       */
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
	long	time_since_last_meal;
	t_table	*table;
};

struct s_table
{
	int		philo_nb;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		max_meal_nb;
	int		start_time;
	bool	done;
	t_fork	*forks;
	t_philo	*philos;
};

//parser
int create_table(char **argv, t_table *table);

//init
int     set_table(t_table *table);

//clean
void    clean_table(t_table *table);