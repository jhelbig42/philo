/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:45:11 by jhelbig           #+#    #+#             */
/*   Updated: 2025/07/10 11:16:33 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	error(char *msg)
{
	printf("%s\n", msg);
	return ;
}

void	set_bool_mtx(pthread_mutex_t *mtx, bool *var, bool val)
{
	pthread_mutex_lock(mtx);
	*var = val;
	pthread_mutex_unlock(mtx);
}

void	set_long_mtx(pthread_mutex_t *mtx, long *var, long val)
{
	pthread_mutex_lock(mtx);
	*var = val;
	pthread_mutex_unlock(mtx);
}

bool	get_bool_mtx(pthread_mutex_t *mtx, bool *var)
{
	bool	ret;

	pthread_mutex_lock(mtx);
	ret = *var;
	pthread_mutex_unlock(mtx);
	return (ret);
}

long	get_long_mtx(pthread_mutex_t *mtx, long *var)
{
	long	ret;

	pthread_mutex_lock(mtx);
	ret = *var;
	pthread_mutex_unlock(mtx);
	return (ret);
}
