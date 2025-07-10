/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:45:22 by jhelbig           #+#    #+#             */
/*   Updated: 2025/07/10 11:09:11 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	watch_philos(t_table *table)
{
	int		i;
	bool	done;
	long	time_since_meal;

	i = 0;
	table->full_philos = 0;
	while (i < table->philo_nb)
	{
		done = get_bool_mtx(&table->philos[i].philo_mtx,
				&table->philos[i].done);
		time_since_meal = get_timestamp() - get_long_mtx
			(&table->philos[i].philo_mtx, &table->philos[i].time_last_meal);
		if (done == true)
		{
			table->full_philos++;
			if (table->full_philos == table->philo_nb)
				return (set_bool_mtx(&table->table_mtx, 
						&table->done, true), printf("all are full\n"), true);
		}
		else if (time_since_meal > table->time_to_die)
			return (set_bool_mtx(&table->table_mtx, &table->done, true), 
				philo_status(&table->philos[i], DIED), true);
		i++;
	}
	return (false);
}

void	*monitor(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	while (!finished(table))
	{
		if (watch_philos(table) == true)
			break ;
	}
	return (NULL);
}
