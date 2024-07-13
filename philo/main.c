/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhambouras <adhambouras@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:22:40 by adbouras          #+#    #+#             */
/*   Updated: 2024/07/13 21:46:44 by adhambouras      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*ft_dinning(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	ft_wait_threads(philo->data);
	// if (philo->id % 2 != 0)
	// 	ft_sleeping(philo);
	while (!philo->data->death)
	{
		if (philo->full)
		{
			ft_print(philo, "is full", BBLU);
			break ;
		}
		if (get_time() - philo->last_meal >= philo->data->time_to_die)
		{
			mutex_handle(&philo->state, LOCK);
			philo->data->death = true;
			mutex_handle(&philo->state, UNLOCK);
			ft_print(philo, "DIED", BRED);
			break ;
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
		printf("MEGA\n");
	}
	else
		write(2, "[INPUT ERROR]\n", 14);
	// data = NULL;
	// system("leaks philo");
	return (0);
}
