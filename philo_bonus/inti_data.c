#include "philo_bonus.h"

void monitor_meals(sem_t *meals, t_data *data)
{
    int i;

    i = -1;
    while ( ++i < data->num_of_philos)
        sem_wait(meals);
    printf("All philosophers have eaten %d.\n", data->philos->num_to_eat);
    exit(1);
}

int init_data(t_data *data, char **av)
{
    int i;

    data->num_of_philos = ft_atol(av[1]);
    data->philos = malloc(sizeof(t_philo) * ft_atol(av[1]));
    if (!data->philos)
        return (1);
    data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, ft_atol(av[1]));
    if (data->forks == SEM_FAILED)
    {      
        free(data->philos);
        return (1);
    }
    data->print = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
    if (data->print == SEM_FAILED)
    {   
        sem_close(data->forks);
        sem_unlink("/forks");
        free(data->philos);
        return (1);
    }
    data->meals = sem_open("/meals", O_CREAT | O_EXCL, 0644, 0);
    if (data->meals == SEM_FAILED)
    {  
        sem_close(data->forks);
        sem_unlink("/forks");
        sem_close(data->print);
        sem_unlink("/print");
        free(data->philos);
        return (1);
    }
    pid_t meal_monitor = fork();
    if (meal_monitor < 0)
    {
        sem_close(data->forks);
        sem_unlink("/forks");
        sem_close(data->print);
        sem_unlink("/print");
        sem_close(data->meals);
        sem_unlink("/meals");
        free(data->philos);
        return (1);
    }
    if (meal_monitor == 0)  
        monitor_meals(data->meals, data);
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
        data->philos[i].pid = fork();
        if (!(data->philos[i].pid))
            philpho_routine(&data->philos[i]);
        if (data->philos[i].pid < 0)
        {            
            sem_close(data->forks);
            sem_unlink("/forks");
            sem_close(data->print);
            sem_unlink("/print");
            sem_close(data->meals);
            sem_unlink("/meals");
            free(data->philos);
            return (1); 
        }
    }
    int status;
    wait(&status);
    i = 0;
    if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
    {
        while (i < ft_atol(av[1]))
        {
            kill(data->philos[i].pid, SIGKILL);
            i++;
        }
        kill(meal_monitor, SIGKILL);
    }
    sem_close(data->forks);
    sem_unlink("/forks");
    sem_close(data->print);
    sem_unlink("/print");
    sem_close(data->meals);
    sem_unlink("/meals");
    free(data->philos);
    return (0);
}
