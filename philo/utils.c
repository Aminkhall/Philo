/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:26:36 by mkhallou          #+#    #+#             */
/*   Updated: 2025/07/07 16:05:39 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void exit_error(char *str)
{
	printf("%s\n", str);
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
