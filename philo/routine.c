/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhambouras <adhambouras@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:14:48 by adhambouras       #+#    #+#             */
/*   Updated: 2024/07/14 14:47:57 by adhambouras      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool    if_philo_died(t_philo *philo)
{
    if (get_time() - philo->last_meal > philo->data->time_to_die)
        return true;
    return false;
}

void	*ft_dinning(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	ft_wait_threads(philo->data);
	if (philo->id % 2 != 0)
		ft_sleeping(philo);
	while (!philo->data->death)
	{
		if (philo->full)
		{
			ft_print(philo, "is full", BBLU);
			break ;
		}
		// if (get_time() - philo->last_meal >= philo->data->time_to_die)
		// {
		// 	mutex_handle(&philo->state, LOCK);
		// 	philo->data->death = true;
		// 	mutex_handle(&philo->state, UNLOCK);
		// 	ft_print(philo, "DIED", BRED);
		// 	break ;
		// }
		
		ft_eating(philo);
		
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	return NULL;
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