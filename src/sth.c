/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sth.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 05:25:50 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/06 20:27:57 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>
#include <limits.h>

int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

long ft_atol(const char *str) {
    long result = 0;
    int is_negative = 0;

    if (!str || *str == '\0')
        return (printf("Error: Input string is NULL or empty.\n"), -1);
    if (*str == '-' || *str == '+') {
        if (*str == '-') is_negative = 1;
        str++;
    }
    if (!is_digit(*str))
        return (printf("Error: Input contains invalid characters.\n"), -1);
    while (*str && is_digit(*str)) {
        result = (result * 10) + (*str - '0');
        if ((!is_negative && result > INT_MAX) || 
            (is_negative && -result < INT_MIN))
            return (printf("Error: Integer overflow.\n"), -1);
        str++;
    }
    return is_negative ? -result : result;
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
