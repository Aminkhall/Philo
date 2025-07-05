/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:27:41 by mkhallou          #+#    #+#             */
/*   Updated: 2025/07/05 18:10:21 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_main(t_main *data, int num_philo)
{
	int	i;

	data->forks = malloc(sizeof(t_philo) * num_philo);
	if (!data->forks)
		exit_error("Somting wrong with malloc");
	i = 0;
	while (i < num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			exit_error("Failed to initialize mutex");
		++i;
	}
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		exit_error("Failed to initialize mutex");
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		exit_error("Failed to initialize mutex");
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		exit_error("Failed to initialize mutex");
}

long long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		exit(1); /// to do
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
// int	ft_usleep(long long ms, t_main *data)
// {
// 	long long	start;

// 	start = get_current_time();
// 	while ((get_current_time() - start) < ms)
// 	{
// 		pthread_mutex_lock(data->philos->dead_lock);
// 		if (*data->philos->dead == 1)
// 		{
// 			pthread_mutex_unlock(data->philos->dead_lock);
// 			break ;
// 		}
// 		pthread_mutex_unlock(data->philos->dead_lock);
// 		usleep(500);
// 	}
// 	return (0);
// }

// long long	get_timestp(long long start_time)
// {
// 	struct timeval	current;

// 	gettimeofday(&current, NULL);
// 	return ((current.tv_sec * 1000 + current.tv_usec / 1000) - start_time);
// }
void	init_philo(t_main *data, char **av)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * ft_atol(av[1]));
	if (!data->philos)
		exit_error("Somting wrong with malloc");
	init_main(data, ft_atol(av[1]));
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
		data->philos[i].r_fork = &data->forks[i];
		data->philos[i].l_fork = &data->forks[(i + ft_atol(av[1]) -1
				% ft_atol(av[1]))];
		if (av[5])
			data->philos[i].num_times_to_eat = ft_atol(av[5]);
		else
			data->philos[i].num_times_to_eat = -1;
		++i;
	}
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
	{
		usleep(100);
	}
}

void	my_print(t_philo *philo, char *msg)
{
	static int	i;

	if (!msg || !philo)
		i++;
	if (i)
		return ;
	else
	{
		pthread_mutex_lock(&philo->data->write_lock);
		printf("%lld %d %s\n", get_current_time() - philo->start_time,
			philo->id, msg);
		pthread_mutex_unlock(&philo->data->write_lock);
	}
}

void ft_think(t_philo *philo)
{
	if (get_dead_flag(philo->data))
		return ;
	my_print(philo, "is thinking");
}

void	ft_eat(t_philo *philo)
{
	if (get_dead_flag(philo->data))
		return ;
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->l_fork);
		my_print(philo, "taken a fork");
		pthread_mutex_lock(philo->r_fork);
		my_print(philo, "taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		my_print(philo, "taken a fork");
		pthread_mutex_lock(philo->l_fork);
		my_print(philo, "taken a fork");
	}
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	my_print(philo, "is eating");
	set_last_meal(philo, get_current_time());
	ft_mysleep(philo->time_to_eat);
}

void	ft_sleep(t_philo *philo)
{
	if (get_dead_flag(philo->data))
		return ;
	my_print(philo, "is sleeping");
	ft_mysleep(philo->time_to_sleep);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!get_dead_flag(philo->data))
	{
		// if (get_dead_flag(philo->data) == 1)
		// 	return (NULL);
		// if (philo->id % 2 == 0)
		// {
		// 	ft_sleep(philo);
		// 	my_print(philo, "is thinking");
		// 	ft_eat(philo);
		// }
		// else
		// {
			ft_eat(philo);
			ft_sleep(philo);
			ft_think(philo);
			
		// }
		usleep(500);
	}
	return (NULL);
}

void	*monitor(void *args)
{
	t_main	*data;
	int		i;

	data = (t_main *)args;
	while (1)
	{
		i = 0;
		while (i < data->philos->num_of_philos)
		{
			if (get_current_time()
				- (size_t)get_last_meal(&data->philos[i]) >= data->philos->time_to_die)
			{
				set_dead_flag(data, 1);
				// pthread_mutex_lock(&data->write_lock);
				// printf("%lld %d dead\n", get_current_time() - data->philos[i].start_time, data->philos[i].id);
				// pthread_mutex_unlock(&data->write_lock);
				my_print(data->philos , "dead");
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	creat_thread(t_main *data)
{
	int			i;
	pthread_t	monitor_th;

	i = 0;
	data->dead_flag = 0;
	while (i < data->philos->num_of_philos)
	{
		data->philos[i].data = data;
		pthread_create(&data->philos[i].thread, NULL, &routine,
			&data->philos[i]);
		++i;
	}
	pthread_create(&monitor_th, NULL, monitor, data);
	i = -1;
	while (++i < data->philos->num_of_philos)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(monitor_th, NULL);
}

int	main(int ac, char **av)
{
	t_main	data;

	if (ac != 5 && ac != 6)
		exit_error("Wrong input\nEnter valid input ./philo 12 600 200 200 [5]");
	if (check_input(av, ac) == 1)
		exit_error("Error: All arguments must be positive digits.");
	init_philo(&data, av);
	creat_thread(&data);
}
