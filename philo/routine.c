/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:14:48 by adhambouras       #+#    #+#             */
/*   Updated: 2024/07/22 14:32:09 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_dinning(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	ft_wait_threads(philo->data);
	if (philo->id % 2 == 0)
		ft_sleeping(philo);
	while (!get_bool(&philo->data->death, &philo->data->death_mutex))
	{
		if (get_bool(&philo->full, &philo->if_full))
			break ;
		ft_thinking(philo);
		ft_eating(philo);
		ft_sleeping(philo);
	}
	return (NULL);
}

void	ft_monitor(t_data *data)
{
	while (!get_bool(&data->death, &data->death_mutex))
	{
		if (all_philos_full(data))
			break ;
		if (if_philo_died(data))
		{
			set_bool(&data->death, &data->death_mutex, true);
			break ;
		}
	}
}

void	*ft_one_philo(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	mutex_handle(&philo->l_fork->forks, LOCK);
	ft_print(philo, "has taken a fork", BYEL);
	set_long(&philo->last_meal, &philo->time, get_time());
	mutex_handle(&philo->l_fork->forks, UNLOCK);
	return (NULL);
}
