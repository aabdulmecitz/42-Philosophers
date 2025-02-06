/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sth.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 05:25:50 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/06 19:36:24 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	result;

	if (str == NULL)
	{
		printf("Error: Input string is NULL.\n");
		return (-1);
	}
	if (*str == '+')
		str++;
	if (*str < '0' || *str > '9')
	{
		printf("Error: Input contains invalid characters.\n");
		return (-1);
	}
	result = 0;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		result = (result * 10) + (*str - '0');
        if (result <= INT_MIN || result >= INT_MAX)
            return (-1);
		str++;
	}
	return (result);
}

long    get_time_ms()
{
    struct timeval *tv;
	long	result;
	tv = malloc(sizeof(struct timeval));
	gettimeofday(tv, NULL);
	result = (tv->tv_sec * 1000) + (tv->tv_usec / 1000);
	free(tv);
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
    pthread_mutex_lock(&philo->data->print_lock);
	printf(CYAN"%zu %d %s\n"RESET, get_time_ms() - philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
}	
