/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:34:29 by adhambouras       #+#    #+#             */
/*   Updated: 2024/07/19 10:52:04 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

bool	if_philo_died(t_data *data)
{
	long	last_time;
	int		i;

	i = 0;
	while (i < data->num_philos)
	{
		last_time = get_long(&data->philo_id[i].last_meal,
				&data->philo_id[i].time);
		if (get_time() - last_time > data->time_to_die
			&& !get_bool(&data->philo_id[i].full, &data->philo_id[i].if_full))
		{
			ft_print(&data->philo_id[i], BRED"DEAD"RSET, BRED);
			return (true);
		}
		i++;
	}
	return (false);
}
