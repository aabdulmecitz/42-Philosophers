/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:42:56 by aozkaya           #+#    #+#             */
/*   Updated: 2025/04/12 23:47:23 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (*str)
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

int	all_is_digit(char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (2);
			j++;
		}
		i++;
	}
	return (0);
}
