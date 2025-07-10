/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:28:12 by jhelbig           #+#    #+#             */
/*   Updated: 2025/07/10 11:03:50 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_table		table;

	if (argc == 5 || argc == 6)
	{
		if (create_table(argv, &table))
			return (1);
		if (set_table(&table))
			return (1);
		dinner(&table);
		clean_table(&table);
	}
	else
	{
		printf("wrong input\nUse should be:\n");
		printf("./philo philo_nb t_to_die t_to_eat t_to_sleep [max_meals]\n");
		printf("e.g.:\n./philo 4 410 200 200 [5]\n");
	}
	return (0);
}
