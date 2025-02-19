/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:24:02 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/19 06:34:17 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void all_destroy(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->num_philosophers)
        kill(data->philosophers[i].pid, SIGTERM);
    i = -1;
    while (++i < data->num_philosophers)
        waitpid(data->philosophers[i].pid, NULL, 0);
    sem_close(data->forks);
    sem_close(data->print_lock);
    sem_unlink("/forks");
    sem_unlink("/print_lock");
    free(data->philosophers);
    exit(0);
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
