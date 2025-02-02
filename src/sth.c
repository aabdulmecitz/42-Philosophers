/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sth.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 05:25:50 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/02 05:34:41 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	result;

	if (!str)
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
    if (result <= INT_MIN || result >= INT_MAX)
        return (-1);
	return (result);
}

long    get_time_ms()
{
    
}

void    custom_sleep(int ms)
{
    
}

void    print_log(t_philo *philo, char *msg)
{
    
}

void    err(char *msg)
{
    
}