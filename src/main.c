/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:46 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/04 06:22:21 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
    t_data *data;
    t_philo *philos;
    pthread_t   *threads;
    pthread_t   *monitor_thread;
    int i;
    
    if (argc < 5 || argc > 6)
    {
        return 1;
    }
   	data = malloc(sizeof(t_data));
	if (!data)
		return(0);
    if (parse_args(argv, data) == 1)
        return 1;
    initialize_forks(data);
    philos = malloc(sizeof(t_philo) * data->num_philosophers);
	threads = malloc(sizeof(pthread_t) * data->num_philosophers);
    monitor_thread = malloc(sizeof(pthread_t));
    create_philo_threads(data, philos, threads);
    pthread_create(monitor_thread, NULL, monitor_routine, data);
    i = 0;
    while (i < data->num_philosophers)
    {
        printf(RED"HERE\n"RESET);
        pthread_join(threads[i], NULL);
        i++;
    }
    pthread_join(*monitor_thread, NULL);
    
    return 0;
}

// ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> ?<number_of_times_each_philosopher_must_eat>