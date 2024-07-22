/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:54:01 by adbouras          #+#    #+#             */
/*   Updated: 2024/07/22 14:32:56 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long ms)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(500);
}

long	ft_atoi(char *s)
{
	int		i;
	long	r;

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
	if (r > INT_MAX)
		return (-1);
	return (r);
}

void	ft_wait_threads(t_data *data)
{
	while (!get_bool(&data->sync, &data->sync_mutex))
		;
}
