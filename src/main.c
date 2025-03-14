/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:46 by aozkaya           #+#    #+#             */
/*   Updated: 2025/03/12 16:59:06 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	all_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_destroy(data->philosophers[i].left_fork);
		pthread_mutex_destroy(data->philosophers[i].right_fork);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->philosophers);
	free(data->forks);
	
	pthread_mutex_destroy(&data->print_lock);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (0);
	if (init_vars(argc, argv, &data) == -2)
		return (0);
	if (create_philos(&data) == -1)
		return (1);
	return (usleep(100), all_destroy(&data), 0);
}
