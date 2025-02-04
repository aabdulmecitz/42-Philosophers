/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 04:24:23 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/04 13:41:29 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void philo_is_eating(t_philo *philo)
{
    if (philo->id % 2 == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_log(philo, "is taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_log(philo, "is taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        print_log(philo, "is taken a fork");
        pthread_mutex_lock(philo->left_fork);
        print_log(philo, "is taken a fork");
    }
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (philo->data->end_simulation == 0)
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
    int i;
    params = (t_data *)arg;
    while ((params->end_simulation) == 0)
    {
        i = 0;
        while (i < params->num_philosophers)
        {
            if (get_time_ms() - params->philosophers[i].last_meal_time > \
params->time_to_die)
            {
                print_log(&(params->philosophers[i]),"died");
                (params->end_simulation) = 1;
                return (NULL);
            }
            if (params->num_meals > 0 && 
            params->philosophers[i].meals_eaten >= params->num_meals)
            {
                (params->end_simulation) = 1;
                return (NULL);
            }
            
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}