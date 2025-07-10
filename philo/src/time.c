/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:44:36 by jhelbig           #+#    #+#             */
/*   Updated: 2025/07/10 11:04:53 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//return milliseconds
long	get_timestamp(void)
{
	struct timeval	tv;
	long			time_in_ms;

	if (gettimeofday(&tv, NULL))
		return (printf("gettime failed\n"), -1);
	time_in_ms = tv.tv_sec * 1e3 + tv.tv_usec / 1e3;
	return (time_in_ms);
}
