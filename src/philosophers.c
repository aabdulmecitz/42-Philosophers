/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 04:24:23 by aozkaya           #+#    #+#             */
/*   Updated: 2025/03/24 15:07:30 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_is_eating(t_philo *philo)
{
	if (philo->data->num_philosophers == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_log(philo, "has taken a fork");
		while (!get_end_simulation(philo->data))
			usleep(100);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	take_forks(philo);
	pthread_mutex_lock(&philo->data->print_lock);
	if (!get_end_simulation(philo->data))
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
	while (!get_end_simulation(philo->data))
	{
		print_log(philo, "is thinking");
		philo_is_eating(philo);
		if (get_end_simulation(philo->data))
			break ;
		print_log(philo, "is sleeping");
		custom_sleep(philo->data->time_to_sleep);
	}
	return (NULL);
}

static int	check_death(t_data *data, int i, long current_time)
{
	pthread_mutex_lock(&data->print_lock);
	if ((current_time
			- data->philosophers[i].last_meal_time) > data->time_to_die)
	{
		printf(RED "%ld %d died\n" RESET, \
			current_time - data->start_time, data->philosophers[i].id);
		set_end_simulation(data, 1);
		pthread_mutex_unlock(&data->print_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->print_lock);
	return (0);
}

static int	check_meals(t_data *data)
{
	int	i;
	int	all_ate_enough;

	i = 0;
	all_ate_enough = 1;
	pthread_mutex_lock(&data->print_lock);
	while (i < data->num_philosophers)
	{
		if (get_meal(data) > 0 && \
			data->philosophers[i].meals_eaten < get_meal(data))
			all_ate_enough = 0;
		i++;
	}
	pthread_mutex_unlock(&data->print_lock);
	if (get_meal(data) > 0 && all_ate_enough)
	{
		set_end_simulation(data, 1);
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
	while (!get_end_simulation(data))
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
