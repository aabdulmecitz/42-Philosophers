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
		
		if (philo->data->end_simulation)
		    break;
		    
		philo_is_eating(philo);
		
		if (philo->data->end_simulation)
		{
		    pthread_mutex_unlock(philo->left_fork);
		    pthread_mutex_unlock(philo->right_fork);
		    break;
		}
		
		print_log(philo, "is eating");
		philo->meals_eaten++;
		custom_sleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		
		if (philo->data->end_simulation)
		    break;
			
		print_log(philo, "is sleeping");
		custom_sleep(philo->data->time_to_sleep);
		
		if (philo->data->end_simulation)
		    break;
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
                data->end_simulation = 1;
                printf(RED"%ld %d died\n"RESET, get_time_ms() - data->start_time, 
                    data->philosophers[i].id);
                pthread_mutex_unlock(&data->print_lock);
                
                // Tüm thread'leri zorla durdur
                for (int j = 0; j < data->num_philosophers; j++)
                {
                    pthread_mutex_unlock(&data->forks[j]);  // Tüm çatalları serbest bırak
                }
                
                // Tüm mutex'leri unlock et
                pthread_mutex_unlock(&data->print_lock);
                
                return (NULL);
            }
            i++;
        }
        
        // Yemek sayısı kontrolü
        if (data->num_meals > 0)
        {
            int all_ate = 1;
            for (int j = 0; j < data->num_philosophers; j++)
            {
                if (data->philosophers[j].meals_eaten < data->num_meals)
                {
                    all_ate = 0;
                    break;
                }
            }
            if (all_ate)
            {
                data->end_simulation = 1;
                return (NULL);
            }
        }
        usleep(100);
    }
    return (NULL);
}
