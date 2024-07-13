/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhambouras <adhambouras@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:14:48 by adhambouras       #+#    #+#             */
/*   Updated: 2024/07/13 21:53:41 by adhambouras      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool    if_philo_died(t_philo *philo)
{
    if (get_time() - philo->last_meal > philo->data->time_to_die)
        return true;
    return false;
}

void    *ft_monitor(void *param)
{
    t_data  *data;
    t_philo *philo;
    int     i;

    i = 0;
    data = (t_data *)param;
    philo = (t_philo *)data->philo_id;
    while (i < data->num_philos)
    {
        if (if_philo_died(&philo[i]))
        {
            ft_print(&philo[i], "DEAD", BRED);
            data->death = true;
            break ;
        }
        i++;
        if (i == data->num_philos)
            i = 0;
    }
    return NULL;
}