/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:30:14 by mkhallou          #+#    #+#             */
/*   Updated: 2025/07/08 15:48:20 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handel_single_ph(t_philo *philo)
{
	my_print(philo, "taken a fork");
	return ;
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->num_of_philos == 1)
		return (handel_single_ph(philo), NULL);
	while (!get_dead_flag(philo->data))
	{
		if (philo->id % 2 == 0)
		{
			ft_sleep(philo);
			ft_think(philo);
			ft_eat(philo);
		}
		else
		{
			ft_eat(philo);
			ft_sleep(philo);
			ft_think(philo);
		}
		usleep(500);
	}
	return (NULL);
}

void	*monitor(void *args)
{
	t_main	*data;
	int		i;

	data = (t_main *)args;
	while (1)
	{
		i = 0;
		check_full(data);
		while (i < data->philos->num_of_philos)
		{
			if (get_current_time()
				- (size_t)get_last_meal(&data->philos[i])
				>= data->philos->time_to_die)
			{
				my_print(data->philos, "dead");
				return (set_dead_flag(data, 1), NULL);
			}
			if (get_meals_eaten(data) == 1)
				return (set_dead_flag(data, 1), NULL);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

int	creat_thread(t_main *data)
{
	int			i;
	pthread_t	monitor_th;

	i = 0;
	data->dead_flag = 0;
	data->full_flag = -1;
	while (i < data->philos->num_of_philos)
	{
		data->philos[i].data = data;
		if (pthread_create(&data->philos[i].thread, NULL, &routine,
				&data->philos[i]) != 0)
			return (exit_error("Failed to create thread"), 1);
		++i;
	}
	if (pthread_create(&monitor_th, NULL, monitor, data) != 0)
		return (exit_error("Failed to create thread"), 1);
	i = -1;
	while (++i < data->philos->num_of_philos)
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (exit_error("Failed to join thread"), 1);
	if (pthread_join(monitor_th, NULL) != 0)
		return (exit_error("Failed to join thread"), 1);
	if (data->dead_flag == 1)
		clean_up(data);
	return (0);
}
