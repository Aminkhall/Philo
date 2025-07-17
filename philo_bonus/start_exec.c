/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:00:35 by mkhallou          #+#    #+#             */
/*   Updated: 2025/07/17 13:45:27 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	monitor_meals(sem_t *meals, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
		sem_wait(meals);
	exit(1);
}

void	ft_kill(t_data *data, pid_t meal_monitor, char **av)
{
	int	i;
	int	status;

	wait(&status);
	i = -1;
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
	{
		while (++i < ft_atol(av[1]))
			kill(data->philos[i].pid, SIGKILL);
		if (data->philos->num_to_eat != -1 && ft_atol(av[1]) > 1)
			kill(meal_monitor, SIGKILL);
	}
}

void	wait_for_child(t_data *data, char **av)
{
	int	i;

	i = -1;
	while (++i < ft_atol(av[1]))
		waitpid(data->philos[i].pid, NULL, 0);
}

int	start_exec(t_data *data, char **av)
{
	int		i;
	pid_t	meal_monitor;

	data->num_of_philos = ft_atol(av[1]);
	data->philos = malloc(sizeof(t_philo) * ft_atol(av[1]));
	if (!data->philos)
		return (1);
	if (init_sem(data, av) == 1 || init_philos(data, av) == 1)
		return (1);
	if (data->philos->num_to_eat != -1 && ft_atol(av[1]) > 1)
	{
		meal_monitor = fork();
		if (meal_monitor < 0)
			return (ft_clean(data), 1);
		if (meal_monitor == 0)
			monitor_meals(data->meals, data);
	}
	i = -1;
	while (++i < ft_atol(av[1]))
		if (fork_philo(data, i) == 1)
			return (1);
	ft_kill(data, meal_monitor, av);
	wait_for_child(data, av);
	return (0);
}
