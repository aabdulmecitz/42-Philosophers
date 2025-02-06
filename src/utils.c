/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:42 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/06 20:56:20 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int argc, char *argv[], t_data *data)
{
	data->end_simulation = 0;
	data->num_philosophers = ft_atol(argv[1]);
	if (data->num_philosophers <= 0)
		return (printf("Error: Num of philos must be a positive int.\n"), 1);
	data->time_to_die = ft_atol(argv[2]);
	if (data->time_to_die <= 0)
		return (printf("Error: Time to die must be a positive int.\n"), 1);
	data->time_to_eat = ft_atol(argv[3]);
	if (data->time_to_eat <= 0)
		return (printf("Error: Time to eat must be a positive int.\n"), 1);
	data->time_to_sleep = ft_atol(argv[4]);
	if (data->time_to_sleep <= 0)
		return (printf("Error: Time to sleep must be a positive int.\n"), 1);
	if (argc == 6)
	{
		data->num_meals = ft_atol(argv[5]);
		if (data->num_meals <= 0)
			return (printf("Error: Num of meals must be a positive int.\n"), 1);
	}
	else if (argc == 5)
		data->num_meals = 0;
	else
		return (printf("ERROR: Incorrect number of arguments.\n"), 1);
	return (0);
}

void	initialize_forks(t_data *data)
{
	int i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	while (i < data->num_philosophers)
	{
    	pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_lock, NULL);	
}

void	create_philo_threads(t_data *data, t_philo *philos, pthread_t *threads)
{
	int	i;

	i = 0;
	data->start_time = get_time_ms();
	while (i < data->num_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->num_philosophers];
		philos[i].data = data;
		philos[i].last_meal_time = get_time_ms();
		philos[i].meals_eaten = 0;
		pthread_create(&threads[i], NULL, philo_routine, &philos[i]);
		i++;
	}
}
