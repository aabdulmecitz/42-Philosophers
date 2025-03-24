/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:32 by aozkaya           #+#    #+#             */
/*   Updated: 2025/03/24 14:29:51 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 500
# define INT_MAX 2147483647
# define INT_MIN -2147483648

// Colors
# define CYAN "\033[1;36m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
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
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	end_sim;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	struct s_philo	*philosophers;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}					t_philo;

int					init_vars(int argc, char *argv[], t_data *data);
int					create_philos(t_data *data);
long				ft_atol(const char *str);
int					initialize_forks(t_data *data);
void				*philo_routine(void *arg);
void				*monitor_routine(void *arg);
void				print_log(t_philo *philo, char *msg);
void				custom_sleep(int ms);
long				get_time_ms(void);
void				take_forks(t_philo *philo);
int					get_end_simulation(t_data *data);
int					set_end_simulation(t_data *data, int value);
int					get_meal(t_data *data);
int					set_meal(t_data *data, int value);
int					init_philo_vals(t_data *data, int i);

#endif
