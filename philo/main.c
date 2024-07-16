/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:22:40 by adbouras          #+#    #+#             */
/*   Updated: 2024/07/16 10:41:29 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	ft_start_sim(t_data *data)
{
	int	i;

	i = 0;
	data->time_init = get_time();
	if (data->num_philos == 1)
	{
		if (!tread_handle(&data->philo_id[0].thread, ft_one_philo, &data->philo_id[0], CREAT))
			return ;
		mutex_handle(&data->lock, LOCK);
		data->sync = true;
		mutex_handle(&data->lock, UNLOCK);
		tread_handle(&data->philo_id[0].thread, NULL, NULL, JOIN);
		// tread_handle (&data->monitor, ft_monitor, data, CREAT);
		// tread_handle (&data->monitor, NULL, NULL, JOIN);
	}
	else
		{
			while (i < data->num_philos)
			{
				if (!tread_handle(&data->philo_id[i].thread, ft_dinning, &data->philo_id[i], CREAT))
					return; // handle later
				i++;
			}
			tread_handle (&data->monitor, ft_monitor, data, CREAT);
			mutex_handle(&data->lock, LOCK);
			data->sync = true;
			mutex_handle(&data->lock, UNLOCK);
			i = 0;
			while (i < data->num_philos)
			{
				if (!tread_handle(&data->philo_id[i++].thread, NULL, NULL, JOIN))
					return ;
				i++;
			}
		}
}

int	main(int ac, char **av)
{
	t_data	*data;
	
	if (ac >= 5 && ac <= 6)
	{
		if (!(data = malloc (sizeof(t_data))))
			return (1);
		if (ft_parsing(av, data) == false)
		{
			free(data);
			write(2, "[PARSING ERR]\n", 15);
			return(1);
		}
		write(2, "[INPUT OK]\n", 11);
		ft_philos_init(data);
		// int i = 0;
		// data->time_init = get_time();
		// while (i < data->num_philos)
		// {
		// 	printf("[%-6ld] Philosopher [%-3d] in da house!\n", get_time() - data->time_init , data->philo_id[i].id);
		// 	i++;
		// }
		// i = 0;
		// while (i < data->num_philos)
		// {
		// 	printf("[%d] LF: %d | RF : %d\n", data->philo_id[i].id, data->philo_id[i].l_fork->id, data->philo_id[i].r_fork->id);
		// 	i++;
		// }
		ft_start_sim(data);
		// ft_clean(data);
	}
	else
		write(2, "[INPUT ERROR]\n", 14);
	// data = NULL;
	// system("leaks philo");
	return (0);
}
