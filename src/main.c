/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:46 by aozkaya           #+#    #+#             */
/*   Updated: 2025/01/30 18:18:14 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, const char *argv[])
{
    t_simulation *simulation;

    init_simulation(simulation, argc, argv);
    init_philosophers(simulation);
    return 0;
}

// ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> ?<number_of_times_each_philosopher_must_eat>