/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 08:34:40 by jhelbig           #+#    #+#             */
/*   Updated: 2025/07/10 11:16:08 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	create_table(char **argv, t_table *table)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if (!ft_isnumber(argv[i]))
			return (1);
		i++;
	}
	table->philo_nb = (long)ft_atoi(argv[1]);
	table->time_to_die = (long)ft_atoi(argv[2]);
	table->time_to_eat = (long)(ft_atoi(argv[3]));
	table->time_to_sleep = (long)(ft_atoi(argv[4]));
	if (argv[5])
		table->max_meals = ft_atoi(argv[5]);
	else
		table->max_meals = -1;
	return (0);
}
