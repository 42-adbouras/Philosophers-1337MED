/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhambouras <adhambouras@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:38:58 by adhambouras       #+#    #+#             */
/*   Updated: 2024/07/14 14:48:24 by adhambouras      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_print(t_philo *philo, char *s, char *color)
{
    (void)color;
    mutex_handle(&philo->data->write, LOCK);
    if (philo->data->death)
    {
        mutex_handle(&philo->data->write, UNLOCK);
        return ;
    }
    printf("%ld %d %s\n", get_time() - philo->data->time_init, philo->id, s);
    // printf("%s[%-6ld] Philosopher [%-3d] %s\n"RSET, color, get_time() - philo->data->time_init, philo->id, s);
    mutex_handle(&philo->data->write, UNLOCK);
}

void	ft_eating(t_philo *philo)
{
    mutex_handle(&philo->l_fork->forks, LOCK);          // LEFT LOCK
    ft_print(philo, "has taken a fork", BYEL);
    mutex_handle(&philo->r_fork->forks, LOCK);          // RGHT LOCK
    ft_print(philo, "has taken a fork", BMAG);
    ft_print(philo, "is eating", BGRN);
    ft_usleep(philo->data->time_to_eat);
    mutex_handle(&philo->data->meals, LOCK);
    philo->meals++;
    mutex_handle(&philo->data->meals, UNLOCK);
    mutex_handle(&philo->data->time, LOCK);
    philo->last_meal = get_time();
    mutex_handle(&philo->data->time, UNLOCK);
    if (philo->data->num_to_eat > 0 && philo->meals == philo->data->num_to_eat)
    {
        mutex_handle(&philo->if_full, LOCK);
        philo->full = true;
        mutex_handle(&philo->if_full, UNLOCK);
    }
    mutex_handle(&philo->l_fork->forks, UNLOCK);
    mutex_handle(&philo->r_fork->forks, UNLOCK);
}

void	ft_sleeping(t_philo *philo)
{
    if (!philo->data->death)
    {
        ft_print(philo, "is sleeping", BBLK);
        ft_usleep(philo->data->time_to_sleep);
    }
}

void	ft_thinking(t_philo *philo)
{
    if (!philo->data->death)
    {
        ft_print(philo, "is thinking", BCYN);
        ft_usleep(philo->data->time_to_eat - 10);
    }
}
