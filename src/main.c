/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:46 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/02 05:02:40 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, const char *argv[])
{
    t_data *data;
    t_philo *philos;
    pthread_t   *threads;
    pthread_t   monitor_thread;
    
    
   
    if (parse_args(argc, argv, data) == 1)
        return 1;
    initialize_forks(data);
    create_philo_threads(data, philos, threads);
    return 0;
}

// ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> ?<number_of_times_each_philosopher_must_eat>