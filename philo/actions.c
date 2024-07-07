/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhambouras <adhambouras@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:38:58 by adhambouras       #+#    #+#             */
/*   Updated: 2024/07/07 22:55:30 by adhambouras      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eating(t_philo *philo)
{
    mutex_handle(&philo->l_fork, LOCK);
    printf("[%ld] Philosopher [%d] has taken the left fork\n", get_time() - philo->data->time_init, philo->id);
    mutex_handle(&philo->r_fork, LOCK);
    printf("[%ld] Philosopher [%d] has taken the right fork\n", get_time() - philo->data->time_init, philo->id);
    mutex_handle(&philo->data->write, LOCK);
    printf("[%ld] Philosopher [%d] is eating\n", get_time() - philo->data->time_init, philo->id);
    mutex_handle(&philo->data->write, UNLOCK);
    philo->meals++;
    usleep(philo->data->time_to_eat * 1000);
    if (philo->data->num_to_eat > 0 && philo->meals == philo->data->num_to_eat)
    {
        mutex_handle(&philo->race, LOCK);
        philo->full = true;
        mutex_handle(&philo->race, UNLOCK);
    }
    mutex_handle(&philo->l_fork, UNLOCK);
    mutex_handle(&philo->r_fork, UNLOCK);
        
}

void	ft_sleeping(t_philo *philo)
{
    mutex_handle(&philo->data->write, LOCK);
    printf("[%ld] Philosopher [%d] is sleeping\n", get_time() - philo->data->time_init, philo->id);
    mutex_handle(&philo->data->write, UNLOCK);
    usleep(philo->data->time_to_sleep * 1000);
}

void	ft_thinking(t_philo *philo)
{
    printf("[%ld] Philosopher [%d] is thinking\n", get_time() - philo->data->time_init, philo->id);
}
