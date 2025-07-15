#include "philo_bonus.h"

void my_print(t_philo *philo, char *msg)
{
    if(!philo || !msg)
        return ;
    sem_wait(philo->print);
    printf("%lld %d %s\n", get_current_time() - philo->start_time, philo->id, msg);
    sem_post(philo->print);
    return ;
}

void ft_eat(t_philo *philo)
{
     sem_wait(philo->forks);
    my_print(philo, "has taken a fork");
    sem_wait(philo->forks);
    my_print(philo, "has taken a fork");
    my_print(philo, "is eating");
    philo->last_meal = get_current_time();
    philo->meals_eaten++;
    ft_mysleep(philo->time_to_eat);
    sem_post(philo->forks);
    sem_post(philo->forks);
    return ;
}

void ft_clean(t_data *data)
{
    sem_close(data->forks);
    sem_unlink("/forks");
    sem_close(data->print);
    sem_unlink("/print");
    sem_close(data->meals);
    sem_unlink("/meals");
    free(data->philos);
}