#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <limits.h>
#include <sys/time.h>
#include <fcntl.h>
# include <pthread.h>



typedef struct s_philo
{
    pid_t pid;
    int id;
    int num_ph;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long last_meal;
    int num_to_eat;
    long start_time;
    int meals_eaten;
    sem_t *forks;
    sem_t *print;
    sem_t *meals;
    sem_t *meal_lock;
    struct s_data *data;
} t_philo;

typedef struct s_data
{
    int num_of_philos;
    int dead_flag;
    sem_t *forks;
    sem_t *print;
    sem_t *meals;
    sem_t *meal_lock;
    t_philo *philos;
} t_data;


int	check_input(char **av, int ac);
void	exit_error(char *str);
long long	get_current_time(void);
void	ft_mysleep(long time);
long	ft_atol(const char *str);
void my_print(t_philo *philo, char *msg);
void philpho_routine(t_philo *philo);
int init_data(t_data *data, char **av);
void ft_eat(t_philo *philo);
void ft_clean(t_data *data);
#endif