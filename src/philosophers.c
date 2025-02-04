/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 04:24:23 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/04 05:23:54 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void philo_is_eating(t_philo *philo)
{
    if (philo->id % 2 == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_log(philo, "is taken left fork");
        pthread_mutex_lock(philo->right_fork);
        print_log(philo, "is taken right fork");
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        print_log(philo, "is taken right fork");
        pthread_mutex_lock(philo->left_fork);
        print_log(philo, "is taken left fork");
    }
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		print_log(philo, "is thinking");
		philo_is_eating(philo);
		print_log(philo, "is eating");
		philo->last_meal_time = get_time_ms();
		philo->meals_eaten++;
		custom_sleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_log(philo, "is sleeping");
		custom_sleep(philo->data->time_to_sleep);
	}
	return (NULL);
}


void    *monitor_routine(void *arg)
{
    t_data *params;
    
    params = (t_data *)arg;
    if (!params->end_simulation)
    {
        int i;

        i = 0;
        while (i++ < params->num_philosophers)
        {
            if (get_time_ms() - params->philosophers[i].last_meal_time > \
params->time_to_die)
            {
                print_log(&params->philosophers[i],"died");
                *params->end_simulation = 1;
                return (NULL);
            }
            if (params->num_meals > 0 && 
            params->philosophers[i].meals_eaten >= params->num_meals)
            {
                *params->end_simulation = 1;
                return (NULL);
            }
            
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}