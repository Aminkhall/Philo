/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:27:41 by mkhallou          #+#    #+#             */
/*   Updated: 2025/07/09 09:50:01 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_mysleep(time_t time, t_main *data)
{
	time_t	start;

	if (get_current_time() == -1)
		return ;
	start = get_current_time();
	while (get_current_time() - start <= time)
	{
		if (get_dead_flag(data) == 1)
			return ;
		usleep(1000);
	}
}

int	main(int ac, char **av)
{
	t_main	data;

	if (ac != 5 && ac != 6)
		return (exit_error("Wrong input\n"
				"Enter valid input ./philo 12 600 200 200 [5]"), 1);
	if (check_input(av, ac) == 1)
		return (exit_error("Error: All arguments must be positive digits."), 1);
	if (init_philo(&data, av) == 1)
		return (1);
	if (creat_thread(&data) == 1)
		return (1);
	return (0);
}
