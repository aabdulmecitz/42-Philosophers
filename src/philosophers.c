/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 04:24:23 by aozkaya           #+#    #+#             */
/*   Updated: 2025/03/12 12:04:42 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_is_eating(t_philo *philo)
{
	if (philo->data->num_philosophers == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_log(philo, "has taken a fork");
		while (!philo->data->end_simulation)
			usleep(100);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	take_forks(philo);
	pthread_mutex_lock(&philo->data->print_lock);
	if (!philo->data->end_simulation)
	{
		philo->last_meal_time = get_time_ms();
		printf(CYAN "%ld %d is eating\n" RESET, \
			get_time_ms() - philo->data->start_time, philo->id);
		philo->meals_eaten++;
	}
	pthread_mutex_unlock(&philo->data->print_lock);
	custom_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal_time = get_time_ms();
	if (philo->id % 2 == 0)
		usleep(100);
	while (!philo->data->end_simulation)
	{
		print_log(philo, "is thinking");
		philo_is_eating(philo);
		if (philo->data->end_simulation)
			break ;
		print_log(philo, "is sleeping");
		custom_sleep(philo->data->time_to_sleep);
	}
	return (NULL);
}

static int	check_death(t_data *data, int i, long current_time)
{
	if ((current_time
			- data->philosophers[i].last_meal_time) > data->time_to_die)
	{
		pthread_mutex_lock(&data->print_lock);
		if (!data->end_simulation)
		{
			printf(RED "%ld %d died\n" RESET, \
				current_time - data->start_time, data->philosophers[i].id);
			data->end_simulation = 1;
		}
		pthread_mutex_unlock(&data->print_lock);
		return (1);
	}
	return (0);
}

static int	check_meals(t_data *data)
{
	int	i;
	int	all_ate_enough;

	i = 0;
	all_ate_enough = 1;
	while (i < data->num_philosophers)
	{
		if (data->num_meals > 0 && \
			data->philosophers[i].meals_eaten < data->num_meals)
			all_ate_enough = 0;
		i++;
	}
	if (data->num_meals > 0 && all_ate_enough)
	{
		pthread_mutex_lock(&data->print_lock);
		data->end_simulation = 1;
		pthread_mutex_unlock(&data->print_lock);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	long	current_time;

	data = (t_data *)arg;
	usleep(100);
	while (!data->end_simulation)
	{
		i = 0;
		while (i < data->num_philosophers)
		{
			current_time = get_time_ms();
			if (check_death(data, i, current_time))
				return (NULL);
			i++;
		}
		if (check_meals(data))
			return (NULL);
		usleep(50);
	}
	return (NULL);
}
