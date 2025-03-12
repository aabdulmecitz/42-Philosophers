/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:42 by aozkaya           #+#    #+#             */
/*   Updated: 2025/03/12 11:18:49 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <limits.h>

long	get_time_ms(void)
{
	struct timeval	tv;
	long			result;

	gettimeofday(&tv, NULL);
	result = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (result);
}

void	custom_sleep(int ms)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
		usleep(100);
}

void	print_log(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_lock);
	if (!philo->data->end_simulation)
	{
		printf(CYAN "%ld %d %s\n" RESET, get_time_ms()
				- philo->data->start_time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}
