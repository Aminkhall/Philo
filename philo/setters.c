/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:25:38 by mkhallou          #+#    #+#             */
/*   Updated: 2025/07/08 15:26:31 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_meals_eaten(t_main *data, int val)
{
	pthread_mutex_lock(&data->full_lock);
	data->full_flag = val;
	pthread_mutex_unlock(&data->full_lock);
	return ;
}

void	set_last_meal(t_philo *philo, long val)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = val;
	pthread_mutex_unlock(philo->meal_lock);
}

void	set_dead_flag(t_main *data, int val)
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead_flag = val;
	pthread_mutex_unlock(&data->dead_lock);
}
