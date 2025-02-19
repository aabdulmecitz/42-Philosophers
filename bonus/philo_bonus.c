/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:37 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/19 06:09:41 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int 	philo_is_eating(void *arg, long *last_meal_time)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	sem_wait(&philo->data->forks[philo->id]);
	sem_wait(&philo->data->forks[(philo->id + 1) % philo->data->num_philosophers]);
	print_log(philo, "is eating");
	philo->meals_eaten++;
	custom_sleep(philo->data->time_to_eat);
	*last_meal_time = get_time_ms();
	return(0);
}

void	*philo_routine(void *arg)
{
	t_philo *philo;
	long *last_meal_time;
	
	philo = (t_philo *)arg; 
	*last_meal_time = get_time_ms();
	philo->meals_eaten = 0;
	while (!philo->data->end_simulation && philo->data->num_meals)
	{
		philo_is_eating(philo, last_meal_time);
		sem_post(&philo->data->forks[philo->id]);
        sem_post(&philo->data->forks[(philo->id + 1) % philo->data->num_philosophers]);
        print_log(philo, "is sleeping");
        custom_sleep(philo->data->time_to_sleep);
		print_log(philo, "is thinking");
        if (get_time_ms() - *last_meal_time > philo->data->time_to_die)
        {
            print_log(philo, "died");
            philo->data->end_simulation = 1;
            break;
        }
	}
	return (NULL);
}
