/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:23:30 by mkhallou          #+#    #+#             */
/*   Updated: 2025/07/08 15:43:25 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_dead_flag(t_main *data)
{
	int	tmp;

	pthread_mutex_lock(&data->dead_lock);
	tmp = data->dead_flag;
	pthread_mutex_unlock(&data->dead_lock);
	return (tmp);
}

long	get_last_meal(t_philo *philo)
{
	long	tmp;

	pthread_mutex_lock(philo->meal_lock);
	tmp = philo->last_meal;
	pthread_mutex_unlock(philo->meal_lock);
	return (tmp);
}

int	get_meals_eaten(t_main *data)
{
	int	tmp;

	pthread_mutex_lock(&data->full_lock);
	tmp = data->full_flag;
	pthread_mutex_unlock(&data->full_lock);
	return (tmp);
}
