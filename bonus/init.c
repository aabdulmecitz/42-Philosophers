/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:51:25 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/19 06:04:51 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int parse_error_check(t_data *data)
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

int init_vars(int argc, char *argv[], t_data *data)
{
    data->end_simulation = 0;
	data->num_philosophers = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
    if (parse_error_check(data))
        return (1);
    if (argc == 6)
	{
		data->num_meals = ft_atol(argv[5]);
		if (data->num_meals <= 0)
			return (printf("Error: Num of meals must be higher than 0.\n"), 1);
	}
	else
		data->num_meals = -1;
    sem_unlink("/forks");
    sem_unlink("/print_lock");
    data->forks = sem_open("/forks", O_CREAT, 0655, data->num_philosophers);
    data->print_lock = sem_open("/print_lock", O_CREAT, 0655, 1);
    if (data->forks == SEM_FAILED || data->print_lock == SEM_FAILED)
        return (printf("Error: Failed to initialize semaphores.\n"), 1);
    data->philosophers = malloc(sizeof(t_philo) * data->num_philosophers);
    if (data->philosophers == NULL)
        return (printf("Error: Failed to allocate memory for philosophers.\n"), 1);
    return 0;
}

int create_philos(t_data *data)
{
    pid_t pid;
    int i;

    i = -1;
    while (++i != data->num_philosophers)
    {
        pid = fork();
        if (pid == -1)
            return(printf("Error: Fork failed.\n"), 1);
        if (pid == 0)
        {
            philo_routine(&data->philosophers[i]);
            exit(0);
        }        
    }
    i = -1;
    while (++i < data->num_philosophers)
        wait(NULL);
    return (0);
}
