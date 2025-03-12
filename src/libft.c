/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:42:56 by aozkaya           #+#    #+#             */
/*   Updated: 2025/03/12 12:16:00 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	long	res;
	int		is_neg;

	res = 0;
	is_neg = 0;
	if (!str || *str == '\0')
		return (printf("Error: Input string is NULL or empty.\n"), -1);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			is_neg = 1;
		str++;
	}
	if (!is_digit(*str))
		return (printf("Error: Input contains invalid characters.\n"), -1);
	while (*str && is_digit(*str))
	{
		res = (res * 10) + (*str - '0');
		if ((res > INT_MAX) || (res < INT_MIN))
			return (printf("Error: Integer overflow.\n"), -1);
		str++;
	}
	if (is_neg)
		return (-res);
	return (res);
}
