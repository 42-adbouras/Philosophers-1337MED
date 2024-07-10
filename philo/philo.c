/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:29:41 by adbouras          #+#    #+#             */
/*   Updated: 2024/07/10 21:21:23 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
int	ft_usleep(size_t ms)
{
	size_t start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(500);
	return 0;
}
// void	ft_fork_ass(t_philo *philo, pthread_mutex_t *forks, int pos, int n_philos)
// {
// 	philo->l_fork = &forks[pos];
// 	philo->r_fork = &forks[(pos + 1) % n_philos];
// 	if (n_philos % 2 != 0)
// 	{
// 		philo->r_fork = &forks[pos];
// 		philo->l_fork = &forks[(pos + 1) % n_philos];
// 	}
// }

void	ft_fork_ass(t_data *data)
{
	int	i = 0;
	while (i < data->num_philos)
	{
		mutex_handle(&data->forks[i], INIT);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		data->philo_id[i].l_fork = &data->forks[i];
		data->philo_id[i].r_fork = &data->forks[i - 1];
		i++;
	}
	data->philo_id[0].r_fork = &data->forks[data->num_philos - 1];
	
}

void	ft_philos_init(t_data *data)
{
	int	i;

	i = 0;
	data->death = false;
	data->sync = false;
	while (i < data->num_philos)
	{
		if (!mutex_handle(&data->forks[i], INIT))
			return ; // handle later
		data->philo_id[i].id = i + 1;
		data->philo_id[i].full = false;
		data->philo_id[i].meals = 0;
		data->philo_id[i].last_meal = 0;
		data->philo_id[i].data = data;
		mutex_handle(&data->philo_id[i].if_full, INIT);
		// ft_fork_ass(&data->philo_id[i], data->forks, i, data->num_philos);
		i++;
	}
	ft_fork_ass(data);
	mutex_handle(&data->lock, INIT);
	mutex_handle(&data->write, INIT);
}

int	ft_atoi(char *s)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	if (s[i] == '+')
		i++;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (-1);
		r = (r * 10) + s[i] - '0';
		i++;
	}
	return (r);
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
