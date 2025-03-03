/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozkaya <aozkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:32 by aozkaya           #+#    #+#             */
/*   Updated: 2025/02/19 06:34:58 by aozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>


# define PHILO_MAX 300
# define INT_MAX 2147483647
# define INT_MIN -2147483648

// Colors
# define CYAN   "\033[1;36m"
# define RED    "\033[1;31m"
# define GREEN  "\033[1;32m"
# define YELLOW "\033[1;33m"
# define RESET  "\033[0m"

typedef struct s_data
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	int				end_simulation;
	long			start_time;
	sem_t			*forks;
	sem_t			*print_lock;
	struct s_philo	*philosophers;
}					t_data;

typedef struct s_philo
{
	int					id;
	pid_t				pid;
	int					meals_eaten;
	long long			last_meal_time;
	struct s_data		*data;
}					t_philo;

int init_vars(int argc, char *argv[], t_data *data);
int create_philos(t_data *data);
long ft_atol(const char *str);
void	initialize_forks(t_data *data);
void    print_log(t_philo *philo, char *msg);
void    custom_sleep(int ms);
long    get_time_ms();
void	*philo_routine(void *arg);

#endif
