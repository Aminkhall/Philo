/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:23:03 by mkhallou          #+#    #+#             */
/*   Updated: 2025/06/30 19:55:28 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_data	t_data;

// typedef struct s_fork
// {
// 	pthread_mutex_t		mutex;
// 	int					fork_id;
// }						t_fork;

typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
    pthread_mutex_t		*left_fork;
    pthread_mutex_t		*right_fork;
	long				last_meal_time;
	int					count_meal;
}						t_philo;


struct					s_data
{
	int					nbr_philo;
	long				time_die;
	long				time_eat;
	long				time_sleep;
	long				must_eat;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write;
	pthread_mutex_t		stop;
};

long					ft_atol(const char *str);
int						ft_isdigit(int c);
int						check_input(char **av, int ac);
void					exit_error(char *str);
