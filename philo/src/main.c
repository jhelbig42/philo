/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:28:12 by jhelbig           #+#    #+#             */
/*   Updated: 2025/06/27 08:12:01 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		//parse input
		//set table
		//have meal
		//clean
	}
	else
	{
		printf("wrong input\nUse should be:\n./philo philo_nb time_to_die time_to_eat time_to_sleep [meals_needed]\ne.g.:\n./philo 4 410 200 200 [5]\n");
	}
	return (0);	
}
