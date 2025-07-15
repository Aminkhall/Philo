#include "philo_bonus.h"

void monitor_meals(sem_t *meals, t_data *data)
{
    int i;

    i = -1;
    while ( ++i < data->num_of_philos)
        sem_wait(meals);
    exit(1);
}

int init_sem(t_data *data, char **av)
{
    sem_unlink("/forks");
    data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, ft_atol(av[1]));
    if (data->forks == SEM_FAILED)
        return (free(data->philos), 1);
    sem_unlink("/print");
    data->print = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
    if (data->print == SEM_FAILED)
    {   
        sem_close(data->forks);
        sem_unlink("/forks");
        return (free(data->philos), 1);
    }
    sem_unlink("/meals");
    data->meals = sem_open("/meals", O_CREAT | O_EXCL, 0644, 1);
    if (data->meals == SEM_FAILED)
    {  
        sem_close(data->forks);
        sem_unlink("/forks");
        sem_close(data->print);
        sem_unlink("/print");
        return (free(data->philos), 1);
    }
    return (0);
}
int fork_philo(t_data *data, int i)
{
    data->philos[i].pid = fork();
    if (!(data->philos[i].pid))
        philpho_routine(&data->philos[i]);
    if (data->philos[i].pid < 0)
        return (ft_clean(data), 1); 
    return (0);
}
int init_philos(t_data *data, char **av)
{
    int i;

    i = -1;
    while (++i < ft_atol(av[1]))
    {
        data->philos[i].start_time = get_current_time();
        data->philos[i].id = i + 1;
        data->philos[i].meals_eaten = 0;
        data->philos[i].num_ph = ft_atol(av[1]);
        data->philos[i].time_to_die = ft_atol(av[2]);
        data->philos[i].time_to_eat = ft_atol(av[3]);
        data->philos[i].time_to_sleep = ft_atol(av[4]);
        if (!av[5])
            data->philos[i].num_to_eat = -1;
        else
            data->philos[i].num_to_eat = ft_atol(av[5]);
        data->philos[i].last_meal = data->philos[i].start_time;
        data->philos[i].forks = data->forks;
        data->philos[i].print = data->print;
        data->philos[i].meals = data->meals;
        data->philos[i].data = data;
        if (fork_philo(data, i) == 1)
            return (1);
    }
    return (0);
}
void ft_kill(t_data *data, pid_t meal_monitor, char **av)
{
    int i;
    int status;

    wait(&status);
    i = -1;
    if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
    {
        while (++i < ft_atol(av[1]))
            kill(data->philos[i].pid, SIGKILL);
        kill(meal_monitor, SIGKILL);
    }
}
int init_data(t_data *data, char **av)
{
    int i;
    pid_t meal_monitor;

    data->num_of_philos = ft_atol(av[1]);
    data->philos = malloc(sizeof(t_philo) * ft_atol(av[1]));
    if (!data->philos)
        return (1);
    if (init_sem(data, av) == 1)
        return (1);
    meal_monitor = fork();
    if (meal_monitor < 0)
        return (ft_clean(data), 1); 
    if (meal_monitor == 0)  
        monitor_meals(data->meals, data);
    if (init_philos(data, av) == 1)
        return (1);
    ft_kill(data, meal_monitor, av);
    i = -1;
    while (++i < ft_atol(av[1]))
        waitpid(data->philos[i].pid, NULL, 0);
    ft_clean(data);
    return (0);
}
