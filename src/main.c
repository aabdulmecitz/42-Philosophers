/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:46 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/04 13:41:37 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
    t_data data;
    t_philo *philos;
    pthread_t   *threads;
    pthread_t   monitor_thread;
    int i;
//t_datayı *'ını çıkar ve  fonksiyonlara &data koycaz freeye gerek kalmicak
    if (argc < 5 || argc > 6)
    {
        return 1;
    }

    if (parse_args(argv, &data) == 1)
        return 1;
    initialize_forks(&data);
    philos = malloc(sizeof(t_philo) * data.num_philosophers);
    data.philosophers = philos;
	threads = malloc(sizeof(pthread_t) * data.num_philosophers);
    create_philo_threads(&data, philos, threads);
    data.end_simulation = 0;
    pthread_create(&monitor_thread, NULL, monitor_routine, &data);
    i = 0;
    while (i < data.num_philosophers)
    {
        pthread_join(threads[i], NULL);
        //printf(RED"HERE\n"RESET);
        i++;
    }
    pthread_join(monitor_thread, NULL);
    
    return 0;
}

// ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> ?<number_of_times_each_philosopher_must_eat>