/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:23:03 by mkhallou          #+#    #+#             */
/*   Updated: 2025/07/08 15:42:24 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*full_lock;
	struct s_main	*data;
}					t_philo;

typedef struct s_main
{
	int				dead_flag;
	int				full_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	full_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_main;

long				ft_atol(const char *str);
int					ft_isdigit(int c);
int					check_input(char **av, int ac);
void				exit_error(char *str);
void				clean_up(t_main *data);
int					get_dead_flag(t_main *data);
long				get_last_meal(t_philo *philo);
int					get_meals_eaten(t_main *data);
void				set_dead_flag(t_main *data, int val);
void				set_last_meal(t_philo *philo, long val);
void				set_meals_eaten(t_main *data, int val);
int					creat_thread(t_main *data);
int					init_philo(t_main *data, char **av);
void				ft_sleep(t_philo *philo);
void				ft_eat(t_philo *philo);
void				ft_think(t_philo *philo);
void				my_print(t_philo *philo, char *msg);
long long			get_current_time(void);
void				ft_mysleep(time_t time);
void				check_full(t_main *data);

#endif