/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:00:32 by mkhallou          #+#    #+#             */
/*   Updated: 2025/07/17 13:11:11 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	my_print(t_philo *philo, char *msg)
{
	if (!philo || !msg)
		return ;
	sem_wait(philo->print);
	printf("%lld %d %s\n", get_current_time()
		- philo->start_time, philo->id, msg);
	sem_post(philo->print);
	return ;
}

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->forks);
	my_print(philo, "has taken a fork");
	sem_wait(philo->forks);
	my_print(philo, "has taken a fork");
	my_print(philo, "is eating");
	sem_wait(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	sem_post(philo->meal_lock);
	ft_mysleep(philo->time_to_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
	return ;
}

void	ft_clean(t_data *data)
{
	sem_close(data->forks);
	sem_unlink("/forks");
	sem_close(data->print);
	sem_unlink("/print");
	sem_close(data->meals);
	sem_unlink("/meals");
	free(data->philos);
}
