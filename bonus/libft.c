/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:42:56 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/19 06:42:35 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long ft_atol(const char *str)
{
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
    if (is_negative)
        return (-result);
    return (result);
}

