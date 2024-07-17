/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:14:48 by adhambouras       #+#    #+#             */
/*   Updated: 2024/07/17 18:59:35 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool    if_philo_died(t_philo *philo)
{
    if (get_time() - get_value(&philo->last_meal, &philo->time) > philo->data->time_to_die
		&& !get_bool(&philo->full, &philo->if_full))
        return true;
    return false;
}

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
		{
			break ;
		}
		ft_thinking(philo);
		ft_eating(philo);
		ft_sleeping(philo);
	}
	return NULL;
}
bool	all_philos_full(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (!get_bool(&data->philo_id[i].full, &data->philo_id[i].if_full))
			return (false);
		i++;
	}
	set_bool(&data->death, &data->death_mutex, true);
	return (true);
}

void    *ft_monitor(t_data *data)
{
    t_philo *philo;
    int     i;

    i = 0;
    philo = (t_philo *)data->philo_id;
    while (i < data->num_philos)
    {
		if (all_philos_full(data))
			break ;
        if (if_philo_died(&philo[i]))
        {
            ft_print(&philo[i], BRED"DEAD"RSET, BRED);
			set_bool(&data->death, &data->death_mutex, true);
            break ;
        }
        i++;
        if (i == data->num_philos)
            i = 0;
    }
    return NULL;
}

void	*ft_one_philo(void *param)
{
	t_philo *philo;

	philo = (t_philo *)param;
	ft_wait_threads(philo->data);
	mutex_handle(&philo->l_fork->forks, LOCK);
    ft_print(philo, "has taken a fork", BYEL);
	mutex_handle(&philo->time, LOCK);
	philo->last_meal = get_time();
	mutex_handle(&philo->time, UNLOCK);
	while (philo->data->death == false)
	{
		if (get_time() - philo->last_meal > philo->data->time_to_die)
		{
			ft_print(&philo[0], "DIED", BRED);
			philo->data->death = true;
		}
	}
	mutex_handle(&philo->l_fork->forks, UNLOCK);
	return (NULL);
}
