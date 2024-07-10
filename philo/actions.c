/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:38:58 by adhambouras       #+#    #+#             */
/*   Updated: 2024/07/10 15:17:07 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eating(t_philo *philo)
{
    mutex_handle(philo->l_fork, LOCK);
    printf(BYEL"[%-6ld] Philosopher [%-3d] has taken the left fork\n"RSET, get_time() - philo->data->time_init, philo->id);
    mutex_handle(philo->r_fork, LOCK);
    printf(BMAG"[%-6ld] Philosopher [%-3d] has taken the right fork\n", get_time() - philo->data->time_init, philo->id);
    mutex_handle(&philo->data->write, LOCK);
    printf(BGRN"[%-6ld] Philosopher [%-3d] is eating\n"RSET, get_time() - philo->data->time_init, philo->id);
    mutex_handle(&philo->data->write, UNLOCK);
    philo->meals++;
    usleep(philo->data->time_to_eat * 1000);
    philo->last_meal = get_time() - philo->data->time_init;
    if (philo->data->num_to_eat > 0 && philo->meals == philo->data->num_to_eat)
    {
        mutex_handle(&philo->race, LOCK);
        philo->full = true;
        mutex_handle(&philo->race, UNLOCK);
    }
    mutex_handle(philo->l_fork, UNLOCK);
    mutex_handle(philo->r_fork, UNLOCK);
        
}

void	ft_sleeping(t_philo *philo)
{
    mutex_handle(&philo->data->write, LOCK);
    printf(BBLK"[%-6ld] Philosopher [%-3d] is sleeping\n"RSET, get_time() - philo->data->time_init, philo->id);
    mutex_handle(&philo->data->write, UNLOCK);
    usleep(philo->data->time_to_sleep * 1000);
}

void	ft_thinking(t_philo *philo)
{
    mutex_handle(&philo->data->write, LOCK);
    printf(BCYN"[%-6ld] Philosopher [%-3d] is thinking\n"RSET, get_time() - philo->data->time_init, philo->id);
    mutex_handle(&philo->data->write, UNLOCK);
    usleep(20000);
}
