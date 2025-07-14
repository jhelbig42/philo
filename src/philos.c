/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:45:03 by jhelbig           #+#    #+#             */
/*   Updated: 2025/07/10 11:35:12 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	synchro_philos(t_table *table)
{
	bool	val;

	val = false;
	while (!val)
	{
		pthread_mutex_lock(&table->table_mtx);
		val = table->ready_to_go;
		pthread_mutex_unlock(&table->table_mtx);
	}
	return ;
}

void	philo_status(t_philo *philo, t_status status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->write_mtx);
	timestamp = get_timestamp() - philo->table->start_time;
	if (status == EATING && !finished(philo->table))
		printf("%ld %d is eating\n", timestamp, philo->id);
	else if (status == LEFT_FORK && !finished(philo->table))
		printf("%ld %d has taken a fork\n", timestamp, philo->id);
	else if (status == RIGHT_FORK && !finished(philo->table))
		printf("%ld %d has taken a fork\n", timestamp, philo->id);
	else if (status == SLEEPING && !finished(philo->table))
		printf("%ld %d is sleeping\n", timestamp, philo->id);
	else if (status == THINKING && !finished(philo->table))
		printf("%ld %d is thinking\n", timestamp, philo->id);
	else if (status == DIED)
		printf("%ld %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->write_mtx);
}

void	eat(t_philo *philo)
{
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
	philo_status(philo, EATING);
	set_long_mtx(&philo->philo_mtx, &philo->time_last_meal, get_timestamp());
	philo->meals++;
	if (philo->table->max_meals > 0 && philo->meals == philo->table->max_meals)
		set_bool_mtx(&philo->philo_mtx, &philo->done, true);
	usleep(philo->table->time_to_eat * 1e3);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void	*philo_life(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	synchro_philos(philo->table);
	while (!finished(philo->table))
	{
		if (philo->done == true)
			break ;
		eat(philo);
		philo_status(philo, SLEEPING);
		usleep(philo->table->time_to_sleep * 1e3);
		philo_status(philo, THINKING);
		usleep(1000);
	}
	return (NULL);
}
