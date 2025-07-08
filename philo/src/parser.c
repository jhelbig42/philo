/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 08:34:40 by jhelbig           #+#    #+#             */
/*   Updated: 2025/06/27 10:11:04 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	create_table(char **argv, t_table *table)
{
	//check if all are numbers
	int		i;

	i = 1;
	while(argv[i])
	{
		if (!ft_isnumber(argv[i]))
			return (1);
		i++;
	}
	//atois
	table->philo_nb = (long)ft_atoi(argv[1]);
	table->time_to_die = (long)ft_atoi(argv[2]);
	table->time_to_eat = (long)(ft_atoi(argv[3]) * 1e3);
	table->time_to_sleep = (long)(ft_atoi(argv[4]) * 1e3);
	if (argv[5])
		table->max_meal_nb = ft_atoi(argv[5]);
	else
		table->max_meal_nb = -1;
	return (0);
}
