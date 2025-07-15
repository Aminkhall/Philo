#include "philo_bonus.h"

long long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_mysleep(long time)
{
	time_t	start;

	start = get_current_time();
	while (get_current_time() - start < time)
		usleep(100);
}

int main(int ac, char **av)
{
    t_data data;
    if (ac != 5 && ac != 6)
        exit_error("Error: invalid number of arguments.\n"
            "./philo_bonus 5 800 200 200 [7]");
    if (check_input(av, ac) == 1)
        exit_error("Error: All arguments must be positive digits.");
    if (init_data(&data, av) == 1)
    {
        exit_error("Error: Failed to initialize data.");
        
    }
    exit(0);    
}