/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:32:02 by mkhallou          #+#    #+#             */
/*   Updated: 2025/07/08 17:43:28 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_main(t_main *data, int num_philo)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * num_philo);
	if (!data->forks)
		return (exit_error("Somting wrong with malloc"), 1);
	i = 0;
	while (i < num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (exit_error("Failed to initialize mutex"), 1);
		++i;
	}
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (exit_error("Failed to initialize mutex"), 1);
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		return (exit_error("Failed to initialize mutex"), 1);
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (exit_error("Failed to initialize mutex"), 1);
	if (pthread_mutex_init(&data->full_lock, NULL) != 0)
		return (exit_error("Failed to initialize mutex"), 1);
	return (0);
}

void	init_var(t_main *data, char **av, int i)
{
	data->philos[i].dead_lock = &data->dead_lock;
	data->philos[i].meal_lock = &data->meal_lock;
	data->philos[i].write_lock = &data->write_lock;
	data->philos[i].full_lock = &data->full_lock;
	data->philos[i].r_fork = &data->forks[i];
	data->philos[i].l_fork = &data->forks[(i + ft_atol(av[1]) - 1)
		% ft_atol(av[1])];
	if (av[5])
		data->philos[i].num_times_to_eat = ft_atol(av[5]);
	else
		data->philos[i].num_times_to_eat = -1;
}

int	init_philo(t_main *data, char **av)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * ft_atol(av[1]));
	if (!data->philos)
		return (exit_error("Somting wrong with malloc"), 1);
	if (init_main(data, ft_atol(av[1])) == 1)
		return (1);
	i = 0;
	while (i < ft_atol(av[1]))
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].num_of_philos = ft_atol(av[1]);
		data->philos[i].time_to_die = ft_atol(av[2]);
		data->philos[i].time_to_eat = ft_atol(av[3]);
		data->philos[i].time_to_sleep = ft_atol(av[4]);
		data->philos[i].start_time = get_current_time();
		data->philos[i].last_meal = get_current_time();
		data->philos[i].meals_eaten = 0;
		init_var(data, av, i);
		++i;
	}
	return (0);
}
