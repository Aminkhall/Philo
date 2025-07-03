/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:02:12 by mkhallou          #+#    #+#             */
/*   Updated: 2025/07/03 15:59:40 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	int		sign;
	long	num;

	sign = 1;
	num = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		num = num * 10 + (*str - '0');
		str++;
		if (num > INT_MAX)
			exit_error("INT_MAX is the limit");
	}
	return (num * sign);
}

int is_valid(char *av)
{
    int i;

    if (!av)
        return (1);
    i = 0;
    if (av[i] == '+')
        ++i;
    while (av[i])
    {
        if (!ft_isdigit(av[i]))
            return (1);
        ++i; 
    }
    return (0);
}

int check_input(char **av, int ac)
{
    int i;

    if (!av || !(*av))
        return (1);
    i = 1;
    while (i < ac)
    {
        if (is_valid(av[i]) || ft_atol(av[i]) < 1)
            return (1);
        ++i;
    }
    return (0);
}
