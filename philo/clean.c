/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:05:48 by adbouras          #+#    #+#             */
/*   Updated: 2024/07/22 14:31:43 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clean(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		mutex_handle(&data->forks[i].forks, DESTROY);
		mutex_handle(&data->philo_id[i].if_full, DESTROY);
		mutex_handle(&data->philo_id[i].time, DESTROY);
		i++;
	}
	mutex_handle(&data->meals, DESTROY);
	mutex_handle(&data->write, DESTROY);
	mutex_handle(&data->sync_mutex, DESTROY);
	mutex_handle(&data->death_mutex, DESTROY);
	free(data->philo_id);
	free(data->forks);
}
