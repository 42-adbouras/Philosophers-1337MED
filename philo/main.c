/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:22:40 by adbouras          #+#    #+#             */
/*   Updated: 2024/07/10 21:23:18 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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
			break;
		}
		ft_eating(philo);
		
		ft_sleeping(philo);
		
		ft_thinking(philo);
	}
	return NULL;
}

void	ft_start_sim(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_philos == 1)
		return ;
	else
		{
			data->time_init = get_time();
			while (i < data->num_philos)
			{
				if (!tread_handle(&data->philo_id[i].thread, ft_dinning, &data->philo_id[i], CREAT))
					return; // handle later
				// pthread_create(&data->philo_id[i].thread, NULL, ft_dinning, &data->philo_id[i]);
				i++;
			}
			mutex_handle(&data->lock, LOCK);
			data->sync = true;
			mutex_handle(&data->lock, UNLOCK);
			i = 0;
			while (i < data->num_philos)
			{
				if (!tread_handle(&data->philo_id[i++].thread, NULL, NULL, JOIN))
					return ;
				// pthread_join(data->philo_id[i].thread, NULL);
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
		data->philo_id = malloc(sizeof(t_philo) * data->num_philos);
		data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
		ft_philos_init(data);
		int i = 0;
		data->time_init = get_time();
		while (i < data->num_philos)
		{
			printf("[%-6ld] Philosopher [%-3d] in da house!\n", get_time() - data->time_init , data->philo_id[i].id);
			i++;
		}
		ft_start_sim(data);
		ft_clean(data);
		printf("MEGA\n");
	}
	else
		write(2, "[INPUT ERROR]\n", 14);
	return (0);
}
