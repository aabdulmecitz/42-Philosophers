/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 04:24:23 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/07 17:39:25 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void philo_is_eating(t_philo *philo)
{
    if (philo->id % 2 == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_log(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_log(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        print_log(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        print_log(philo, "has taken a fork");
    }
}

void	*philo_routine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	
	if (philo->id % 2 == 0)
		usleep(1000);
		
	while (!philo->data->end_simulation)
	{
		print_log(philo, "is thinking");
		philo_is_eating(philo);
		
		if (philo->data->end_simulation)
		{
		    pthread_mutex_unlock(philo->left_fork);
		    pthread_mutex_unlock(philo->right_fork);
		    break;
		}
		
		print_log(philo, "is eating");
		philo->last_meal_time = get_time_ms();
		philo->meals_eaten++;
		custom_sleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		
		if (philo->data->end_simulation)
		    break;
		    
		print_log(philo, "is sleeping");
		custom_sleep(philo->data->time_to_sleep);
	}
	return (NULL);
}


void    *monitor_routine(void *arg)
{
    t_data *data;
    int i;
    data = (t_data *)arg;
    
    while (1)
    {
        i = 0;
        while (i < data->num_philosophers)
        {
            if (get_time_ms() - data->philosophers[i].last_meal_time > data->time_to_die)
            {
                pthread_mutex_lock(&data->print_lock);
                printf(RED"%ld %d died\n"RESET, get_time_ms() - data->start_time, 
                    data->philosophers[i].id);
                data->end_simulation = 1;
                pthread_mutex_unlock(&data->print_lock);
                
                // Tüm filozofların thread'lerini bekle
                for (int j = 0; j < data->num_philosophers; j++)
                {
                    pthread_join(data->philosophers[j].thread, NULL);
                }
                return (NULL);
            }
            i++;
        }
        if (data->end_simulation)
            return (NULL);
        usleep(100);
    }
    return (NULL);
}
