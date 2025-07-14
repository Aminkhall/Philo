#include "philo_bonus.h"

void my_print(t_philo *philo, char *msg)
{
    if(!philo || !msg)
        return ;
    sem_wait(philo->print);
    printf("%lld %d %s\n", get_current_time() - philo->start_time, philo->id, msg);
    sem_post(philo->print);
    return ;
}