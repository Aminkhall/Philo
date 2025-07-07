/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:27:41 by mkhallou          #+#    #+#             */
/*   Updated: 2025/07/07 16:20:07 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_main(t_main *data, int num_philo)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * num_philo);
	if (!data->forks)
		return (exit_error("Somting wrong with malloc"), 1);
	i = 0;
	while (i < num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (exit_error("Failed to initialize mutex"), 1);
		++i;
	}
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (exit_error("Failed to initialize mutex"), 1);
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		return (exit_error("Failed to initialize mutex"), 1);
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (exit_error("Failed to initialize mutex"), 1);
	if (pthread_mutex_init(&data->full_lock, NULL) != 0)
		return (exit_error("Failed to initialize mutex"), 1);
	return (0);
}

long long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	init_philo(t_main *data, char **av)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * ft_atol(av[1]));
	if (!data->philos)
		return (exit_error("Somting wrong with malloc"), 1);
	if (init_main(data, ft_atol(av[1])) == 1)
		return (1);
	i = 0;
	while (i < ft_atol(av[1]))
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].num_of_philos = ft_atol(av[1]);
		data->philos[i].time_to_die = ft_atol(av[2]);
		data->philos[i].time_to_eat = ft_atol(av[3]);
		data->philos[i].time_to_sleep = ft_atol(av[4]);
		data->philos[i].start_time = get_current_time();
		data->philos[i].dead_lock = &data->dead_lock;
		data->philos[i].meal_lock = &data->meal_lock;
		data->philos[i].write_lock = &data->write_lock;
		data->philos[i].write_lock = &data->full_lock;
		data->philos[i].last_meal = get_current_time();
		data->philos[i].meals_eaten = 0;
		data->philos[i].r_fork = &data->forks[i];
		data->philos[i].l_fork = &data->forks[(i + ft_atol(av[1]) - 1)
			% ft_atol(av[1])];
		if (av[5])
			data->philos[i].num_times_to_eat = ft_atol(av[5]);
		else
			data->philos[i].num_times_to_eat = -1;
		++i;
	}
	return (0);
}

int	get_dead_flag(t_main *data)
{
	int	tmp;

	pthread_mutex_lock(&data->dead_lock);
	tmp = data->dead_flag;
	pthread_mutex_unlock(&data->dead_lock);
	return (tmp);
}

void	set_dead_flag(t_main *data, int val)
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead_flag = val;
	pthread_mutex_unlock(&data->dead_lock);
}

long	get_last_meal(t_philo *philo)
{
	long	tmp;

	pthread_mutex_lock(philo->meal_lock);
	tmp = philo->last_meal;
	pthread_mutex_unlock(philo->meal_lock);
	return (tmp);
}

void	set_last_meal(t_philo *philo, long val)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = val;
	pthread_mutex_unlock(philo->meal_lock);
}

void	ft_mysleep(time_t time)
{
	time_t	start;

	start = get_current_time();
	while (get_current_time() - start <= time)
		usleep(500);
}

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
	my_print(philo, "is eating");
	set_last_meal(philo, get_current_time());
	ft_mysleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_sleep(t_philo *philo)
{
	if (get_dead_flag(philo->data) || philo->num_of_philos == 1)
		return ;
	my_print(philo, "is sleeping");
	ft_mysleep(philo->time_to_sleep);
	return ;
}
void	handel_single_ph(t_philo *philo)
{
	my_print(philo, "taken a fork");
	return ;
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->num_of_philos == 1)
		return (handel_single_ph(philo), NULL);
	while (!get_dead_flag(philo->data))
	{
		if (philo->id % 2 == 0)
		{
			ft_sleep(philo);
			ft_think(philo);
			ft_eat(philo);
		}
		else
		{
			ft_eat(philo);
			ft_sleep(philo);
			ft_think(philo);
		}
		usleep(500);
	}
	return (NULL);
}

void	set_meals_eaten(t_main *data, int val)
{
	pthread_mutex_lock(&data->full_lock);
	data->full_flag = val;
	pthread_mutex_unlock(&data->full_lock);
	return ;
}

int	get_meals_eaten(t_main *data)
{
	int	tmp;

	pthread_mutex_lock(&data->full_lock);
	tmp = data->full_flag;
	pthread_mutex_unlock(&data->full_lock);
	return (tmp);
}

void	check_full(t_main *data)
{
	int	i;
	int	count;

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

void	*monitor(void *args)
{
	t_main	*data;
	int		i;

	data = (t_main *)args;
	while (1)
	{
		i = 0;
		check_full(data);
		while (i < data->philos->num_of_philos)
		{
			if (get_current_time()
				- (size_t)get_last_meal(&data->philos[i]) >= data->philos->time_to_die)
			{
				my_print(data->philos, "dead");
				return (set_dead_flag(data, 1), NULL);
			}
			if (get_meals_eaten(data) == 1)
				return (set_dead_flag(data, 1), NULL);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

int	creat_thread(t_main *data)
{
	int			i;
	pthread_t	monitor_th;

	i = 0;
	data->dead_flag = 0;
	data->full_flag = -1;
	while (i < data->philos->num_of_philos)
	{
		data->philos[i].data = data;
		if (pthread_create(&data->philos[i].thread, NULL, &routine,
				&data->philos[i]) != 0)
			return (exit_error("Failed to create thread"), 1);
		++i;
	}
	if (pthread_create(&monitor_th, NULL, monitor, data) != 0)
		return (exit_error("Failed to create thread"), 1);
	i = -1;
	while (++i < data->philos->num_of_philos)
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (exit_error("Failed to join thread"), 1);
	if (pthread_join(monitor_th, NULL) != 0)
		return (exit_error("Failed to join thread"), 1);
	if (data->dead_flag == 1)
		clean_up(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_main	data;

	if (ac != 5 && ac != 6)
		return (exit_error("Wrong input\nEnter valid input ./philo 12 600 200 200 [5]"),
			1);
	if (check_input(av, ac) == 1)
		return (exit_error("Error: All arguments must be positive digits."), 1);
	if (init_philo(&data, av) == 1)
		return (1);
	if (creat_thread(&data) == 1)
		return (1);
	return (0);
}
