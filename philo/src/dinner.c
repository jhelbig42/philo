/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:44:55 by jhelbig           #+#    #+#             */
/*   Updated: 2025/07/10 11:16:08 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	finished(t_table *table)
{
	bool	ret;

	pthread_mutex_lock(&table->table_mtx);
	ret = table->done;
	pthread_mutex_unlock(&table->table_mtx);
	return (ret);
}

void	just_one(t_table *table)
{
	table->start_time = get_timestamp();
	philo_status(&table->philos[0], LEFT_FORK);
	usleep(table->time_to_die * 1e3);
	philo_status(&table->philos[0], DIED);
}

bool	special_case(t_table *table)
{
	if (table->max_meals == 0)
		return (true);
	if (table->philo_nb == 1)
		return (just_one(table), true);
	return (false);
}

void	dinner(t_table *table)
{
	int			i;
	pthread_t	monitor_thread;

	if (special_case(table) == true)
		return ;
	i = 0;
	while (i < table->philo_nb)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, 
				&philo_life, &table->philos[i]) != 0)
			return (error("Failed to create philo thread"));
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, &monitor, table) != 0)
		return (error("Failed to create monitor thread"));
	table->start_time = get_timestamp();
	set_bool_mtx(&table->table_mtx, &table->ready_to_go, true);
	i = 0;
	while (i < table->philo_nb)
	{
		if (pthread_join(table->philos[i++].thread_id, NULL) != 0)
			return (error("Failed to join philo thread"));
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		return (error("Failed to join monitor thread"));
}
