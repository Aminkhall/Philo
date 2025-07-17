/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:33:22 by mkhallou          #+#    #+#             */
/*   Updated: 2025/07/17 14:15:25 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_sem(t_data *data, char **av)
{
	ft_unlink();
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, ft_atol(av[1]));
	if (data->forks == SEM_FAILED)
		return (free(data->philos), 1);
	data->print = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	if (data->print == SEM_FAILED)
	{
		clean_sem(data, 1);
		return (free(data->philos), 1);
	}
	data->meals = sem_open("/meals", O_CREAT | O_EXCL, 0644, 1);
	if (data->meals == SEM_FAILED)
	{
		clean_sem(data, 2);
		return (free(data->philos), 1);
	}
	data->meal_lock = sem_open("/meal_lock", O_CREAT | O_EXCL, 0644, 1);
	if (data->meal_lock == SEM_FAILED)
	{
		clean_sem(data, 3);
		return (free(data->philos), 1);
	}
	return (0);
}

int	fork_philo(t_data *data, int i)
{
	data->philos[i].pid = fork();
	if (!(data->philos[i].pid))
		philpho_routine(&data->philos[i]);
	if (data->philos[i].pid < 0)
		return (ft_clean(data), 1);
	return (0);
}

int	init_philos(t_data *data, char **av)
{
	int	i;

	i = -1;
	while (++i < ft_atol(av[1]))
	{
		data->philos[i].start_time = get_current_time();
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].num_ph = ft_atol(av[1]);
		data->philos[i].time_to_die = ft_atol(av[2]);
		data->philos[i].time_to_eat = ft_atol(av[3]);
		data->philos[i].time_to_sleep = ft_atol(av[4]);
		if (!av[5])
			data->philos[i].num_to_eat = -1;
		else
			data->philos[i].num_to_eat = ft_atol(av[5]);
		data->philos[i].last_meal = data->philos[i].start_time;
		data->philos[i].forks = data->forks;
		data->philos[i].print = data->print;
		data->philos[i].meals = data->meals;
		data->philos[i].meal_lock = data->meal_lock;
		data->philos[i].data = data;
	}
	return (0);
}
