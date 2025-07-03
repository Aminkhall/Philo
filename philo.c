/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:27:41 by mkhallou          #+#    #+#             */
/*   Updated: 2025/07/03 15:14:51 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_main(t_main *data, int num_philo)
{
    int i;

    data->forks = malloc(sizeof(t_philo) * num_philo);
    if (!data->forks)
        exit_error("Somting wrong with malloc");
    i = 0;
    while (i < num_philo)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0) {
            fprintf(stderr, "Failed to initialize mutex\n");
            return ;
        }
        ++i;
    }
    
    if (pthread_mutex_init(&data->dead_lock, NULL) != 0) {
        fprintf(stderr, "Failed to initialize mutex\n");
        return ;
    }
    if (pthread_mutex_init(&data->meal_lock, NULL) != 0) {
        fprintf(stderr, "Failed to initialize mutex\n");
        return ;
    }
    if (pthread_mutex_init(&data->write_lock, NULL) != 0) {
        fprintf(stderr, "Failed to initialize mutex\n");
        return ;
    }
}

void init_philo(t_main *data, char **av)
{
    int i;

    data->philos = malloc(sizeof(t_philo) * ft_atol(av[1]));
    if (!data->philos)
        exit_error("Somting wrong with malloc");
    init_main(data, ft_atol(av[1]));
    i = 0;
    while (i < ft_atol(av[1]))
    {
        data->philos->id = i + 1;
        data->philos->meals_eaten = 0;
        data->philos[i].num_of_philos = ft_atol(av[1]);
        data->philos[i].time_to_die = ft_atol(av[2]);
        data->philos[i].time_to_eat = ft_atol(av[3]);
        data->philos[i].time_to_sleep = ft_atol(av[4]);
        data->philos[i].dead_lock = &data->dead_lock;
        data->philos[i].meal_lock = &data->meal_lock;
        data->philos[i].write_lock = &data->write_lock;
        data->philos->r_fork = &data->forks[i];
        data->philos->l_fork = &data->forks[(i + ft_atol(av[1] - 1) % ft_atol(av[1]))];
        if (av[5])
            data->philos->num_times_to_eat = ft_atol(av[5]);
        else
            data->philos->num_times_to_eat = -1;
       ++i;
    }
}

void *routine()
{
    printf("here\n");
    return (0);
}

void creat_thread(t_main *data)
{
    int i;

    i = 0;
    while (i < data->philos->num_of_philos)
    {
        pthread_create(&data->philos[i].thread, NULL, &routine, NULL);
        ++i;
    }
    i = 0;
    while (i < data->philos->num_of_philos)
    {
        pthread_join(data->philos[i].thread, NULL);
        ++i;
    }
    
    
}

int main(int ac, char **av)
{
    t_main data;

    if (ac != 5 && ac != 6)
        exit_error("Wrong input\nEnter valid input ./philo 12 600 200 200 [5]");
    if (check_input(av, ac) == 1)
        exit_error("Error: All arguments must be positive digits.");
    init_philo(&data, av);
    creat_thread(&data);

}
