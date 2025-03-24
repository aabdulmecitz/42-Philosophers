/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:46 by aozkaya           #+#    #+#             */
/*   Updated: 2025/03/24 14:23:25 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	all_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->philosophers);
	pthread_mutex_destroy(&data->end_sim);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->meal_lock);
}

int	main(int argc, char *argv[])
{
	t_data			data;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	data.forks = forks;
	data.philosophers = philos;
	if (argc != 5 && argc != 6)
		return (0);
	if (init_vars(argc, argv, &data) == -1)
		return (1);
	if (create_philos(&data) == -1)
		return (all_destroy(&data), 1);
	return (usleep(100), all_destroy(&data), 0);
}
