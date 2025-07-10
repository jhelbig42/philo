/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:43:23 by jhelbig           #+#    #+#             */
/*   Updated: 2025/07/10 11:01:21 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	clean_table(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->write_mtx);
	pthread_mutex_destroy(&table->table_mtx);
	while (i < table->philo_nb)
	{
		pthread_mutex_destroy(&(table->forks[i]).fork);
		pthread_mutex_destroy(&(table->philos[i]).philo_mtx);
		i++;
	}
	free(table->forks);
	free(table->philos);
}
