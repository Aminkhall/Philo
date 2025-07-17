/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:00:48 by mkhallou          #+#    #+#             */
/*   Updated: 2025/07/17 14:53:41 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (!philo)
		return (NULL);
	while (1)
	{
		sem_wait(philo->meal_lock);
		if (get_current_time() - philo->last_meal > philo->time_to_die)
		{
			sem_post(philo->meal_lock);
			sem_wait(philo->print);
			printf("%lld %d died\n", get_current_time()
				- philo->start_time, philo->id);
			exit(1);
		}
		sem_post(philo->meal_lock);
		usleep(100);
	}
	return (NULL);
}

void	philpho_routine(t_philo *philo)
{
	pthread_t	thread;

	if (!philo)
		return ;
	pthread_create(&thread, NULL, &monitor, philo);
	pthread_detach(thread);
	while (1)
	{
		ft_eat(philo);
		my_print(philo, "is sleeping");
		ft_mysleep(philo->time_to_sleep);
		my_print(philo, "is thinking");
		if (philo->num_to_eat != -1 && philo->meals_eaten >= philo->num_to_eat)
			break ;
	}
	if (philo->num_to_eat != -1)
		sem_post(philo->meals);
	exit(0);
}
