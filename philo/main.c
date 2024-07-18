/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:22:40 by adbouras          #+#    #+#             */
/*   Updated: 2024/07/18 18:47:48 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


bool	ft_start_sim(t_data *data)
{
	int	i;

	i = -1;
	data->time_init = get_time();
	if (data->num_philos == 1)
	{
		if (thread_handle(&data->philo_id[0].thread, ft_one_philo, &data->philo_id[0], CREAT))
			return (false);
		set_bool(&data->sync, &data->sync_mutex, true);
		thread_handle(&data->philo_id[0].thread, NULL, NULL, JOIN);
	}
	else
		{
			while (++i < data->num_philos)
				if (thread_handle(&data->philo_id[i].thread, ft_dinning, &data->philo_id[i], CREAT))
					return (false);
			set_bool(&data->sync, &data->sync_mutex, true);
			ft_monitor(data);
			i = -1;
			while (++i < data->num_philos)
				if (thread_handle(&data->philo_id[i].thread, NULL, NULL, JOIN))
					return (false);
		}
	return (true);
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
			write(2, BRED"[PARSING ERR]\n"RSET, 25);
			return(1);
		}
		write(2, BGRN"[INPUT OK]\n"RSET, 22);
		if (!ft_philos_init(data))
			return (1);
		if (!ft_start_sim(data))
			return (1);
		ft_clean(data);
	}
	else
		write(2, "[INPUT ERROR]\n", 14);
	// data = NULL;
	// system("leaks philo");
	return (0);
}
