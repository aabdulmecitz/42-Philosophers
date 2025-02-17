/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:11:57 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/17 21:48:37 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <limits.h>

long    get_time_ms()
{
    struct timeval tv;
	long	result;
    
	gettimeofday(&tv, NULL);
	result = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return result;
}

void    custom_sleep(int ms)
{
    long	start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
		usleep(100);
}

void    print_log(t_philo *philo, char *msg)
{
    sem_wait(&philo->data->print_lock);
    if (!philo->data->end_simulation)
        printf(CYAN"%ld %d %s\n"RESET, get_time_ms() - philo->data->start_time, 
            philo->id, msg);
    sem_post(&philo->data->print_lock);
}	