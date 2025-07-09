/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:35:29 by mkhallou          #+#    #+#             */
/*   Updated: 2025/07/09 09:43:12 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_print(t_philo *philo, char *msg)
{
	if (!msg || !philo)
		return ;
	if (pthread_mutex_lock(&philo->data->write_lock) != 0)
		return ;
	if (!get_dead_flag(philo->data))
		printf("%lld %d %s\n", get_current_time() - philo->start_time,
			philo->id, msg);
	if (pthread_mutex_unlock(&philo->data->write_lock) != 0)
		return ;
	return ;
}

void	ft_think(t_philo *philo)
{
	if (get_dead_flag(philo->data) || philo->num_of_philos == 1)
		return ;
	my_print(philo, "is thinking");
	return ;
}

void	eat_util(t_philo *philo)
{
	my_print(philo, "is eating");
	set_last_meal(philo, get_current_time());
	ft_mysleep(philo->time_to_eat, philo->data);
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_eat(t_philo *philo)
{
	if (get_dead_flag(philo->data))
		return ;
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->r_fork);
		my_print(philo, "taken a fork");
		pthread_mutex_lock(philo->l_fork);
		my_print(philo, "taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		my_print(philo, "taken a fork");
		pthread_mutex_lock(philo->r_fork);
		my_print(philo, "taken a fork");
	}
	if (get_dead_flag(philo->data))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	eat_util(philo);
}

void	ft_sleep(t_philo *philo)
{
	if (get_dead_flag(philo->data) || philo->num_of_philos == 1)
		return ;
	my_print(philo, "is sleeping");
	ft_mysleep(philo->time_to_sleep, philo->data);
	return ;
}
