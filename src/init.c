/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:51:25 by aozkaya           #+#    #+#             */
/*   Updated: 2025/03/24 14:03:45 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int initialize_forks(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philosophers)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&data->forks[i]);
            return (-1);
        }
        i++;
    }
    data->start_time = get_time_ms();
    return (0);
}

static int	parse_error_check(t_data *data)
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

int	init_vars(int argc, char *argv[], t_data *data)
{
	data->num_philosophers = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->philosophers = malloc(sizeof(t_philo) * data->num_philosophers);
	if (!data->philosophers)
		return (printf("Error: Malloc failed.\n"), 1);
	if (parse_error_check(data))
		return (-2);
	if (argc == 6)
	{
		data->num_meals = ft_atol(argv[5]);
		if (data->num_meals <= 0)
			return (printf("Error: Num of meals must be higher than 0.\n"), 2);
	}
	else if (argc == 5)
		data->num_meals = 0;
	else
		return (printf("ERROR: Incorrect number of arguments.\n"), 2);
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->end_sim, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	data->end_simulation = set_end_simulation(data, 0);
	return (0);
}

int	create_philos(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = -1;
	if (initialize_forks(data) != 0)
		return (-1);
	while (++i < data->num_philosophers)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].meals_eaten = data->num_meals;
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[(i + 1)
			% data->num_philosophers];
		data->philosophers[i].data = data;
		data->philosophers[i].last_meal_time = get_time_ms();
		data->philosophers[i].meals_eaten = 0;
		
		// Add delay between thread creation
		//usleep(100);
		
		if (pthread_create(&data->philosophers[i].thread, NULL, &philo_routine,
				&(data->philosophers[i])))
		{
			set_end_simulation(data, 1);
			return (-1);
		}
	}

	//usleep(100); // Add delay before monitor thread
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data))
	{
		set_end_simulation(data, 1);
		return (-1);
	}

	pthread_join(monitor_thread, NULL);
	i = -1;
	while (++i < data->num_philosophers)
		pthread_join(data->philosophers[i].thread, NULL);
	return (0);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_log(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_log(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
	}
}
