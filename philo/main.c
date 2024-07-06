/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhambouras <adhambouras@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:22:40 by adbouras          #+#    #+#             */
/*   Updated: 2024/07/06 18:53:53 by adhambouras      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	ft_eating(t_data *data, int p)
{
	printf("%-6lu Philosopher %-3d is eating!\n", get_time() - data->time_init , data->philo_id[p].id);
	usleep(data->time_to_eat * 1000);
	data->philo_id[p].last_meal = get_time() - data->time_init;
	data->philo_id[p].meals++;
}

void	ft_sleeping(t_data *data, int p)
{
	printf("%-6lu Philosopher %-3d is sleeping!\n", get_time() - data->time_init , data->philo_id[p].id);
	usleep(data->time_to_sleep * 1000);
}

void	ft_thinking(t_data *data, int p)
{
	printf ("%-6lu Philosopher %-3d is thinking!\n", get_time() - data->time_init , data->philo_id[p].id);
}

void	*ft_dinning(void *param)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)param;
	while (1)
	{
		pthread_mutex_lock(&data->lock);
		// check
		if (i == data->num_philos)
			i = 0;
		// if (data->philo_id[0].meals == data->num_to_eat && data->philo_id[data->num_philos - 1].meals == data->num_to_eat)
		// {
		// 	printf("%-6lu Philosopher %-3d is full!\n", get_time() - data->time_init , data->philo_id[i].id);
		// 	return NULL;
		// }
		//												EATING
		ft_eating(data, i);
		//												SLEEPING
		ft_sleeping(data, i);
		//												THINKING
		ft_thinking(data, i);
		i++;
		pthread_mutex_unlock(&data->lock);
	}
	return NULL;
}

void	ft_sim(t_data *data)
{
	int	i;
	int	f = 0;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philo_id[i].thread, NULL, &ft_dinning, data);
		i++;
	}
	while (1)
	{
		i = 0;
		if (f == 1)
		{
			return ;
		}
		while (i < data->num_philos)
		{
			// if (data->philo_id[i].last_meal >= data->time_to_die)
			// {
			// 	printf (":%ld: | :%ld:\n", data->philo_id[i].last_meal, data->time_to_die);
			// 	printf("[%6lu] Philosopher [%d] DIED!\n", get_time() - data->time_init , data->philo_id[i].id);
			// 	f = 1;
			// 	break ;
			// }
			if (data->num_to_eat == data->philo_id[i].meals && data->philo_id[data->num_philos - 1].meals == data->num_to_eat)
			{
				printf("%-6lu Philosophers are full!\n", get_time() - data->time_init);
				if (data->num_to_eat == data->philo_id[0].meals && data->philo_id[data->num_philos - 1].meals == data->num_to_eat)
				f = 1;
				break;
			}
			i++;
		}
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philo_id[i].thread, NULL);
		i++;
	}
	return ;
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
		while (i < data->num_philos)
		{
			printf("%-6lu Philosopher %-3d in da house!\n", get_time() - data->time_init , data->philo_id[i].id);
			i++;
		}
		ft_sim(data);
	}
	else
		write(2, "[INPUT ERROR]\n", 14);
	return (0);
}
