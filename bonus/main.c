/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:24:02 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/17 21:28:59 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void all_destroy(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philosophers)
    {
        kill();
        i++;
    }
    // free(data->philosophers);
    pthread_mutex_destroy(&data->print_lock);
}

int main(int argc, char *argv[])
{
    t_data data;

    if (argc != 5 && argc != 6)
        return 0;
    if (init_vars(argc, argv, &data) == 2)
        return (free(data.philosophers), 0);
    if (create_philos(&data) == -1)
        return (1);
    return (usleep(100), all_destroy(&data),0);
}

// 