/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:51:25 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/07 19:00:56 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
}

static int parse_error_check(t_data *data)
{
    if (data->num_philosophers <= 0)
		return (printf("Error: Num of philos must be higher than 0.\n"), 1);
	if (data->time_to_die <= 0)
		return (printf("Error: Time to die must be higher than 0.\n"), 1);
	if (data->time_to_eat <= 0)
		return (printf("Error: Time to eat must be higher than 0.\n"), 1);
	if (data->time_to_sleep <= 0)
		return (printf("Error: Time to sleep must be higher than 0.\n"), 1);
    return (0);
}


int init_vars(int argc, char *argv[], t_data *data)
{
    data->end_simulation = 0;
	data->num_philosophers = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
    if (parse_error_check(data))
        return 1;
    if (argc == 6)
	{
		data->num_meals = ft_atol(argv[5]);
		if (data->num_meals <= 0)
			return (printf("Error: Num of meals must be higher than 0.\n"), 1);
	}
	else if (argc == 5)
		data->num_meals = 0;
	else
		return (printf("ERROR: Incorrect number of arguments.\n"), 1);
    pthread_mutex_init(&data->print_lock, NULL);
    data->philosophers = malloc(sizeof(t_philo) * data->num_philosophers);
    if (!(data->philosophers))
        return (2);    
    
    
    return 0;
}

int create_philos(t_data *data)
{
    int	i;
    pthread_t monitor_thread;
    
    i = 0;
    initialize_forks(data);
    
    data->start_time = get_time_ms();
    
    // Önce filozofları oluştur
    while (i < data->num_philosophers)
    {
        data->philosophers[i].id = i + 1;
        data->philosophers[i].left_fork = &data->forks[i];
        data->philosophers[i].right_fork = &data->forks[(i + 1) % data->num_philosophers];
        data->philosophers[i].data = data;
        data->philosophers[i].last_meal_time = get_time_ms();
        data->philosophers[i].meals_eaten = 0;
        if (pthread_create(&data->philosophers[i].thread, NULL, \
                &philo_routine, &(data->philosophers[i])))
            return -1;
        i++;
    }

    // Sonra monitor thread'i oluştur
    if (pthread_create(&monitor_thread, NULL, monitor_routine, data))
        return -1;
    
    // Monitor thread'i bekle
    pthread_join(monitor_thread, NULL);
    
    // Monitor thread bittiğinde tüm filozofları bekle
    i = 0;
    while (i < data->num_philosophers)
    {
        pthread_join(data->philosophers[i].thread, NULL);
        i++;
    }
    
    return (0);
}
