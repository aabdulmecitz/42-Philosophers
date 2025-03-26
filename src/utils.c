/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:42 by aozkaya           #+#    #+#             */
/*   Updated: 2025/03/24 14:51:38 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (!get_end_simulation(philo->data))
	{
		printf(CYAN "%ld %d %s\n" RESET, get_time_ms() \
				- philo->data->start_time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}

int	init_philo_vals(t_data *data, int i)
{
	data->philosophers[i].id = i + 1;
	data->philosophers[i].meals_eaten = 0;
	data->philosophers[i].left_fork = &data->forks[i];
	data->philosophers[i].right_fork = &data->forks[(i + 1)
		% data->num_philosophers];
	data->philosophers[i].data = data;
	data->philosophers[i].last_meal_time = get_time_ms();
	data->philosophers[i].meals_eaten = 0;
	return (0);
}
