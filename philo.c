/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:27:41 by mkhallou          #+#    #+#             */
/*   Updated: 2025/06/30 19:54:00 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void ft_creat_philo(t_philo philo)
// {
//     int *philosopher;
    
//     pthread_create()
// }

int main(int ac, char **av)
{
    t_data data;

    if (ac != 5 && ac != 6)
        exit_error("Wrong input\nEnter valid input ./philo 12 600 200 200 [5]");
    if (check_input(av, ac) == 1)
        exit_error("Error: All arguments must be positive digits.");
        
    
}
