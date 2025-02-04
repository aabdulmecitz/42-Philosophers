/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:42 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/04 13:39:50 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(char *argv[], t_data *data)
{
	data->end_simulation = 0;
	data->num_philosophers = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	// if (argc == 6)
	// {
	// 	/* code */
	// 	// num meals burada çekecez yazılmamışsa num meals 0;
	// 	// structlar ayarlanacak unutma
		
	// }
	data->num_meals = ft_atol(argv[5]);
	if (data->num_philosophers != -1 || data->time_to_die != -1 || 
		data->time_to_eat != -1 || data->time_to_sleep != -1 ||
		data->num_meals != 1)
		return 0;
	return 1;
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

