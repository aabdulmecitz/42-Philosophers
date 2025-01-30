/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:32 by aozkaya           #+#    #+#             */
/*   Updated: 2025/01/30 18:19:06 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 300
# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long long			last_meal_time;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_simulation	*simulation;
	
}					t_philo;

typedef struct s_simulation
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	bool			*dead_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	meal_mutex;
	t_philo			*philosophers;
}					t_simulation;

long	ft_atol(const char *str);
void init_simulation(t_simulation* simulation, int argc, const char *argv[]);
void init_philosophers(t_simulation *simulation);

#endif