/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:32 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/06 19:34:53 by aozkaya          ###   ########.fr       */
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

//Colors
# define CYAN "\033[36m"
# define RED "\033[31m"
# define GREEN "\032[31m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

 
typedef struct s_data
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	int				end_simulation;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	struct s_philo *philosophers;
}					t_data;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long long			last_meal_time;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_data		*data;
	
}					t_philo;


long	ft_atol(const char *str);
int		parse_args(int argc, char *argv[], t_data *data);
void	create_philo_threads(t_data *data, t_philo *philos, pthread_t *threads);
void	*philo_routine(void *arg);
void    *monitor_routine(void *arg);
void	initialize_forks(t_data *data);
long	get_time_ms();
void	custom_sleep(int ms);
void	print_log(t_philo *philo, char *msg);
void init_philos(t_philo *philos, t_data data);

#endif