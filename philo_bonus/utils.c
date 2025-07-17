/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:00:51 by mkhallou          #+#    #+#             */
/*   Updated: 2025/07/17 13:25:39 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	exit_error(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	clean_sem(t_data *data, int flag)
{
	if (flag == 1)
	{
		sem_close(data->forks);
		sem_unlink("/forks");
	}
	else if (flag == 2)
	{
		sem_close(data->forks);
		sem_unlink("/forks");
		sem_close(data->print);
		sem_unlink("/print");
	}
	else if (flag == 3)
	{
		sem_close(data->forks);
		sem_unlink("/forks");
		sem_close(data->print);
		sem_unlink("/print");
		sem_close(data->meals);
		sem_unlink("/meals");
	}
}

void	ft_unlink(void)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/meals");
	sem_unlink("/meal_lock");
	return ;
}
