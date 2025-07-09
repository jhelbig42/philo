/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:28:12 by jhelbig           #+#    #+#             */
/*   Updated: 2025/06/27 13:49:51 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_table		table;

	if (argc == 5 || argc == 6)
	{
		//parse input
		if (create_table(argv, &table))
			return (1);
		//set table
		if (set_table(&table))
			return (1);
		//have meal
		dinner(&table);
		//clean
		clean_table(&table);
	}
	else
	{
		printf("wrong input\nUse should be:\n./philo philo_nb time_to_die time_to_eat time_to_sleep [meals_needed]\ne.g.:\n./philo 4 410 200 200 [5]\n");
	}
	return (0);	
}
