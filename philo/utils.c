/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:26:36 by mkhallou          #+#    #+#             */
/*   Updated: 2025/07/17 15:32:03 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_error(char *str)
{
	printf("%s\n", str);
	return ;
}

void	ft_destroy_mut(t_main *data, int flag, int i)
{
	free(data->forks);
	free(data->philos);
	if (flag == 1)
		while (i)
			pthread_mutex_destroy(&data->forks[i--]);
	else if (flag >= 2)
	{
		while (i)
			pthread_mutex_destroy(&data->forks[i--]);
		if (flag == 3)
			pthread_mutex_destroy(&data->dead_lock);
		else if (flag == 4)
			pthread_mutex_destroy(&data->meal_lock);
		else if (flag == 5)
			pthread_mutex_destroy(&data->write_lock);
	}
	return ;
}

void	clean_up(t_main *data)
{
	int	i;

	if (!data)
		return ;
	i = -1;
	while (++i < data->philos->num_of_philos)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->full_lock);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	return ;
}

void	check_full(t_main *data)
{
	int	i;
	int	count;

	if (get_dead_flag(data))
		return ;
	i = -1;
	count = 0;
	while (++i < data->philos->num_of_philos)
	{
		pthread_mutex_lock(data->philos[i].meal_lock);
		if (data->philos[i].num_times_to_eat > 0
			&& data->philos[i].meals_eaten >= data->philos[i].num_times_to_eat)
			count++;
		pthread_mutex_unlock(data->philos[i].meal_lock);
	}
	if (count == data->philos->num_of_philos)
		set_meals_eaten(data, 1);
	return ;
}
