/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:46 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/06 21:06:34 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void allocate_resources(t_data *data, t_philo **philos)
{
    *philos = malloc(sizeof(t_philo) * data->num_philosophers);
    if (!*philos)
    {
        printf(RED "Memory allocation failed for philosophers!\n" RESET);
        exit(1);
    }
    data->philosophers = *philos;
}

void free_resources(t_philo *philos)
{
    free(philos);
}

int main(int argc, char *argv[])
{
    t_data data;
    t_philo *philos;
    pthread_t monitor_thread;
    pthread_t threads[PHILO_MAX];
    int i;


    if (argc < 5 || argc > 6)
    {
        printf("Error: Incorrect number of arguments.\n");
        return (1);
    }
    if (parse_args(argc, argv, &data) == 1)
        return (1);
    initialize_forks(&data);
    allocate_resources(&data, &philos);
    data.end_simulation = 0;
    create_philo_threads(&data, philos, threads);
    pthread_create(&monitor_thread, NULL, monitor_routine, &data);
    i = 0;
    while (i < data.num_philosophers)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
    pthread_join(monitor_thread, NULL);
    free_resources(philos);
    return (0);
}

// ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> ?<number_of_times_each_philosopher_must_eat>