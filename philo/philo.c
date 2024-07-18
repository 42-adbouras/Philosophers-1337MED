/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:29:41 by adbouras          #+#    #+#             */
/*   Updated: 2024/07/18 18:46:43 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_fork_ass(t_data *data)
{
	int	i = 0;

	while (i < data->num_philos)
	{
		data->forks[i].id = i + 1;	
		data->philo_id[i].r_fork = &data->forks[i];
		data->philo_id[i].l_fork = &data->forks[i + 1];
		i++;
	}
	data->philo_id[data->num_philos - 1].l_fork = &data->forks[0];
}

bool	ft_philos_init(t_data *data)
{
	int	i;

	i = 0;
	data->philo_id = malloc(sizeof(t_philo) * data->num_philos);
	data->forks = malloc(sizeof(t_mtx) * data->num_philos);
	if (!data->philo_id || !data->forks)
		return (false);
	data->death = false;
	data->sync = false;
	while (i < data->num_philos)
	{
		mutex_handle(&data->forks[i].forks, INIT);
		data->philo_id[i].id = i + 1;
		data->philo_id[i].full = false;
		data->philo_id[i].meals = 0;
		data->philo_id[i].last_meal = get_time();
		data->philo_id[i].data = data;
		mutex_handle(&data->philo_id[i].if_full, INIT);
		mutex_handle(&data->philo_id[i].state, INIT);
		mutex_handle(&data->philo_id[i].time, INIT);
		i++;
	}
	ft_fork_ass(data);
	mutex_handle(&data->meals, INIT);
	mutex_handle(&data->lock, INIT);
	mutex_handle(&data->write, INIT);
	mutex_handle(&data->sync_mutex, INIT);
	mutex_handle(&data->death_mutex, INIT);
	return (true);
}


bool	ft_parsing(char **arg, t_data *prog)
{
	if ((prog->num_philos = ft_atoi(arg[1])) <= 0)
		return (false);
	if ((prog->time_to_die = ft_atoi(arg[2])) <= 0)
		return (false);
	if ((prog->time_to_eat = ft_atoi(arg[3])) <= 0)
		return (false);
	if ((prog->time_to_sleep = ft_atoi(arg[4])) <= 0)
		return (false);
	if (arg[5])
	{
		if ((prog->num_to_eat = ft_atoi(arg[5])) <= 0)
			return (false);
	}
	else
		prog->num_to_eat = -1;
	return (true);
}
