/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:37 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/17 21:53:50 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*philo_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	philo->last_meal_time = get_time_ms();
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		print_log(philo, "is thinking");
        sem_wait(philo->data->forks);
        sem_wait(philo->data->forks);
		print_log(philo, "is eating");
        
		philo_is_eating(philo);
		if (philo->data->end_simulation)
            break;
		print_log(philo, "is sleeping");
		custom_sleep(philo->data->time_to_sleep);
	}
	return (NULL);
}