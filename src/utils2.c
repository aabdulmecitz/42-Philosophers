/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:58:52 by aozkaya           #+#    #+#             */
/*   Updated: 2025/03/24 14:24:02 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_meal(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->meal_lock);
	i = data->num_meals;
	pthread_mutex_unlock(&data->meal_lock);
	return (i);
}

int	set_meal(t_data *data, int value)
{
	pthread_mutex_lock(&data->meal_lock);
	data->num_meals = value;
	pthread_mutex_unlock(&data->meal_lock);
	return (value);
}

int	get_end_simulation(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->end_sim);
	i = data->end_simulation;
	pthread_mutex_unlock(&data->end_sim);
	return (i);
}

int	set_end_simulation(t_data *data, int value)
{
	pthread_mutex_lock(&data->end_sim);
	data->end_simulation = value;
	pthread_mutex_unlock(&data->end_sim);
	return (value);
}
